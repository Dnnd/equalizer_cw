#include "SosFilterController.h"


void SosFilterController::onNewBlock(std::vector<SecondOrderSection<CoeffType>::CalcFrame> block_) {
    blockChain_.push(std::move(block_));
    ++blockNumber_;
    emit newBlockArrived(blockNumber_);
}

SosFilterController::SosFilterController(SosFilter &filter, QObject *parent)
        : filter{filter},
          QObject{parent} {

}

SosFilterController::FrameBlock SosFilterController::takeBlock() {
    auto top = blockChain_.front();
    blockChain_.pop();
    return std::move(top);
}
