#include <QtCore/QFuture>
#include <QtConcurrent/QtConcurrent>
#include "AudioPlayer.h"

int tick(void *outputBuffer,
         void *inputBuffer,
         unsigned int nBufferFrames,
         double streamTime,
         RtAudioStreamStatus status,
         void *userData) {
    AudioPlayer *player = (AudioPlayer *) userData;
    if (status != 0) {
        qDebug() << "status alert: " << status;
    }
    stk::StkFloat *samples = (stk::StkFloat *) outputBuffer;
    return player->onNewAudioBufferAcquire(samples);

}

AudioPlayer::AudioPlayer(AudioPlayer::ChannelFiltersSet &&channelFilters, QObject *parent)
        : QObject(parent),
          bufferSize{stk::RT_BUFFER_SIZE},
          leftFilters{std::move(channelFilters)},
          rightFilters{leftFilters},
          threadPool{new QThreadPool{this}} {

    stk::Stk::setSampleRate(44100);
    //GUI-thread + audio-thread
    threadPool->setMaxThreadCount(QThread::idealThreadCount() - 2);

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

    for (unsigned int j = 0; j < frames.frames(); j++) {

        auto leftFiltersProcessing = QtConcurrent::run(threadPool, [this, sample = frames(j, 0)] {
            stk::StkFloat res = 0;
            for (auto &filter : leftFilters) {
                res += filter.processSample(sample);
            }
            return res;
        });

        auto rightFiltersProcessing = QtConcurrent::run(threadPool, [this, sample = frames(j, 1)] {
            stk::StkFloat res = 0;
            for (auto &filter : rightFilters) {
                res += filter.processSample(sample);
            }
            return res;
        });
        watcher.addFuture(leftFiltersProcessing);
        watcher.addFuture(rightFiltersProcessing);
        for (const auto &future : watcher.futures()) {
            stk::StkFloat result = future.result();
            for (auto &&effect : effectsStorage) {
                result = effect->apply(result);
            }
            if (result > 1) {
                result = 1;
            }
            if (result < -1) {
                result = -1;
            }

            *outputBuffer++ = result;
        }

        watcher.clearFutures();
    }

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


