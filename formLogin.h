#ifndef FORMLOGIN_H
#define FORMLOGIN_H

#include <QtWidgets>
#include "ui_formUser.h"

class formLogin : public QDialog, private Ui::formUser {
    Q_OBJECT
public:
    formLogin();
    QString getName();
    int getAge();
    QPixmap getAvatar();
private slots:
    void HandleCloseButton();
    void saveInfo();
    void addAvatar();
signals:
    void clickedCloseButton();
private:
    QString name;
    int age;
    QPixmap avatar;
};
#endif // FORMLOGIN_H
