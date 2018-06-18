#ifndef EQULIZER_FILTER_H
#define EQULIZER_FILTER_H

#include <vector>
#include <mutex>
#include "SecondOrderSection.h"
#include <QReadWriteLock>
#include <cmath>
#include <QReadLocker>
#include <QWriteLocker>

template<int NumLen,
        int DenLen,
        typename CoeffType = double,
        typename SampleType = double
>
class Filter {
public:
    using Section_t = SecondOrderSection<CoeffType, SampleType>;

    Filter(const CoeffType (*num)[NumLen], const CoeffType (*den)[DenLen], std::size_t len);

    Filter(const Filter &other);

    SampleType processSample(const SampleType &sample) const;

    void setGain(int gainDb);

    double getGain() const;

private:
    std::vector<Section_t> sections_;
    double gain = 1;
    mutable QReadWriteLock gainLock;

};

template<int NumLen, int DenLen, typename CoeffType, typename SampleType>
Filter<NumLen, DenLen, CoeffType, SampleType>::Filter(const CoeffType (*num)[NumLen], const CoeffType (*den)[DenLen],
                                                      std::size_t len) {
    sections_.reserve(len);
    for (auto i = 0; i < len; ++i) {
        sections_.emplace_back(num[i], den[i]);
    }

}

template<int NumLen,
        int DenLen,
        typename CoeffType,
        typename SampleType>
SampleType Filter<NumLen, DenLen, CoeffType, SampleType>::processSample(const SampleType &sample) const {
    SampleType resSample = sample;
    for (auto &&i: sections_) {
        resSample = i.processSample(resSample);
    }
    auto gain = getGain();
    resSample = gain * resSample;

    return resSample;
}

template<int NumLen, int DenLen, typename CoeffType, typename SampleType>
Filter<NumLen, DenLen, CoeffType, SampleType>::Filter(const Filter &other)
        :sections_{other.sections_} {

}

template<int NumLen, int DenLen, typename CoeffType, typename SampleType>
void Filter<NumLen, DenLen, CoeffType, SampleType>::setGain(int gainDb) {
    QWriteLocker lock(&gainLock);
    gain = std::pow(10, gainDb / 20.);
}

template<int NumLen, int DenLen, typename CoeffType, typename SampleType>
double Filter<NumLen, DenLen, CoeffType, SampleType>::getGain() const {
    QReadLocker lock(&gainLock);
    return gain;
}


template<typename Filter, typename SampleType>
class Filtered {
public:
    explicit Filtered(SampleType inSample);

    using result_type = SampleType;

    SampleType operator()(const Filter &filter);

private:
    SampleType sample;
};

template<typename Filter, typename SampleType>
SampleType Filtered<Filter, SampleType>::operator()(const Filter &filter) {
    return filter.processSample(sample);
}

template<typename Filter, typename SampleType>
Filtered<Filter, SampleType>::Filtered(SampleType inSample)
        :sample{inSample} {

}

template<typename SampleType>
class SampleReducer {
public:
    void operator()(SampleType &result, const SampleType &sample) {
        result += sample;
    }
};

#endif //EQULIZER_FILTER_H