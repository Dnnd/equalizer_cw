#include "DecodedAudioReciever.h"

DecodedAudioReciever::DecodedAudioReciever(QAudioDecoder *decoder, QObject *parent)
        : decoder_{decoder},
          QObject{parent} {

}

void DecodedAudioReciever::recieve() {
    QObject::connect(decoder_, &QAudioDecoder::bufferReady, this, &DecodedAudioReciever::recieveBuffer);

    QObject::connect(decoder_, &QAudioDecoder::finished, [this] {
        emit finished();
    });

    decoder_->start();
}

void DecodedAudioReciever::recieveBuffer() {
    decodedBuffers_.emplace_back(decoder_->read());
}

