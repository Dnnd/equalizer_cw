
#include <QtCore/QUrl>
#include "AudioPlayerController.h"


AudioController::AudioController(AudioPlayer *target, QObject *parent)
        : QObject(parent) {
    QObject::connect(this, &AudioController::play, target, &AudioPlayer::play);
    QObject::connect(this, &AudioController::gain, target, &AudioPlayer::setGain);

}

void AudioController::setGain(int band, int gainDb) {
    emit gain(band, gainDb);
}

void AudioController::playSong(QString file) {
    QUrl url {file};

    emit play(url.toLocalFile());

}
