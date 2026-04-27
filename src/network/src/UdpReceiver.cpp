#include "UdpReceiver.hpp"
#include <QNetworkDatagram>

/**
 * @brief Construct and bind the UDP receiver socket.
 */
UdpReceiver::UdpReceiver(uint16_t port, QObject *parent) : QObject(parent) {
    m_udpSocket = new QUdpSocket(this);
    
    bool success = m_udpSocket->bind(QHostAddress::LocalHost, port, QUdpSocket::ShareAddress);
    
    if (success) {
        connect(m_udpSocket, &QUdpSocket::readyRead, this, &UdpReceiver::processPendingDatagrams);
        emit statusMessage(QString("Listening on port %1").arg(port));
    } else {
        emit statusMessage("Failed to bind UDP port!");
    }
}

uint16_t UdpReceiver::localPort() const {
    return m_udpSocket ? m_udpSocket->localPort() : 0;
}

/**
 * @brief Process any pending datagrams on the UDP socket.
 */
void UdpReceiver::processPendingDatagrams() {
    while (m_udpSocket->hasPendingDatagrams()) {
        QNetworkDatagram datagram = m_udpSocket->receiveDatagram();
        QByteArray data = datagram.data().trimmed();
        
        // Robust protocol parsing: support both numeric values and "ROLL <n>" strings.
        bool ok;
        int pins = -1;
        
        if (data.startsWith("ROLL ")) {
            pins = data.mid(5).toInt(&ok);
        } else {
            pins = data.toInt(&ok);
        }

        if (ok && pins >= 0 && pins <= 10) {
            emit rollReceived(pins);
        } else {
            emit statusMessage("Received invalid data: " + QString(data));
        }
    }
}
