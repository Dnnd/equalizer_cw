
#ifndef AUDIO_PLAYER_ECHO_H
#define AUDIO_PLAYER_ECHO_H

#include "Effect.h"
#include <vector>
#include <cmath>

template<typename SampleType>
class Echo : public Effect<SampleType> {
public:
    explicit Echo(int delayMs, double rate);

    void setDelay(double delayMs);
    void changeParam(QVariant param) override;

protected:
    SampleType applyImpl(SampleType sample) override;

private:
    std::vector<SampleType> buffer;
    std::size_t front = 0;
    double gain = 0.85;
    double rate = 0;
    QReadWriteLock rwlock;
};

template<typename SampleType>
Echo<SampleType>::Echo(int delayMs, double inRate)
        :buffer{}, rate{inRate} {
    long delay = std::lround(inRate * delayMs*0.000001);
    buffer.resize(static_cast<unsigned long>(delay));
}

template<typename SampleType>
SampleType Echo<SampleType>::applyImpl(SampleType sample) {
    QReadLocker locker{&rwlock};
    front = (front + 1) % buffer.size();
    SampleType ret = sample;
    std::size_t i = front, gainPow = 0;
    for(; i < buffer.size(); ++i, ++gainPow){
        ret += buffer[i] * std::pow(gain, buffer.size() + 1 - gainPow);
    }
    for(i = 0; i < front; ++i, ++gainPow){
        ret += buffer[i] * std::pow(gain, buffer.size() + 1 - gainPow);
    }

    buffer[front] = sample;
    return ret;
}

template<typename SampleType>
void Echo<SampleType>::setDelay(double delayMs) {
    QWriteLocker locker{&rwlock};
    buffer.clear();
    front = 0;
    long delay = std::lround(rate * delayMs*0.000001);
    buffer.resize(static_cast<unsigned long>(delay));
}

template<typename SampleType>
void Echo<SampleType>::changeParam(QVariant param) {
    int delayMs = param.toInt();
    setDelay(delayMs);
}


#endif //AUDIO_PLAYER_ECHO_H
