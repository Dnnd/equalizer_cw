
#ifndef EQULIZER_SECONDORDERSECTION_H
#define EQULIZER_SECONDORDERSECTION_H

#include <array>

enum SoSCoeffs {
    B0,
    B1,
    B2,
    A1,
    A2
};

template<typename CoeffType>
class SecondOrderSection {
public:
    struct CalcFrame {
        double left{0};
        double right{0};
    };

    SecondOrderSection(const CoeffType *num, const CoeffType *den);


    CalcFrame processFrame(CalcFrame frame);

    void calcDenZ();

    void calcNumZ();

    std::array<CoeffType, 5> coeffs;
    std::array<CalcFrame, 2> buffer;
    std::array<CalcFrame, 2> calcBuffer;
};


template<typename CoeffType>
typename SecondOrderSection<CoeffType>::CalcFrame SecondOrderSection<CoeffType>::processFrame(CalcFrame frame) {

    double xLeft = frame.left + calcBuffer[0].left;

    double xRight = frame.right + calcBuffer[0].right;

    buffer[1] = buffer[0];
    buffer[0].left = xLeft;
    buffer[0].right = xRight;
    CalcFrame out{xLeft * coeffs[B0] + calcBuffer[1].left, xRight * coeffs[B0] + calcBuffer[1].right};

    return out;
}

template<typename CoeffType>
void SecondOrderSection<CoeffType>::calcDenZ() {
    calcBuffer[0].left = coeffs[A1] * buffer[0].left + coeffs[A2] * buffer[1].left;
    calcBuffer[0].right = coeffs[A1] * buffer[0].right + coeffs[A2] * buffer[1].right;
}

template<typename CoeffType>
void SecondOrderSection<CoeffType>::calcNumZ() {
    calcBuffer[1].left = coeffs[B1] * buffer[0].left + coeffs[B2] * buffer[1].left;
    calcBuffer[1].right = coeffs[B1] * buffer[0].right + coeffs[B2] * buffer[1].right;
}

template<typename CoeffType>
SecondOrderSection<CoeffType>::SecondOrderSection(const CoeffType *num, const CoeffType *den)
        :coeffs{0, 0, 0, 0, 0},
         buffer{0, 0},
         calcBuffer{0, 0} {
    for (auto i = 0; i < 3; ++i) {
        coeffs[i] = num[i];
    }
    //skip den[0] because it always equals 1
    for (auto i = 0; i < 2; ++i) {
        coeffs[i + 3] = -den[i + 1];
    }
}


#endif //EQULIZER_SECONDORDERSECTION_H
