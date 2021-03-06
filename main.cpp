#include <QApplication>
#include <mainWindowClient.h>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    mainWindowClient window;
    window.show();

    QObject::connect(&window, SIGNAL(destroyed(QObject*)), &app, SLOT(quit()));
    return app.exec();
}
