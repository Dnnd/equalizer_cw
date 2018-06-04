
#ifndef AUDIO_PLAYER_ECHO_H
#define AUDIO_PLAYER_ECHO_H

#include "Effect.h"
#include <vector>

template<typename SampleType>
class Echo : public Effect {
public:
    explicit Echo(int delay);

protected:
    SampleType applyImpl(SampleType sample) override;

private:
    std::vector<SampleType> buffer;
    std::size_t front = 0;
    std::size_t last = 1;
};

template<typename SampleType>
Echo<SampleType>::Echo(int delay)
        :Effect(),
         buffer(0, delay) {

}

template<typename SampleType>
SampleType Echo<SampleType>::applyImpl(SampleType sample) {
    buffer[front++ % buffer.size()] = sample;
    return buffer[last++ %buffer.size()] + sample;
}

#endif //AUDIO_PLAYER_ECHO_H
