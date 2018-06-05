
#ifndef AUDIO_PLAYER_EFFECT_H
#define AUDIO_PLAYER_EFFECT_H

template<typename SampleType>
class Effect {

public:
    SampleType apply(SampleType sample);

    virtual void changeParam(QVariant param);

    virtual void toggle();

    virtual ~Effect<SampleType>() = default;

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

template<typename SampleType>
void Effect<SampleType>::changeParam(QVariant param) {

}


#endif //AUDIO_PLAYER_EFFECT_H
