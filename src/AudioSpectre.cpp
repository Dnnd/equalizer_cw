#include "AudioSpectre.h"

#include <QtCharts/QXYSeries>
#include <QtQuick/QQuickView>
#include <QtQuick/QQuickItem>

QT_CHARTS_USE_NAMESPACE

Q_DECLARE_METATYPE(QAbstractSeries *)

Q_DECLARE_METATYPE(QAbstractAxis *)

AudioSpectre::AudioSpectre(std::size_t len, QObject *parent) :
        QObject(parent),
        length{len},
        freqStep(44100. / len) {
    qRegisterMetaType<QAbstractSeries *>();
    qRegisterMetaType<QAbstractAxis *>();

    cfg = kiss_fftr_alloc(length, 0, NULL, NULL);
    for (auto &input: inputs) {
        input = new kiss_fft_scalar[length];
    }
    for (auto &output: outputs) {
        output = new kiss_fft_cpx[length / 2 + 1];
    }
    spectrums[0].resize(length / 2 + 1);
    spectrums[1].resize(length / 2 + 1);
}

void AudioSpectre::update(QAbstractSeries *series, unsigned channel) {
    if (series) {

        QXYSeries *xySeries = static_cast<QXYSeries *>(series);

        xySeries->replace(spectrums[channel]);

    }
}

void AudioSpectre::setData(const stk::StkFrames &frames, unsigned int channel) {

    kiss_fft_scalar *in = inputs[channel];

    kiss_fft_cpx *out = outputs[channel];

    for (std::size_t i = 0; i < length; ++i) {
        in[i] = frames(i, channel);
    }

    kiss_fftr(cfg, in, out);
    for (std::size_t i = 0; i < length / 2 + 1; ++i) {
        spectrums[channel][i] = QPointF(i * 1. / length * 44100,10*std::log10(out[i].i * out[i].i + out[i].r * out[i].r));
    }
}

void AudioSpectre::setData(std::vector<double> frames, unsigned channel) {

    kiss_fft_scalar *in = frames.data();

    kiss_fft_cpx *out = outputs[channel];

    kiss_fftr(cfg, in, out);
    for (std::size_t i = 0; i < length / 2 + 1; ++i) {
        spectrums[channel][i] = QPointF(i * 1. / length * 44100,10*std::log10(out[i].i * out[i].i + out[i].r * out[i].r));
    }

}

AudioSpectre::~AudioSpectre() {
    free(cfg);
    for (auto &input: inputs) {
        delete[]input;
    }
    for (auto &output: outputs) {
        delete[]output;
    }
}

void AudioSpectre::lock() {
    mutex.lock();

}

void AudioSpectre::unlock() {
    mutex.unlock();

}
