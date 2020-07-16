#ifndef QSERVERLOADER_H
#define QSERVERLOADER_H

#include "../commonFiles/QUnNetProtokol/qunnetprotokolserver.h"
#include "../QPlugins/qsalesserverplugin.h"

class QServerLoader : public QObject
{
    Q_OBJECT
public:
    explicit QServerLoader(QSettings *settings, QObject *parent = nullptr);
    ~QServerLoader();

    void setDBSettings(QUnDataBaseSettings &settingsDB);
    void start();
    void stop();
    void setServerPort(int port);

private:
    void removeClient(QUnClientHandler *client);

    QSettings *currentSettings = nullptr;
    QUnNetProtokolServer *server = nullptr;
    QUnDataBaseSettings currentSettingsUnDB;
    QVector<QUnClientHandler*> clients;
    int currentPort;
    Plugins::QSalesServerPlugin *pluginSales = nullptr;

signals:
    void signalServerStarted();
    void signalServerStoped();

private slots:
    void slotServerStarted();
    void slotServerStoped();
    void slotNewConnection(QUnClientHandler *client);
    void slotClientDisconnected();

};

#endif // QSERVERLOADER_H
