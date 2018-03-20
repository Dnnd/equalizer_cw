#ifndef EQULIZER_FILTERCONTROLLER_H
#define EQULIZER_FILTERCONTROLLER_H


#include "AudioProcessor.h"
#include <QQueue>
#include <queue>


class SosFilterController: public QObject {
    Q_OBJECT
public:
    using FrameBlock = std::vector<SecondOrderSection<CoeffType >::CalcFrame>;

    explicit SosFilterController(Filter<3, 3> &filter, QObject *parent);


    FrameBlock takeBlock();

public slots:
    void onNewBlock(std::vector<SecondOrderSection<CoeffType >::CalcFrame> block_);

signals:
    void newBlockArrived(std::size_t blockNumber);

private:
    Filter<3, 3> &filter;
    std::queue<std::vector<SecondOrderSection<CoeffType >::CalcFrame>> blockChain_;
    std::size_t blockNumber_{0};

};


#endif //EQULIZER_FILTERCONTROLLER_H
