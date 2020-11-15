#ifndef FORMLOGIN_H
#define FORMLOGIN_H

#include <QtWidgets>
#include "ui_formUser.h"

class formLogin : public QDialog, private Ui::formUser {
    Q_OBJECT
public:
    formLogin();
    QString getName();
    quint8 getAge();
private slots:
    void HandleCloseButton();
    void saveInfo();
    void addAvatar();
signals:
    void clickedCloseButton();
private:
    QString name;
    quint8 age;
    QPixmap avatar;
};
#endif // FORMLOGIN_H
