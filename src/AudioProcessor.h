#ifndef EQULIZER_AUDIOPROCESSOR_H
#define EQULIZER_AUDIOPROCESSOR_H

#include <vector>
#include <QtCore/QFutureWatcher>
#include <QtCore/QBuffer>
#include <QtMultimedia/QAudioOutput>
#include "Filter.h"
#include "DecodedAudioReciever.h"
#include "SosFilterController.h"
#include <QElapsedTimer>
using SosFilter = Filter<3, 3>;
class SosFilterController;

class AudioProcessor : public QObject {
public:
    AudioProcessor(DecodedAudioReciever *reciever,
                   QByteArray *audioBuffer,
                   QBuffer *ab,
                   std::vector<SosFilter> filters,
                   std::size_t notifyInterval,
                   QObject *parent);

    void summarize(std::size_t blockNumber);

public slots:

    void onNotify();
    void onNewBlockArrived(std::size_t blockNumber);

private:
    std::vector<SosFilter> filters_;
    std::vector<SosFilterController*> controllers_;
    std::size_t processed_;
    DecodedAudioReciever *reciever_;
    std::size_t notifyInterval_;
    QByteArray *buffer_;
    QBuffer *ab_;
    std::map<std::size_t, std::size_t> blocksCalculated_;


};


#endif //EQULIZER_AUDIOPROCESSOR_H
