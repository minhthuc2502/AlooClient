#include "userInfo.h"

userInfo::userInfo() {
    nickName = "";
    age = 0;
    idSocket = NULL;
    avatar = NULL;
}

void userInfo::setNickName(QString name) {
    nickName = name;
}

void userInfo::setAge(quint8 a) {
    age = a;
}

void userInfo::setSocketId(QTcpSocket *socket) {
    idSocket = socket;
}

QTcpSocket* userInfo::getSocketId() {
    return idSocket;
}

QString userInfo::getNickName() {
    return nickName;
}