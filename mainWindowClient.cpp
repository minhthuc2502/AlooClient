#include "mainWindowClient.h"

mainWindowClient::mainWindowClient() : QWidget(){
    setupUi(this);
    // set feature for some widgets
    logoLabel->setPixmap(QPixmap(QApplication::applicationDirPath() + "/../AlooClient/img/iconApp.png"));
    chatZone->setEnabled(false);

    QTcpSocket *socket = new QTcpSocket(this);
    user.setSocketId(socket);

    connect(user.getSocketId(), SIGNAL(connected()), this, SLOT(connected()));
    connect(user.getSocketId(), SIGNAL(readyRead()), this, SLOT(readMessage()));
    connect(user.getSocketId(), SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(user.getSocketId(), SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(errorSocket(QAbstractSocket::SocketError)));

    connect(ConnectButton, SIGNAL(clicked()), this, SLOT(pressConnectButton()));
    connect(disconnectButton, SIGNAL(clicked(bool)), this, SLOT(pressDisconnectButton()));
    connect(sendButton, SIGNAL(clicked()), this, SLOT(sendMessage()));
    connect(zoneMessage, SIGNAL(returnPressed()), this, SLOT(sendMessageByEnter()));

    size = 0;
}

void mainWindowClient::pressConnectButton() {
    // open form get info user
    fLogin = new formLogin();
    connect(fLogin, SIGNAL(clickedCloseButton()), this, SLOT(getInfoUser()));
    fLogin->setModal(true);
    fLogin->show();
}

void mainWindowClient::pressDisconnectButton() {
    user.getSocketId()->abort();
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

    user.getSocketId()->write(packageMessage);

    zoneMessage->clear();
    zoneMessage->setFocus(); // cursor of keyboard focus here
}

void mainWindowClient::sendMessageByEnter() {
    sendMessage();
}

void mainWindowClient::readMessage() {
    QDataStream in(user.getSocketId());

    if (size == 0) {
        if (user.getSocketId()->bytesAvailable() < (int)sizeof(quint16)) {
            return;
        }
        in >> size;
    }

    if (user.getSocketId()->bytesAvailable() < size) {
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
    nickName->setEnabled(true);
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
            chatZone->append(tr("<em>Error: ") + user.getSocketId()->errorString() + tr("</em>"));
    }

    ConnectButton->setEnabled(true);
}

void mainWindowClient::getInfoUser() {
    // get info user
    user.setNickName(fLogin->getName());
    user.setAge(fLogin->getAge());

    nickName->setText(user.getNickName());
    nickName->setEnabled(false);

    // setup connection
    chatZone->append(tr("<em>Connecting to server...</em>"));
    ConnectButton->setEnabled(false);

    user.getSocketId()->abort();
    user.getSocketId()->connectToHost(ipAddresse->text(), portSpinBox->value());
}
