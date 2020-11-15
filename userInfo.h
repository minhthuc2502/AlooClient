#ifndef USERINFO_H
#define USERINFO_H

#include <stdio.h>
#include <QDataStream>
#include <QtNetwork>
class userInfo {
public:
    userInfo();
    void setNickName(QString name);
    void setAge(quint8 a);
    void setSocketId(QTcpSocket *socket);

    QTcpSocket* getSocketId();
    QString getNickName();
private:
    QString nickName;
    quint8 age;
    QTcpSocket *idSocket;
    QImage *avatar;
};

#endif // USERINFO_H
