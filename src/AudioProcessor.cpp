#include <QtConcurrent/QtConcurrent>
#include "AudioProcessor.h"

AudioProcessor::AudioProcessor(DecodedAudioReciever *reciever,
                               QByteArray *audioBuffer,
                               QBuffer *ab,
                               std::vector<SosFilter> filters,
                               std::size_t notifyInterval,
                               QObject *parent)
        : QObject{parent},
          filters_{std::move(filters)},
          notifyInterval_{notifyInterval},
          processed_{0},
          ab_{ab},
          reciever_{reciever},
          buffer_{audioBuffer} {
    for (auto &&filter : filters_) {
        filter.setBufferSize(reciever->format().framesForDuration(notifyInterval * 1000));
        controllers_.push_back(new SosFilterController{filter, this});
    }
    for (auto &&controller: controllers_) {
        QObject::connect(controller, &SosFilterController::newBlockArrived, this, &AudioProcessor::onNewBlockArrived);
    }

}

void AudioProcessor::onNotify() {

    using Frame = QAudioBuffer::S16S;
    auto from = reciever_->at<Frame>(processed_);
    auto end = reciever_->at<Frame>(processed_ + reciever_->format().framesForDuration(notifyInterval_ * 1000));

    auto taskProducer = [from, end](auto &filter) {
        return [&filter, from, end] {
            for (auto i = from; i != end; ++i) {
                filter.processFrame(*i);
            }
            return filter.harvest();
        };
    };

    using FrameBlock_t = std::vector<SecondOrderSection<CoeffType>::CalcFrame>;
    for (auto i = 0; i < filters_.size(); ++i) {
        auto task = taskProducer(filters_[i]);
        auto *watcher = new QFutureWatcher<FrameBlock_t>();
        QFuture<FrameBlock_t> future = QtConcurrent::run(task);

        QObject::connect(watcher, &QFutureWatcher<FrameBlock_t>::finished, controllers_[i], [this, watcher, i] {
            auto block = watcher->result();
            controllers_[i]->onNewBlock(std::move(block));
        });

        QObject::connect(watcher, &QFutureWatcher<FrameBlock_t>::finished, &QObject::deleteLater);
        watcher->setFuture(future);
    }

}

void AudioProcessor::onNewBlockArrived(std::size_t blockNumber) {

    auto blockPtr = blocksCalculated_.find(blockNumber);

    if (blockPtr == blocksCalculated_.end()) {
        blockPtr = blocksCalculated_.emplace(blockNumber, 1).first;
    }

    if (blockPtr->second == filters_.size()) {
        summarize(blockNumber);
        blocksCalculated_.erase(blockPtr);
    }
}

void AudioProcessor::summarize(std::size_t blockNumber) {

    using FrameBlock = std::vector<SecondOrderSection<CoeffType>::CalcFrame>;

    using Frame = QAudioBuffer::S16S;
    std::vector<Frame> output;
    auto format = reciever_->format();

    output.resize(format.framesForDuration(notifyInterval_ * 1000));

    for (auto &&controller:controllers_) {
        FrameBlock block = controller->takeBlock();
        for (std::size_t i = 0; i < output.size(); ++i) {

            output[i].left += block[i].left;
            output[i].right += block[i].right;
        }
    }
    processed_ += format.framesForDuration(notifyInterval_ * 1000);
    ab_->seek(0);
    ab_->write((const char *) output.data(), format.bytesForDuration(notifyInterval_ * 1000));
    ab_->seek(0);

}
