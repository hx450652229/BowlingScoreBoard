#include "UdpReceiver.hpp"

#include <QCoreApplication>
#include <QEventLoop>
#include <QTimer>
#include <QUdpSocket>

#include <gtest/gtest.h>

static void waitForSignalOrTimeout(QEventLoop &loop, QTimer &timer, int timeoutMs = 500)
{
    timer.setSingleShot(true);
    timer.start(timeoutMs);
    loop.exec();
}

TEST(UdpReceiverTest, EmitsRollReceivedForNumericPayload)
{
    UdpReceiver receiver(0);
    QUdpSocket sender;
    ASSERT_TRUE(sender.bind(QHostAddress::LocalHost, 0));

    const uint16_t port = receiver.localPort();
    ASSERT_NE(port, 0u);

    int receivedPins = -1;
    QObject::connect(&receiver, &UdpReceiver::rollReceived, [&](int pins) { receivedPins = pins; });

    QEventLoop loop;
    QTimer timer;
    QObject::connect(&receiver, &UdpReceiver::rollReceived, &loop, &QEventLoop::quit);
    QObject::connect(&timer, &QTimer::timeout, &loop, &QEventLoop::quit);

    const qint64 bytes = sender.writeDatagram("10", QHostAddress::LocalHost, port);
    ASSERT_EQ(bytes, 2);
    waitForSignalOrTimeout(loop, timer);

    EXPECT_EQ(receivedPins, 10);
}

TEST(UdpReceiverTest, EmitsRollReceivedForRollCommand)
{
    UdpReceiver receiver(0);
    QUdpSocket sender;
    ASSERT_TRUE(sender.bind(QHostAddress::LocalHost, 0));

    const uint16_t port = receiver.localPort();
    ASSERT_NE(port, 0u);

    int receivedPins = -1;
    QObject::connect(&receiver, &UdpReceiver::rollReceived, [&](int pins) { receivedPins = pins; });

    QEventLoop loop;
    QTimer timer;
    QObject::connect(&receiver, &UdpReceiver::rollReceived, &loop, &QEventLoop::quit);
    QObject::connect(&timer, &QTimer::timeout, &loop, &QEventLoop::quit);

    const qint64 bytes = sender.writeDatagram("ROLL 7", QHostAddress::LocalHost, port);
    ASSERT_EQ(bytes, 6);
    waitForSignalOrTimeout(loop, timer);

    EXPECT_EQ(receivedPins, 7);
}

TEST(UdpReceiverTest, EmitsRollReceivedForLowercaseRollCommand)
{
    UdpReceiver receiver(0);
    QUdpSocket sender;
    ASSERT_TRUE(sender.bind(QHostAddress::LocalHost, 0));

    const uint16_t port = receiver.localPort();
    ASSERT_NE(port, 0u);

    int receivedPins = -1;
    QObject::connect(&receiver, &UdpReceiver::rollReceived, [&](int pins) { receivedPins = pins; });

    QEventLoop loop;
    QTimer timer;
    QObject::connect(&receiver, &UdpReceiver::rollReceived, &loop, &QEventLoop::quit);
    QObject::connect(&timer, &QTimer::timeout, &loop, &QEventLoop::quit);

    const qint64 bytes = sender.writeDatagram("roll 5", QHostAddress::LocalHost, port);
    ASSERT_EQ(bytes, 6);
    waitForSignalOrTimeout(loop, timer);

    EXPECT_EQ(receivedPins, 5);
}

TEST(UdpReceiverTest, EmitsErrorOccurredForInvalidPayload)
{
    UdpReceiver receiver(0);
    QUdpSocket sender;
    ASSERT_TRUE(sender.bind(QHostAddress::LocalHost, 0));

    const uint16_t port = receiver.localPort();
    ASSERT_NE(port, 0u);

    QString errorMessage;
    QObject::connect(&receiver, &UdpReceiver::errorOccurred, [&](const QString &msg) { errorMessage = msg; });

    QEventLoop loop;
    QTimer timer;
    QObject::connect(&receiver, &UdpReceiver::errorOccurred, &loop, &QEventLoop::quit);
    QObject::connect(&timer, &QTimer::timeout, &loop, &QEventLoop::quit);

    const qint64 bytes = sender.writeDatagram("BAD DATA", QHostAddress::LocalHost, port);
    ASSERT_EQ(bytes, 8);
    waitForSignalOrTimeout(loop, timer);

    EXPECT_EQ(errorMessage, "Payload is not a valid pin count");
}

int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
