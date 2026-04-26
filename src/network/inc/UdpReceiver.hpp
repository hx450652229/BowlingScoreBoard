#pragma once

#include <QObject>
#include <QUdpSocket>
#include <QHostAddress>

class UdpReceiver : public QObject {
    Q_OBJECT
public:
    UdpReceiver(uint16_t port = 45454, QObject *parent = nullptr);

signals:
    // 当解析出有效的投球数时发出
    void rollReceived(int pins);
    // 用于通知 UI 网络状态（可选）
    void statusMessage(QString msg);

private slots:
    void processPendingDatagrams();

private:
    QUdpSocket *m_udpSocket = nullptr;
};