#include "formLogin.h"

formLogin::formLogin() {
    setupUi(this);

    connect(closeButton, SIGNAL(clicked()), this, SLOT(HandleCloseButton()));
    connect(confirmButton, SIGNAL(clicked()), this, SLOT(saveInfo()));
    connect(addImageButton, SIGNAL(clicked(bool)), this, SLOT(addAvatar()));
}

void formLogin::saveInfo() {
    name = nameLineEdit->text();
    age = ageSpinBox->value();
}

QString formLogin::getName() {
    return name;
}

int formLogin::getAge() {
    return age;
}

QPixmap formLogin::getAvatar() {
    return avatar;
}

void formLogin::HandleCloseButton() {
    this->close();
    emit clickedCloseButton();
}

void formLogin::addAvatar() {
   QString imagePath = QFileDialog::getOpenFileName(this,
                                                    tr("Open File"),
                                                    "",
                                                    tr("JPEG (*.jpg *.jpeg);;PNG (*.png)" ));
   QImage image;
   QImage imageConverted;
   image.load(imagePath);
   imageConverted = image.scaledToHeight(90).scaledToWidth(84);
   avatar = QPixmap::fromImage(imageConverted);
   QGraphicsScene *graphicScene = new QGraphicsScene();
   graphicScene->addPixmap(avatar);
   graphicScene->setSceneRect(avatar.rect());

   avataView->setScene(graphicScene);
}
