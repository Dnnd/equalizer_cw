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
    Frame processFrame(Frame frame);

private:
    mutable std::vector<SecondOrderSection<CoeffType>> sections_;
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
Frame Filter<NumLen, DenLen>::processFrame(Frame frame) {
    SecondOrderSection<CoeffType>::CalcFrame calcFrame{static_cast<double>(frame.left),
                                                       static_cast<double >(frame.right)};
    for (auto &&i:sections_) {
        i.calcDenZ();
        i.calcNumZ();
    }

    for (auto &&i: sections_) {
        calcFrame = i.processFrame(calcFrame);
    }

    Frame out;
    out.left = calcFrame.left;
    out.right = calcFrame.right;
    return std::move(out);
}

#endif //EQULIZER_FILTER_H
