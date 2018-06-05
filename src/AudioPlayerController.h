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
    Q_INVOKABLE void toggleEffect(QString effect);
    Q_INVOKABLE void changeEffectParam(const QString &effectId, QVariant param);
    Q_INVOKABLE void stop();
    Q_INVOKABLE void resume();
signals:

    void play(QString file);

    void gain(int band, int gain);

    void effect(QString effect);

    void newParameter(QString effectId, QVariant parameter);
    void stopSignal();
    void resumeSignal();

};


#endif //AUDIO_PLAYER_AUDIOPLAYERCONTROLLER_H
