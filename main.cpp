#define kiss_fft_scalar double

#include <iostream>
#include <QtCore/QCoreApplication>
#include <QtCore/QThread>
#include <QtWidgets/QApplication>
#include <QtQml/QQmlApplicationEngine>
#include "src/AudioPlayer.h"
#include "src/AudioPlayerController.h"
#include "filters/fdacoefs.h"
#include "src/Echo.h"
#include "src/Overdrive.h"
#include <QQmlContext>
#include "QDebug"
int main(int argc, char **argv) {
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);
    QQmlApplicationEngine engine;


    std::vector<Filter<3, 3, real64_T, real64_T >> filters;
    filters.emplace_back(NUM_BAND_1, DEN_BAND_1, MWSPT_NSEC_1);
    filters.emplace_back(NUM_BAND_2, DEN_BAND_2, MWSPT_NSEC_2);
    filters.emplace_back(NUM_BAND_3, DEN_BAND_3, MWSPT_NSEC_3);
    filters.emplace_back(NUM_BAND_4, DEN_BAND_4, MWSPT_NSEC_4);
    filters.emplace_back(NUM_BAND_5, DEN_BAND_5, MWSPT_NSEC_5);
    filters.emplace_back(NUM_BAND_6, DEN_BAND_6, MWSPT_NSEC_6);
    filters.emplace_back(NUM_BAND_7, DEN_BAND_7, MWSPT_NSEC_7);
    filters.emplace_back(NUM_BAND_8, DEN_BAND_8, MWSPT_NSEC_8);
    filters.emplace_back(NUM_BAND_9, DEN_BAND_9, MWSPT_NSEC_9);
    filters.emplace_back(NUM_BAND_10, DEN_BAND_10, MWSPT_NSEC_10);
    filters.emplace_back(NUM_BAND_11, DEN_BAND_11, MWSPT_NSEC_11);
    filters.emplace_back(NUM_BAND_12, DEN_BAND_12, MWSPT_NSEC_12);
//    filters.emplace_back(NUM_BAND_13, DEN_BAND_13, MWSPT_NSEC_13);


    AudioPlayer *player = new AudioPlayer(std::move(filters));


    Effect<stk::StkFloat> *echo = new Echo<stk::StkFloat>(100, player->getSampleRate());
    player->registerEffect("echo", echo);
    player->registerEffect("overdrive", new Overdrive<stk::StkFloat>(1. / 3, 2. / 3));

    AudioController *controller = new AudioController(player, &app);
    engine.load(QUrl{"qrc:///main.qml"});

    QQmlContext *context = engine.rootContext();

    context->setContextProperty("audioController", controller);
    context->setContextProperty("audioSpectrum", player->getSpectrum());

    QObject *window = engine.rootObjects()[0];


    QObject::connect(player, SIGNAL(inputSpectrumUpdate()),
                     window, SLOT(updateInput()));

    QObject::connect(player, SIGNAL(outputSpectrumUpdate()),
                     window, SLOT(updateOutput()));

    return app.exec();
}