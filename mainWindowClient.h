#ifndef MAINWINDOWCLIENT_H
#define MAINWINDOWCLIENT_H


#include <QtWidgets>
#include <QtNetwork>
#include "ui_mainWindowClient.h"

class mainWindowClient : public QWidget, private Ui::mainWindowClient {
    Q_OBJECT
public:
    mainWindowClient();
private slots:
    void pressConnectButton();
    void pressDisconnectButton();
    void connected();
    void disconnected();
    void readMessage();
    void sendMessageByEnter();
    void sendMessage();
    void errorSocket(QAbstractSocket::SocketError err);
private:
    QTcpSocket *socket;
    quint16 size;
};

#endif // MAINWINDOWCLIENT_H
