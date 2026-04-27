#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "ScoreboardViewModel.hpp"
#include "UdpReceiver.hpp"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    // Create the view model that contains the bowling game state.
    ScoreboardViewModel *viewModel = new ScoreboardViewModel(&app);

    // Create the UDP receiver that accepts incoming pin count updates.
    UdpReceiver *receiver = new UdpReceiver(45454, &app);

    // Connect the network layer to the view model.
    // Valid roll values received over UDP are forwarded into the model.
    QObject::connect(receiver, &UdpReceiver::rollReceived,
                     viewModel, &ScoreboardViewModel::roll);

    // Expose the view model to QML under the name "bowlingVM".
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("bowlingVM", viewModel);

    const QUrl url(u"qrc:/Bowling/src/ui/Main.qml"_qs);
    engine.load(url);

    return app.exec();
}
