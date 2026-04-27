#include "UdpReceiver.hpp"
#include "UdpProtocol.hpp"

#include <QNetworkDatagram>

UdpReceiver::UdpReceiver(uint16_t port, const QHostAddress &bindAddress, QObject *parent) : QObject(parent)
{
    m_udpSocket = new QUdpSocket(this);

    const bool success = m_udpSocket->bind(bindAddress, port, QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint);

    if (success)
    {
        connect(m_udpSocket, &QUdpSocket::readyRead, this, &UdpReceiver::processPendingDatagrams);
        emit statusMessage(QStringLiteral("Listening on %1:%2").arg(bindAddress.toString()).arg(port));
    }
    else
    {
        emit errorOccurred(QStringLiteral("Failed to bind UDP port %1:%2").arg(bindAddress.toString()).arg(port));
    }
}

uint16_t UdpReceiver::localPort() const
{
    return m_udpSocket ? m_udpSocket->localPort() : 0;
}

void UdpReceiver::processPendingDatagrams()
{
    while (m_udpSocket->hasPendingDatagrams())
    {
        const QNetworkDatagram datagram = m_udpSocket->receiveDatagram();
        const auto parseResult = Bowling::Network::parseUdpMessage(datagram.data());

        if (parseResult.isValid())
        {
            emit rollReceived(parseResult.message->pins);
        }
        else
        {
            emit errorOccurred(parseResult.error);
        }
    }
}
