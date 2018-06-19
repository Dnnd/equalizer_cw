#include <QtCore/QFuture>
#include <QtConcurrent/QtConcurrent>
#include "AudioPlayer.h"
#include <QDebug>

int tick(void *outputBuffer,
         void *inputBuffer,
         unsigned int nBufferFrames,
         double streamTime,
         RtAudioStreamStatus status,
         void *userData) {
    AudioPlayer *player = (AudioPlayer *) userData;
    stk::StkFloat *samples = (stk::StkFloat *) outputBuffer;
    return player->onNewAudioBufferAcquire(samples);

}

AudioPlayer::AudioPlayer(AudioPlayer::ChannelFiltersSet &&channelFilters, QObject *parent)
        : QObject(parent),
          bufferSize{stk::RT_BUFFER_SIZE},
          leftFilters{std::move(channelFilters)},
          rightFilters{leftFilters},
          spectre(stk::RT_BUFFER_SIZE/2, this),
          threadPool{new QThreadPool{this}} {

    stk::Stk::setSampleRate(44100);
    //GUI-thread + audio-thread
    threadPool->setMaxThreadCount(QThread::idealThreadCount() - 2);
    qDebug() << leftFilters.size() << " " << rightFilters.size();

}

void AudioPlayer::play(QString audioPath) {
    source.reset();
    if (dac.isStreamOpen()) {
        dac.closeStream();
    }

    auto path = audioPath.toStdString();
    source.openFile(path);
    stk::StkFloat rate = source.getFileRate() / stk::Stk::sampleRate();
    source.setRate(rate);
    RtAudio::StreamParameters parameters;
    source.ignoreSampleRateChange();
    int channels = source.channelsOut();

    parameters.deviceId = dac.getDefaultOutputDevice();
    RtAudio::DeviceInfo dinfo = dac.getDeviceInfo(parameters.deviceId);

    parameters.nChannels = channels;

    RtAudioFormat format = RTAUDIO_FLOAT64;
    frames.resize(bufferSize, channels);
    dac.openStream(&parameters,
                   NULL,
                   format,
                   (unsigned int) stk::Stk::sampleRate(),
                   &bufferSize,
                   &tick,
                   (void *) this);
    dac.startStream();

}

int AudioPlayer::onNewAudioBufferAcquire(stk::StkFloat *outputBuffer) {
    source.tick(frames);

    QFutureSynchronizer<stk::StkFloat> watcher;

    auto leftInputSpectrum = QtConcurrent::run(threadPool, [this]{
        spectre.lock();
        spectre.setData(frames, 0);
        emit inputSpectrumUpdate();
        spectre.unlock();
    });


    std::vector<double> outputs;
    outputs.reserve((frames.size() / 2));

    for (unsigned int j = 0; j < frames.frames(); j++) {

        auto leftFiltersProcessing = QtConcurrent::run(threadPool, [this, sample = frames(j, 0)] {

            stk::StkFloat res = 0;
            for (auto &filter : leftFilters) {
                res += filter.processSample(sample);
            }
            for (auto &&effect : effectsStorage) {
                res = effect->apply(res);
            }
            return res;
        });

        auto rightFiltersProcessing = QtConcurrent::run(threadPool, [this, sample = frames(j, 1)] {
            stk::StkFloat res = 0;
            for (auto &filter : rightFilters) {
                res += filter.processSample(sample);
            }
            for (auto &&effect : effectsStorage) {
                res = effect->apply(res);
            }
            return res;
        });

        watcher.addFuture(leftFiltersProcessing);
        watcher.addFuture(rightFiltersProcessing);
        for (const auto &future : watcher.futures()) {
            stk::StkFloat result = future.result();

            if (result < -1) {
                result = -1;
            } else if (result > 1) {
                result = 1;
            }
            *outputBuffer++ = result;
        }
        outputs.push_back(watcher.futures()[0].result());
        watcher.clearFutures();
    }

    auto outputSpectrum = QtConcurrent::run(threadPool,[this, outputs = std::move(outputs) ]{
        spectre.lock();
        spectre.setData(outputs, 1);
        emit outputSpectrumUpdate();
        spectre.unlock();
    });


    if (source.isFinished()) {
        return 1;
    } else
        return 0;
}


void AudioPlayer::resume() {
    if (dac.isStreamOpen()) {
        dac.startStream();
    }
}

void AudioPlayer::setGain(int band, int gain) {
    if(band >= leftFilters.size()){
        return;
    }
    leftFilters[band].setGain(gain);
    rightFilters[band].setGain(gain);
}

void AudioPlayer::registerEffect(const std::string &effectId, Effect<stk::StkFloat> *effect) {
    effectsRegistry[effectId] = effect;
    effectsStorage.push_back(effect);
}

stk::StkFloat AudioPlayer::getSampleRate() {
    return stk::Stk::sampleRate();
}

AudioPlayer::~AudioPlayer() {
    for (auto *effect: effectsStorage) {
        delete effect;
    }
}

void AudioPlayer::toggleEffect(const QString &effectId) {
    auto found = effectsRegistry.find(effectId.toStdString());
    if (found != effectsRegistry.end()) {
        auto effect = found->second;
        effect->toggle();
    }
}

void AudioPlayer::changeParameter(QString effectId, QVariant param) {
    auto found = effectsRegistry.find(effectId.toStdString());
    if (found != effectsRegistry.end()) {
        auto effect = found->second;
        effect->changeParam(param);
    }
}

void AudioPlayer::pause() {
    if (dac.isStreamOpen()) {
        dac.stopStream();
    }
}

AudioSpectre *AudioPlayer::getSpectrum() {
    return &spectre;
}


