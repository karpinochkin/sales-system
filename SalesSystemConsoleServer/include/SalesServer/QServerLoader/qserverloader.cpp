#include "qserverloader.h"
QServerLoader::QServerLoader(QSettings *settings, QObject *parent)
    : QObject(parent),
      currentSettings(settings)
{
    qDebug()<<"Server loader start";
}

QServerLoader::~QServerLoader()
{

}

void QServerLoader::setDBSettings(QUnDataBaseSettings &settingsDB)
{
    currentSettingsUnDB = settingsDB;
}

void QServerLoader::start()
{
    if (server == nullptr) {
        server = new QUnNetProtokolServer(currentSettingsUnDB,
                                          currentPort,
                                          currentSettings,
                                          this);

        connect(server, &QUnNetProtokolServer::signalStartServer,
                this,   &QServerLoader::slotServerStarted);
        connect(server, &QUnNetProtokolServer::signalStopServer,
                this,   &QServerLoader::slotServerStoped);
        connect(server, &QUnNetProtokolServer::signalNewConnection,
                this,   &QServerLoader::slotNewConnection);

        server->start();
    }
}

void QServerLoader::stop()
{
    if (server != nullptr) {
        server->stop();
        delete server;
        server = nullptr;
    }
}

void QServerLoader::setServerPort(int port)
{
    currentPort = port;
}

void QServerLoader::slotServerStarted()
{
    pluginSales = new Plugins::QSalesServerPlugin(server, 0x08, this);
    QDataBaseSettings settingsDB;
    settingsDB.type = QDataBaseSettings::typeQMYSQL;
    settingsDB.host = "127.0.0.1";
    settingsDB.dataBaseName = "db_sales";
    settingsDB.port = 3306;
    settingsDB.login = "root";
    settingsDB.password = "password";

    pluginSales->initExtDataBase(settingsDB);
    emit signalServerStarted();
}

void QServerLoader::slotServerStoped()
{
    delete pluginSales;
    emit signalServerStoped();
}

void QServerLoader::slotNewConnection(QUnClientHandler *client)
{
    clients.push_back(client);
    connect(client, &QUnClientHandler::signalDisconnected,
            this, &QServerLoader::slotClientDisconnected);
}

void QServerLoader::slotClientDisconnected()
{
    QUnClientHandler *client = static_cast<QUnClientHandler*>(QObject::sender());
    qDebug()<<client->getCurrentAccountInfo()->login<<":"<<" CLient disconnected: "<<client;

    removeClient(client);
}

void QServerLoader::removeClient(QUnClientHandler *client)
{
    int pos = clients.indexOf(client, 0);

    if (pos >= 0) {
        clients.remove(pos,1);
    }
}
