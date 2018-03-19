#include <QtConcurrent/QtConcurrent>
#include "AudioProcessor.h"

AudioProcessor::AudioProcessor(DecodedAudioReciever *reciever,
                               QBuffer *audioBuffer,
                               std::vector<SosFilter> filters,
                               QObject *parent)
        : QObject{parent},
          reciever_{reciever},
          audioBuffer_{audioBuffer},
          buffer_{audioBuffer->buffer()},
          filters_{std::move(filters)} {
}

void AudioProcessor::onNotify() {

    auto getFrames = [this](const SosFilter &filter) {
        auto iter = reciever_->at<const QAudioBuffer::S16S>(processed);
        std::vector<QAudioBuffer::S16S> frames;
        frames.reserve(format.framesForDuration(notifyInterval * 1000));
        for (auto i = 0; i < frames.size(); ++i) {
            const QAudioBuffer::S16S frame = filter.processFrame<QAudioBuffer::S16S>(*iter);
            frames.push_back(std::move(frame));
            ++iter;
        }
        return std::move(frames);
    };

    auto mergeFrames = [](std::vector<QAudioBuffer::S16S> &result, const std::vector<QAudioBuffer::S16S> &frames) {
        if (result.size() == 0) {
            result.reserve(frames.size());
            for (auto &&i: frames) {
                result.push_back(i);
            }
            return;
        }
        for (std::size_t i = 0; i < frames.size(); ++i) {
            result[i].left += frames[i].left;
            result[i].right += frames[i].right;
        }
    };

    QFuture<std::vector<QAudioBuffer::S16S>> future = QtConcurrent::mappedReduced(
            &filters_,
            getFrames,
            mergeFrames
    );

    future.waitForFinished();
    auto res = future.result();
    buffer_.replace(0,
                    res.size() * format.bytesPerFrame(),
                    reinterpret_cast<const char *>(res.data()),
                    res.size() * format.bytesPerFrame());
}

void AudioProcessor::configure(QAudioOutput *output) {
    format = output->format();
    notifyInterval = output->notifyInterval();

}
