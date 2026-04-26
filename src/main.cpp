#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "ScoreboardViewModel.hpp"
#include "UdpReceiver.hpp"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    // 1. 创建业务逻辑层（ViewModel）
    ScoreboardViewModel *viewModel = new ScoreboardViewModel(&app);

    // 2. 创建网络层（Receiver）
    UdpReceiver *receiver = new UdpReceiver(45454, &app);

    // 3. 核心链接：网络层 -> 逻辑层
    // 当 UDP 收到球数，直接喂给 ViewModel，ViewModel 会处理后续计分并通知 QML
    QObject::connect(receiver, &UdpReceiver::rollReceived, 
                     viewModel, &ScoreboardViewModel::roll);

    // 4. 将实例化好的 viewModel 注入 QML 上下文
    // 这样在 QML 里就不需要自己实例对象了，直接用 "bowlingVM" 这个名字
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("bowlingVM", viewModel);

    const QUrl url(u"qrc:/Bowling/src/ui/Main.qml"_qs);
    engine.load(url);

    return app.exec();
}