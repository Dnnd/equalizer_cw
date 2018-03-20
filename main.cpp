#include <QApplication>
#include <QQmlApplicationEngine>
#include <QAudioDecoder>
#include <QAudioDeviceInfo>
#include <QtMultimedia/QAudioOutput>
#include <QDataStream>
#include <QtCore/QBuffer>
#include <QtCore/QTimer>
#include "src/DecodedAudioReciever.h"
#include "src/Filter.h"
#include "src/AudioProcessor.h"

template<typename Data>
const char *toChar(Data &d) {
    return reinterpret_cast<const char *>(&d);
}

int main(int argc, char *argv[]) {
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);
    QQmlApplicationEngine engine;
    engine.load(QUrl{"qrc:///main.qml"});

    QAudioDecoder decoder{};
    QAudioFormat format = QAudioDeviceInfo::defaultOutputDevice().preferredFormat();

    decoder.setAudioFormat(format);
    decoder.setSourceFilename("/home/danm/14_Magika.wav");

    DecodedAudioReciever reciever{&decoder, &app};

    QAudioOutput audioOutput{decoder.audioFormat()};

    QByteArray bytea;
    bytea.resize(format.bytesForDuration(100 * 1000));

    QObject::connect(&reciever, &DecodedAudioReciever::finished, [&] {

        QBuffer *od = new QBuffer{&bytea};

        od->open(QBuffer::ReadWrite);

        std::vector<SosFilter> filters;
        filters.emplace_back(NUM, DEN, MWSPT_NSEC);
        qDebug() << "PROC IN DA HOUSE";

        AudioProcessor *proc = new AudioProcessor(&reciever, &bytea, od, std::move(filters),100, &app);

        QObject::connect(&audioOutput, &QAudioOutput::notify, proc, &AudioProcessor::onNotify);

        audioOutput.setNotifyInterval(100);


        audioOutput.start(od);
        proc->onNotify();
    });


    reciever.recieve();


    return app.exec();
}