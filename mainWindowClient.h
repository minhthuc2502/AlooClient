#ifndef MAINWINDOWCLIENT_H
#define MAINWINDOWCLIENT_H

#include <QtWidgets>
#include <QtNetwork>
#include <userInfo.h>
#include <formLogin.h>
#include "ui_mainWindowClient.h"

class mainWindowClient : public QWidget, private Ui::mainWindowClient {
    Q_OBJECT
public:
    mainWindowClient();
    void sendImageToServer();
    void sendInfoUserToServer();
private slots:
    void pressConnectButton();
    void pressDisconnectButton();
    void connected();
    void disconnected();
    void readMessage();
    void sendMessageByEnter();
    void sendMessage();
    void errorSocket(QAbstractSocket::SocketError err);
    void getInfoUser();
private:
    userInfo user;
    formLogin *fLogin;
    quint16 size;
};

#endif // MAINWINDOWCLIENT_H
