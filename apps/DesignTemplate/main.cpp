#include <QApplication>
#include <QGuiApplication>

#include "splashscreen.h"

using namespace VitragesDecision;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    SplashScreen w;
    w.show();

    return a.exec();
}
