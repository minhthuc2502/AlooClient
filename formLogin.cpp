#include "formLogin.h"

formLogin::formLogin() {
    setupUi(this);

    connect(closeButton, SIGNAL(clicked()), this, SLOT(HandleCloseButton()));
    connect(confirmButton, SIGNAL(clicked()), this, SLOT(saveInfo()));
}

void formLogin::saveInfo() {
    name = nameLineEdit->text();
    age = ageSpinBox->value();
}

QString formLogin::getName() {
    return name;
}

quint8 formLogin::getAge() {
    return age;
}

void formLogin::HandleCloseButton() {
    this->close();
    emit clickedCloseButton();
}
