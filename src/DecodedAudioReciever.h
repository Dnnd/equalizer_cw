#ifndef EQULIZER_DECODEDAUDIOBUFFER_H
#define EQULIZER_DECODEDAUDIOBUFFER_H


#include <QtCore/QObject>
#include <QtMultimedia/QAudioDecoder>
#include "DecodedAudioIterator.h"

class DecodedAudioReciever : public QObject {
Q_OBJECT
public:
    DecodedAudioReciever(QAudioDecoder *decoder, QObject *parent = nullptr);

    void recieve();

    template<typename SampleType>
    DecodedAudioIterator<SampleType> begin();

    template<typename SampleType>
    DecodedAudioIterator<SampleType> end();

    template<typename SampleType>
    DecodedAudioIterator<SampleType> at(std::size_t frame);

signals:
    void finished();

protected:
    void recieveBuffer();

private:
    std::vector<QAudioBuffer> decodedBuffers_;
    QAudioDecoder *decoder_;
};

template<typename SampleType>
DecodedAudioIterator<SampleType> DecodedAudioReciever::begin() {
    return DecodedAudioIterator<SampleType>{&decodedBuffers_};
}

template<typename SampleType>
DecodedAudioIterator<SampleType> DecodedAudioReciever::end() {
    return DecodedAudioIterator<SampleType>{nullptr};
}

template<typename SampleType>
DecodedAudioIterator<SampleType> DecodedAudioReciever::at(std::size_t frame) {
    return DecodedAudioIterator<SampleType>{&decodedBuffers_};
}



#endif //EQULIZER_DECODEDAUDIOBUFFER_H
