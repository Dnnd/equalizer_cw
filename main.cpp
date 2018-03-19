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

    QObject::connect(&reciever, &DecodedAudioReciever::finished, [&] {

        for (auto i = reciever.begin<QAudioBuffer::S16S>();
             i != reciever.at<QAudioBuffer::S16S>(format.framesForDuration(100 * 1000)); ++i) {
            bytea.append(toChar(*i), format.bytesPerFrame());
        }

        QBuffer *od = new QBuffer{&bytea};

        od->open(QBuffer::ReadWrite);

        std::vector<SosFilter> filters;
        filters.emplace_back(NUM, DEN, MWSPT_NSEC);

        AudioProcessor *proc = new AudioProcessor(&reciever, od, std::move(filters), &app);

        QObject::connect(&audioOutput, &QAudioOutput::notify, proc, &AudioProcessor::onNotify);

        audioOutput.start(od);
        audioOutput.setNotifyInterval(100);
    });


    reciever.recieve();


    return app.exec();
}