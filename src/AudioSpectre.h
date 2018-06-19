#ifndef AUDIO_PLAYER_AUDIOSPECTRE_H
#define AUDIO_PLAYER_AUDIOSPECTRE_H


#include <QtCore/QObject>
#include <QtCharts/QAbstractSeries>
#include <Stk.h>
#include <QtCore/QMutex>
#include "kiss_fftr.h"

QT_CHARTS_USE_NAMESPACE

class AudioSpectre : public QObject{
Q_OBJECT
public:
    explicit AudioSpectre(std::size_t length, QObject *parent = nullptr);

    void lock();
    void unlock();

    ~AudioSpectre() override;

public slots:
    void setData(const stk::StkFrames &frames,unsigned int channel);
    void setData(std::vector<double> frames, unsigned channel);

    void update(QAbstractSeries *series, unsigned channel);


private:
    QMutex mutex;
    std::array<QVector<QPointF>, 2> spectrums;
    std::array<kiss_fft_scalar*, 2> inputs;
    std::array<kiss_fft_cpx*, 2> outputs;
    std::size_t length;
    kiss_fftr_cfg cfg;
    double freqStep;

};


#endif //AUDIO_PLAYER_AUDIOSPECTRE_H
