#ifndef EQULIZER_SECONDORDERSECTION_H
#define EQULIZER_SECONDORDERSECTION_H

#include <array>
#include <QDebug>
#include <Stk.h>

enum SoSCoeffs {
    B0 = 0,
    B1 = 1,
    B2 = 2,
    A1 = 3,
    A2 = 4
};

template<typename CoeffType, typename SampleType>
class SecondOrderSection {
public:

    SecondOrderSection(const CoeffType *num, const CoeffType *den);


    SampleType processSample(const SampleType &sample) const;

    SampleType calcBufferedSample(SampleType sample) const;

    SampleType calcOutputSample(SampleType bufferedSample) const;

    std::array<CoeffType, 5> coeffs;
    mutable std::array<SampleType, 2> buffer;
};


template<typename CoeffType, typename SampleType>
SampleType SecondOrderSection<CoeffType, SampleType>::processSample(const SampleType &sample) const {

    double bufferedSample = calcBufferedSample(sample);
    double out = calcOutputSample(bufferedSample);

    buffer[1] = buffer[0];
    buffer[0] = bufferedSample;
    return out;
}



template<typename CoeffType, typename SampleType>
SecondOrderSection<CoeffType, SampleType>::SecondOrderSection(const CoeffType *num, const CoeffType *den)
        :coeffs{0, 0, 0, 0, 0},
         buffer{0, 0}{
    for (auto i = 0; i < 3; ++i) {
        coeffs[i] = num[i];
    }

    for (auto i = 0; i < 2; ++i) {
        coeffs[i + 3] = den[i + 1];
    }
}

template<typename CoeffType, typename SampleType>
SampleType SecondOrderSection<CoeffType, SampleType>::calcOutputSample(SampleType bufferedSample) const {
    return coeffs[B0] * bufferedSample + coeffs[B1] * buffer[0] + coeffs[B2] * buffer[1];
}

template<typename CoeffType, typename SampleType>
SampleType SecondOrderSection<CoeffType, SampleType>::calcBufferedSample(SampleType sample) const {
    return sample - coeffs[A1] * buffer[0] - coeffs[A2] * buffer[1];
}


#endif