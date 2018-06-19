#ifndef AUDIO_PLAYER_AUDIOPLAYER_H
#define AUDIO_PLAYER_AUDIOPLAYER_H

#include <QObject>
#include <RtAudio.h>
#include <FileWvIn.h>
#include "Filter.h"
#include "Effect.h"
#include "AudioSpectre.h"
#include <QThreadPool>
#include <unordered_map>

class AudioPlayer : public QObject {
Q_OBJECT
public:
    using Filter_t = Filter<3, 3>;
    using ChannelFiltersSet = std::vector<Filter_t>;

    explicit AudioPlayer(std::vector<Filter_t> &&filters, QObject *parent = nullptr);

    int onNewAudioBufferAcquire(stk::StkFloat *outputBuffer);

    void registerEffect(const std::string &id, Effect<stk::StkFloat> *effect);

    AudioSpectre *getSpectrum();

    stk::StkFloat getSampleRate();

    ~AudioPlayer() override;

public slots:

    void play(QString audioPath);

    void setGain(int band, int gain);

    void pause();

    void resume();

    void toggleEffect(const QString &effectId);

    void changeParameter(QString effectId, QVariant param);


public:


signals:

    void inputSpectrumUpdate();
    void outputSpectrumUpdate();

    void finish();

private:
    RtAudio dac;
    stk::FileWvIn source;
    unsigned bufferSize;
    stk::StkFrames frames;
    ChannelFiltersSet leftFilters;
    ChannelFiltersSet rightFilters;
    QThreadPool *threadPool;
    std::unordered_map<std::string, Effect<stk::StkFloat> *> effectsRegistry;
    std::vector<Effect<stk::StkFloat> *> effectsStorage;
    AudioSpectre spectre;
};


#endif //AUDIO_PLAYER_AUDIOPLAYER_H
