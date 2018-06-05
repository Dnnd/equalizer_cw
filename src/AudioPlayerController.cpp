
#include <QtCore/QUrl>
#include "AudioPlayerController.h"


AudioController::AudioController(AudioPlayer *target, QObject *parent)
        : QObject(parent) {
    QObject::connect(this, &AudioController::play, target, &AudioPlayer::play);
    QObject::connect(this, &AudioController::gain, target, &AudioPlayer::setGain);
    QObject::connect(this, &AudioController::effect, target, &AudioPlayer::toggleEffect);
    QObject::connect(this, &AudioController::newParameter, target, &AudioPlayer::changeParameter);
    QObject::connect(this, &AudioController::stopSignal, target, &AudioPlayer::pause);
    QObject::connect(this, &AudioController::resumeSignal, target, &AudioPlayer::resume);
}

void AudioController::setGain(int band, int gainDb) {
    emit gain(band, gainDb);
}

void AudioController::playSong(QString file) {
    QUrl url {file};

    emit play(url.toLocalFile());

}

void AudioController::toggleEffect(QString effectId) {
    emit effect(effectId);
}

void AudioController::changeEffectParam(const QString &effectId, QVariant param) {
    emit newParameter(effectId, param);
}

void AudioController::stop() {
    emit stopSignal();

}

void AudioController::resume() {
    emit resumeSignal();
}
