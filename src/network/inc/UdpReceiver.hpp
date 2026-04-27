#pragma once

#include <QObject>
#include <QUdpSocket>
#include <QHostAddress>

/**
 * @file UdpReceiver.hpp
 * @brief UDP receiver declarations for bowling pin count input.
 */

/**
 * @brief UDP receiver that parses incoming bowling roll data.
 *
 * This class listens on a UDP port and emits signals when valid pin counts
 * are received or when network status changes.
 */
class UdpReceiver : public QObject {
    Q_OBJECT
public:
    /**
     * @brief Construct a UdpReceiver instance.
     * @param port Local UDP port to bind.
     * @param parent Optional QObject parent.
     */
    UdpReceiver(uint16_t port = 45454, QObject *parent = nullptr);

    /**
     * @brief Get the local port bound by the UDP socket.
     * @return Bound port number or zero if unbound.
     */
    uint16_t localPort() const;

signals:
    /**
     * @brief Emitted when a valid pin count is parsed from UDP.
     * @param pins Number of pins reported by the remote sender.
     */
    void rollReceived(int pins);

    /**
     * @brief Emitted when network or parsing status changes.
     * @param msg Status description.
     */
    void statusMessage(QString msg);

private slots:
    void processPendingDatagrams();

private:
    QUdpSocket *m_udpSocket = nullptr; /**< Underlying UDP socket instance. */
};
