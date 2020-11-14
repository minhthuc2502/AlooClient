#include <QApplication>
#include <mainWindowClient.h>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    mainWindowClient window;
    window.show();
    return app.exec();
}
