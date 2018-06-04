#ifndef AUDIO_PLAYER_AUDIOPLAYERCONTROLLER_H
#define AUDIO_PLAYER_AUDIOPLAYERCONTROLLER_H


#include <QtCore/QObject>
#include "AudioPlayer.h"

class AudioController : public QObject {
Q_OBJECT
public:
    explicit AudioController(AudioPlayer *target, QObject *parent);

    Q_INVOKABLE void setGain(int band, int gain);
    Q_INVOKABLE void playSong(QString file);

signals:

    void play(QString file);

    void gain(int band, int gain);


};


#endif //AUDIO_PLAYER_AUDIOPLAYERCONTROLLER_H
