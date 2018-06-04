
#ifndef AUDIO_PLAYER_EFFECT_H
#define AUDIO_PLAYER_EFFECT_H

template<typename SampleType>
class Effect {

public:
    SampleType apply(SampleType sample);


    virtual void toggle();

protected:
    virtual SampleType applyImpl(SampleType sample) = 0;

    bool isEnabled = false;
};

template<typename SampleType>
void Effect<SampleType>::toggle() {
    isEnabled = !isEnabled;
}

template<typename SampleType>
SampleType Effect<SampleType>::apply(SampleType sample) {
    if(isEnabled){
        return applyImpl(sample);
    }
    return sample;
}


#endif //AUDIO_PLAYER_EFFECT_H
