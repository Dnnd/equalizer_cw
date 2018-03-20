#ifndef EQULIZER_FILTER_H
#define EQULIZER_FILTER_H

#include <vector>
#include "filters/fdacoefs.h"
#include "SecondOrderSection.h"


using CoeffType = real64_T;

template<int NumLen, int DenLen>
class Filter {
public:

    Filter(const CoeffType (*num)[NumLen], const CoeffType (*den)[DenLen], std::size_t len);

    template<typename Frame>
    void processFrame(Frame frame);

    void prepareSections();

    void setBufferSize(std::size_t buffSize);

    std::vector<SecondOrderSection<CoeffType>::CalcFrame> harvest();

private:
    std::vector<SecondOrderSection<CoeffType>> sections_;
    std::vector<SecondOrderSection<CoeffType>::CalcFrame> buffer_;

};

template<int NumLen, int DenLen>
Filter<NumLen, DenLen>::Filter(const CoeffType (*num)[NumLen], const CoeffType (*den)[DenLen], std::size_t len) {
    sections_.reserve(len);
    for (auto i = 0; i < len; ++i) {
        sections_.emplace_back(num[i], den[i]);
    }

}

template<int NumLen, int DenLen>
template<typename Frame>
void Filter<NumLen, DenLen>::processFrame(Frame frame) {
    SecondOrderSection<CoeffType>::CalcFrame calcFrame{static_cast<double>(frame.left),
                                                       static_cast<double >(frame.right)};

    prepareSections();
    for (auto &&i: sections_) {
        calcFrame = i.processFrame(calcFrame);
    }

    buffer_.push_back(calcFrame);
}

template<int NumLen, int DenLen>
void Filter<NumLen, DenLen>::prepareSections() {
    for (auto &&i: sections_) {
        i.calcNumZ();
        i.calcDenZ();
    }
}

template<int NumLen, int DenLen>
void Filter<NumLen, DenLen>::setBufferSize(std::size_t buffSize) {
    buffer_.reserve(buffSize);

}

template<int NumLen, int DenLen>
std::vector<SecondOrderSection<CoeffType>::CalcFrame> Filter<NumLen, DenLen>::harvest() {
    std::vector<SecondOrderSection<CoeffType>::CalcFrame> swap;
    swap.reserve(buffer_.size());
    swap.swap(buffer_);
    return std::move(swap);
}

#endif //EQULIZER_FILTER_H
