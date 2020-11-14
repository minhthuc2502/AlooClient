#include "mainWindowClient.h"

mainWindowClient::mainWindowClient() : QWidget(){
    setupUi(this);
    // set feature for some widgets
    logoLabel->setPixmap(QPixmap(QApplication::applicationDirPath() + "/../AlooClient/img/iconApp.png"));
    chatZone->setEnabled(false);

    socket = new QTcpSocket(this);
    connect(socket, SIGNAL(connected()), this, SLOT(connected()));
    connect(socket, SIGNAL(readyRead()), this, SLOT(readMessage()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(errorSocket(QAbstractSocket::SocketError)));

    connect(ConnectButton, SIGNAL(clicked()), this, SLOT(pressConnectButton()));
    connect(disconnectButton, SIGNAL(clicked(bool)), this, SLOT(pressDisconnectButton()));
    connect(sendButton, SIGNAL(clicked()), this, SLOT(sendMessage()));
    connect(zoneMessage, SIGNAL(returnPressed()), this, SLOT(sendMessageByEnter()));

    size = 0;
}

void mainWindowClient::pressConnectButton() {
    // setup connection
    chatZone->append(tr("<em>Connecting to server...</em>"));
    ConnectButton->setEnabled(false);

    socket->abort();
    socket->connectToHost(ipAddresse->text(), portSpinBox->value());
}

void mainWindowClient::pressDisconnectButton() {
    socket->abort();
}

void mainWindowClient::sendMessage() {
    QByteArray packageMessage;
    QDataStream out(&packageMessage, QIODevice::WriteOnly);

    // setup message
    QString mess = tr("<strong>") + nickName->text() + "</strong> :" + zoneMessage->text();

    out << (quint16) 0;
    out << mess;
    out.device()->seek(0);
    out << (quint16)(packageMessage.size() - sizeof(quint16));

    socket->write(packageMessage);

    zoneMessage->clear();
    zoneMessage->setFocus(); // cursor of keyboard focus here
}

void mainWindowClient::sendMessageByEnter() {
    sendMessage();
}

void mainWindowClient::readMessage() {
    QDataStream in(socket);

    if (size == 0) {
        if (socket->bytesAvailable() < (int)sizeof(quint16)) {
            return;
        }
        in >> size;
    }

    if (socket->bytesAvailable() < size) {
        return;
    }
    QString message;
    in >> message;

    chatZone->append(message);

    size = 0;
}


void mainWindowClient::connected() {
    chatZone->append(tr("<em>Connect successfully !</em>"));
    // theses widgets will be enabled only connection established
    disconnectButton->setEnabled(true);
    chatZone->setEnabled(true);
}

void mainWindowClient::disconnected() {
    chatZone->append(tr("<em>goodbye, see you again !</em>"));
    ConnectButton->setEnabled(true);
    disconnectButton->setEnabled(false);
    chatZone->setEnabled(false);
}

void mainWindowClient::errorSocket(QAbstractSocket::SocketError err) {
    switch(err) {
        case QAbstractSocket::HostNotFoundError:
            chatZone->append(tr("<em>Error: can not connect to host</em>"));
            break;
        case QAbstractSocket::ConnectionRefusedError:
            chatZone->append(tr("<em>Error: Server refuse access</em>"));
            break;
        case QAbstractSocket::RemoteHostClosedError:
            chatZone->append(tr("<em>Error: Server is disconnected</em>"));
            break;
        default:
            chatZone->append(tr("<em>Error: ") + socket->errorString() + tr("</em>"));
    }

    ConnectButton->setEnabled(true);
}
