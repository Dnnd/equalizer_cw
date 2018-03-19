//
// Created by danm on 18.03.18.
//

#ifndef EQULIZER_AUDIOPROCESSOR_H
#define EQULIZER_AUDIOPROCESSOR_H

#include <vector>
#include <QtCore/QFutureWatcher>
#include <QtCore/QBuffer>
#include <QtMultimedia/QAudioOutput>
#include "Filter.h"
#include "DecodedAudioReciever.h"

using SosFilter = Filter<3, 3>;

class AudioProcessor : public QObject {
public:
    AudioProcessor(DecodedAudioReciever *reciever,
                   QBuffer *audioBuffer,
                   std::vector<SosFilter> filters,
                   QObject *parent);


    void configure(QAudioOutput* output);

public slots:

    void onNotify();

private:
    std::vector<SosFilter> filters_;
    QFutureWatcher<std::vector<QAudioBuffer::S16S>> watcher_;
    DecodedAudioReciever *reciever_;
    QByteArray &buffer_;
    QBuffer *audioBuffer_;
    QAudioFormat format;
    int notifyInterval;
    int processed{0};
};


#endif //EQULIZER_AUDIOPROCESSOR_H
