
#ifndef AUDIO_PLAYER_OVERDRIVE_H
#define AUDIO_PLAYER_OVERDRIVE_H

#include <complex>
#include "Effect.h"

template<typename SampleType>
class Overdrive : public Effect<SampleType> {
public:
    explicit Overdrive(SampleType lowerBound, SampleType upperBound);

protected:
    SampleType applyImpl(SampleType sample) override;

    SampleType lowerRangeTransform(SampleType sample);

    SampleType middleRangeTransform(SampleType sample);

private:
    SampleType lowerBound;
    SampleType upperBound;
};

template<typename SampleType>
SampleType Overdrive<SampleType>::applyImpl(SampleType sample) {
    SampleType sampleAbs = std::abs(sample);
    if (sampleAbs > lowerBound) {
        return lowerRangeTransform(sample);
    }
    if (sampleAbs < upperBound) {
        return middleRangeTransform(sample);
    }
    return sample;
}

template<typename SampleType>
SampleType Overdrive<SampleType>::lowerRangeTransform(SampleType sample) {
    return 2 * sample;
}

template<typename SampleType>
Overdrive<SampleType>::Overdrive(SampleType inLowerBound, SampleType inUpperBound)
        :lowerBound{inLowerBound},
         upperBound{inUpperBound} {

}

template<typename SampleType>
SampleType Overdrive<SampleType>::middleRangeTransform(SampleType sample) {
    return (3 - (2 - 3 * sample) * (2 - 3 * sample)) / 3;
}


#endif //AUDIO_PLAYER_OVERDRIVE_H
