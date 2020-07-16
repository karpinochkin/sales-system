#include <QGuiApplication>
#include "appstarter.h"
#include <memory>

int main(int argc, char *argv[])
{
    QCoreApplication::setOrganizationName("Sales");
    QCoreApplication::setApplicationName("Sales Client");
//    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

#ifdef Q_OS_ANDROID
     qApp->setQuitOnLastWindowClosed(false);  // не должно закрываться при сворачивании
#endif

    auto appStarter = std::make_unique<AppStarter>();

    return app.exec();
}
