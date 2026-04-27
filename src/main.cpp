#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "ScoreboardViewModel.hpp"
#include "UdpReceiver.hpp"

namespace
{
constexpr int UDP_RECEIVER_PORT = 45454; /**< Default UDP port for receiving bowling roll data. */
}

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    ScoreboardViewModel *viewModel = new ScoreboardViewModel(&app);
    UdpReceiver *receiver = new UdpReceiver(UDP_RECEIVER_PORT, &app);

    // Connect the network layer to the view model.
    // Valid roll values received over UDP are forwarded into the model.
    QObject::connect(receiver, &UdpReceiver::rollReceived, viewModel, &ScoreboardViewModel::roll);

    // Expose the view model to QML under the name "bowlingVM".
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("bowlingVM", viewModel);

    const QUrl url(u"qrc:/Bowling/src/ui/Main.qml"_qs);
    engine.load(url);

    return app.exec();
}
