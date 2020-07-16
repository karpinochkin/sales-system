#include "qserverplugin.h"

QServerPlugin::QServerPlugin(QUnNetProtokolServer *server, quint16 business, QObject *parent)
    : QObject(parent),
      currentIdBusiness(business),
      currentServer(server)
{
    connect(currentServer, &QUnNetProtokolServer::signalNewConnection,
            this,          &QServerPlugin::slotNewConnection);

    mutexDataBase = new QMutex();

    timerDB = new QTimer(this);
    connect(timerDB, &QTimer::timeout,
            this,    &QServerPlugin::slotTimerDB);
    timerDB->start(21600000);
}

QServerPlugin::~QServerPlugin()
{
    deInitExtDataBase();
    delete mutexDataBase;
}

quint8 QServerPlugin::pluginCode()
{
    return currentPluginCode;
}

QString QServerPlugin::pluginName()
{
    return currentPluginName;
}

quint16 QServerPlugin::businessId()
{
    return currentIdBusiness;
}

quint32 QServerPlugin::version()
{
    return currentVersion;
}

void QServerPlugin::setBusinessId(quint16 id)
{
    currentIdBusiness = id;
}

bool QServerPlugin::initExtDataBase(QDataBaseSettings &settingsDB)
{
    qDebug()<<"initExtDataBase : "<<settingsDB.dataBaseName;
    bool Output = false;

    mutexDataBase->lock();
    currentSettingsDB = settingsDB;
    if (!dataBase.isValid()) {
        connectionNameDB = getConnectionNameDB();
        dataBase = getDatabase();
        Output = databaseOpen();
    }
    mutexDataBase->unlock();

    if (Output) {
        dataBaseIsInit();
    }

    return Output;
}

QString QServerPlugin::getConnectionNameDB()
{
    QString connectionName = currentPluginName + "_"
            + QString::number(currentPluginCode) + "_"
            + QString::number(currentIdBusiness);

    return  connectionName;
}

QSqlDatabase QServerPlugin::getDatabase()
{
    switch (currentSettingsDB.type) {
    case QDataBaseSettings::typeQDB2:
        return QSqlDatabase::addDatabase("QDB2", connectionNameDB);

    case QDataBaseSettings::typeQIBASE:
        return QSqlDatabase::addDatabase("QIBASE", connectionNameDB);

    case QDataBaseSettings::typeQMYSQL:
        return QSqlDatabase::addDatabase("QMYSQL", connectionNameDB);

    case QDataBaseSettings::typeQOCI:
        return QSqlDatabase::addDatabase("QOCI", connectionNameDB);

    case QDataBaseSettings::typeQODBC:
        return QSqlDatabase::addDatabase("QODBC", connectionNameDB);

    case QDataBaseSettings::typeQPSQL:
        return QSqlDatabase::addDatabase("QPSQL", connectionNameDB);

    case QDataBaseSettings::typeQSQLITE:
        return QSqlDatabase::addDatabase("QSQLITE", connectionNameDB);

    case QDataBaseSettings::typeQSQLITE2:
        return QSqlDatabase::addDatabase("QSQLITE2", connectionNameDB);

    case QDataBaseSettings::typeQTDS:
        return QSqlDatabase::addDatabase("QTDS", connectionNameDB);
    }

    return QSqlDatabase::addDatabase("QSQLITE", connectionNameDB);
}

bool QServerPlugin::databaseOpen()
{
    dataBase.setHostName(currentSettingsDB.host);
    dataBase.setPort(currentSettingsDB.port);
    dataBase.setDatabaseName(currentSettingsDB.dataBaseName);
    dataBase.setUserName(currentSettingsDB.login);
    dataBase.setPassword(currentSettingsDB.password);

    bool Output = dataBase.open();
    return Output;
}

void QServerPlugin::deInitExtDataBase()
{
    mutexDataBase->lock();
    if (dataBase.isValid()) {
        if (dataBase.isOpen()) {
            dataBase.close();
        }
        dataBase.removeDatabase(connectionNameDB);
    }
    mutexDataBase->unlock();
}

bool QServerPlugin::sendExtData(quint8 command, QByteArray &data, QUnClientHandler *client)
{
    bool Output = false;

    if (clientsLists.indexOf(client) >= 0) {
        client->sendExtData(currentPluginCode,
                            command,
                            currentIdBusiness,
                            data, true);

        Output = true;
    }

    return Output;
}

void QServerPlugin::slotNewConnection (QUnClientHandler *client)
{
    clientsLists.push_back(client);

    connect(client, &QUnClientHandler::signalNewExtData,
            this, &QServerPlugin::slotNewExtData);
    connect(client, &QUnClientHandler::signalDisconnected,
            this, &QServerPlugin::slotClientDisconnected);
}

void QServerPlugin::slotClientDisconnected()
{
    QUnClientHandler *client = static_cast<QUnClientHandler*>(QObject::sender());
    clientsLists.remove(clientsLists.indexOf(client));
}

void QServerPlugin::slotNewExtData (quint8 plugin, quint8 command,
                                    quint16 idBusiness, QByteArray data,
                                    QUnClientHandler *client)
{
    if ((plugin == currentPluginCode) &&
            (idBusiness = currentIdBusiness)) {
                processCommand(command,data,client);
    }
}

void QServerPlugin::slotTimerDB()
{
    mutexDataBase->lock();

    if (dataBase.isValid() && dataBase.isOpen()) {
        dataBase.close();
    }

    mutexDataBase->unlock();
}
