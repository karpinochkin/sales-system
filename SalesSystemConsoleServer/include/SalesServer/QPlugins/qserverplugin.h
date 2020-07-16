#ifndef QSERVERPLUGIN_H
#define QSERVERPLUGIN_H

#include <QObject>
#include "../../../../commonFiles/QDataBaseSettings/qdatabasesettings.h"
#include "../../../../commonFiles/QUnNetProtokol/qunnetprotokolserver.h"

class QServerPlugin : public QObject
{
    Q_OBJECT
public:
    explicit QServerPlugin(QUnNetProtokolServer *server,quint16 business, QObject *parent = nullptr);
    virtual ~QServerPlugin();

    quint8 pluginCode();
    QString pluginName();
    quint16 businessId();
    quint32 version();
    void setBusinessId(quint16 id);

    bool initExtDataBase(QDataBaseSettings &settingsDB);
    void deInitExtDataBase();

//    QSqlQuery *execQuery(QString textQuery, bool *ok = nullptr);
//    QSqlQuery *execQuery(QString textQuery, QString bindName,
//                         QVariant bindValue, bool *ok = nullptr);

protected:
    quint8 currentPluginCode = 0xFF; //Задается уникальный код плагина
    QString currentPluginName = "QServerPlugin"; //Уникальное имя плагина
    quint16 currentIdBusiness = 0xffff; //Уникальный идентификатор деятельности
    quint32 currentVersion = 0xffffffff; //Версия плагина

    QUnNetProtokolServer *currentServer;
    QVector<QUnClientHandler*> clientsLists;
    QDataBaseSettings currentSettingsDB;
    QString connectionNameDB;
    QSqlDatabase dataBase;

    QMutex *mutexDataBase = nullptr;
    QTimer *timerDB = nullptr;

    virtual void dataBaseIsInit() = 0;
    virtual void processCommand(quint8 command, QByteArray data,
                                QUnClientHandler *client) = 0; //Обработчик комманд плагина

//    int getNextId(QString table, QString idName);
    bool sendExtData(quint8 command, QByteArray &data,
                     QUnClientHandler *client); //Функция для отправки данных клиентам

private:
    QString getConnectionNameDB();
    QSqlDatabase getDatabase();
    bool databaseOpen();

signals:
    void signalPluginDebugMessage(quint8 plugCode, QString plugName,
                                  quint16 business, QString message);

public slots:
    void slotNewConnection (QUnClientHandler *client);
    void slotClientDisconnected();
    void slotNewExtData (quint8 plugin, quint8 command,
                         quint16 idBusiness, QByteArray data,
                         QUnClientHandler *client);

private slots:
    void slotTimerDB();
};

#endif // QSERVERPLUGIN_H
