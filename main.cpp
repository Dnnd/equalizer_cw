#include <iostream>
#include <QtCore/QCoreApplication>
#include <QtCore/QThread>
#include <QtWidgets/QApplication>
#include <QtQml/QQmlApplicationEngine>
#include "src/AudioPlayer.h"
#include "src/AudioPlayerController.h"
#include "filters/fdacoefs.h"
#include <QQmlContext>

int main(int argc, char **argv) {
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);
    QQmlApplicationEngine engine;


    std::vector<Filter<3, 3, real64_T, real64_T >> filters;
    filters.emplace_back(NUM_BAND_1, DEN_BAND_1, MWSPT_NSEC);
    filters.emplace_back(NUM_BAND_2, DEN_BAND_2, MWSPT_NSEC);
    filters.emplace_back(NUM_BAND_3, DEN_BAND_3, MWSPT_NSEC);
    filters.emplace_back(NUM_BAND_4, DEN_BAND_4, MWSPT_NSEC);
    filters.emplace_back(NUM_BAND_5, DEN_BAND_5, MWSPT_NSEC);
    filters.emplace_back(NUM_BAND_6, DEN_BAND_6, MWSPT_NSEC);
    filters.emplace_back(NUM_BAND_7, DEN_BAND_7, MWSPT_NSEC);

    AudioPlayer *player = new AudioPlayer(std::move(filters));


    AudioController *controller = new AudioController(player, &app);
    QQmlContext *context = engine.rootContext();

    context->setContextProperty("audioController", controller);

    engine.load(QUrl{"qrc:///main.qml"});

    controller->play("sample.wav");


    return app.exec();
}