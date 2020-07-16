#include <QCoreApplication>
#include <QSettings>
#include <QDebug>
#include "include/SalesServer/QServerLoader/qserverloader.h"
#include <memory.h>

QUnDataBaseSettings getDBSettings()
{
    QUnDataBaseSettings dbSettings;
    dbSettings.type = "QMYSQL";
    dbSettings.host = "127.0.0.1";
    dbSettings.dataBaseName = "db_salesUsers";
    dbSettings.port = 3306;
    dbSettings.login = "root";
    dbSettings.password = "password";

    return dbSettings;
}

int main(int argc, char *argv[])
{
    qDebug()<<"Start Sales System server";

    QCoreApplication a(argc, argv);
    QSettings *settings = new QSettings("salesSystem", "SalesServer");
    auto loader = new QServerLoader(settings, &a);

    QUnDataBaseSettings currentSettingsUnDB = getDBSettings();

    loader->setServerPort(32004);
    loader->setDBSettings(currentSettingsUnDB);
    loader->start();

    return a.exec();
}
