#ifndef QNETMANAGER_H
#define QNETMANAGER_H

#include <QObject>
#include <QSettings>
#include "../commonFiles/QUnNetProtokol/qunnetprotokolclient.h"
#include "QSynchronization/qsynchronization.h"
#include "../commonFiles/DatabaseEnumCommands/DatabaseEnumCommands.h"
#include "../commonFiles/SalesSystem/QStatistics/qstatistics.h"

struct ConnectionData
{
    QString login;
    QString password;
    QString address;
    QString port;
};

class QNetManager : public QObject
{
    Q_OBJECT
public:
    [[deprecated("use this constructor only for getters func")]]
    explicit QNetManager(bool isClientCreate,
                         QSettings *settings,
                         QObject *parent = nullptr);

    explicit QNetManager(QSettings *settings, QObject *parent = nullptr);
    explicit QNetManager(int idPointSale, QSettings *settings,
                         QObject *parent = nullptr);

    ~QNetManager();

    QDatabaseConrol* DatabaseCommands() const;
    QClientCommandsToServer* CommandsToServer() const;
    void setCurrentUser(const QUser &user);
    QUser getCurrentUser() const;
    bool isAuthorized();
    void clientConnect();
    void Disconnect();
    QString host() const;
    int port() const;
    QShift currentShift() const;
    void setCurrentShift(const QShift&);
    QPointSale currentPointSale() const;
    void closeShift();
    void sale(QReceipt &receipt,
              const QVector<QSoldPosition> &soldPositions);

    void setAccount(QString login, QString password);
    void setHosts(const QVector<HostInfo> &hosts);
    QVector<HostInfo> hosts() const;

private:
    quint8 currentPluginCode;
    quint16 currentBusinessCode;
    QString currentPluginName = "QSalesPlugin";
    ConnectionData connectionUserInformation;
    int idPointSale;
    bool isAdminClient = false;

    QMutex *mutexCurrentUser = nullptr;
    QSettings *currentSettings = nullptr;
    QUnNetProtokolCLient *client = nullptr;
    QSynchronization *synchronization = nullptr;

private:
    void startSynchronization(); //Запуск процесса синхронизации
    void createObjects();
    void loadSettings();
    void checkHosts();
    void createSynchronizationObject();
    void slotsConnect();

    void processCommand(quint8 command, QByteArray data);
    void command0xA1_handshake(QByteArray &data);
    void command0x01_getPointSale(QByteArray &data);
    void command0x02_getCategories(QByteArray &data);
    void command0x03_getProducts(QByteArray &data);
    void command0x04_getVolumes(QByteArray &data);
    void command0x05_getTypes(QByteArray &data);
    void command0x06_getPrices(QByteArray &data);
    void command0x07_getUser(QByteArray &data);
    void command0x08_openShift(QByteArray &data);
    void command0x09_closeShift(QByteArray &data);
    void command0x0A_getReceipts(QByteArray &data);
    void command0x0B_getSoldPositions(QByteArray &data);
    void command0x0C_sentSale(QByteArray &data);
    void command0x0D_sentPicture(QByteArray &data);
    void command0x0E_getPicture(QByteArray &data);
    void command0x0F_getIdAllPointSales(QByteArray &data);
    void command0x10_getPointSale(QByteArray &data);
    void command0x11_getAllCategories(QByteArray &data);
    void command0x12_getAllProducts(QByteArray &data);
    void command0x13_getAllPrices(QByteArray &data);
    void command0x14_getAllShifts(QByteArray &data);
    void command0x15_getAllReceipts(QByteArray &data);
    void command0x16_getAllSoldPositions(QByteArray &data);
    void command0xA2_endSynchronization(QByteArray &data);
    void command0xB0_getPointSales(QByteArray &data);
    void command0xB1_getAllPictures(QByteArray &data);
    void command0xB2_removePicture(QByteArray &data);
    void command0xB3_removeType(QByteArray &data);
    void command0xB4_sentType(QByteArray &data);
    void command0xB5_removeVolume(QByteArray &data);
    void command0xB6_sentVolume(QByteArray &data);
    void command0xB7_removeUser(QByteArray &data);
    void command0xB8_sentUser(QByteArray &data);
    void command0xB9_getAllUsers(QByteArray &data);
    void command0xC1_sentPointSale(QByteArray &data);
    void command0xC2_removePointSale(QByteArray &data);
    void command0xC3_sentCategory(QByteArray &data);
    void command0xC4_removeCategory(QByteArray &data);
    void command0xC5_sentPrice(QByteArray &data);
    void command0xC6_getReceiptsByDateRange(QByteArray &data);
    void command0xC7_getSoldPositionsByDateRange(QByteArray &data);
    void command0xC8_getStatistics(QByteArray &data);
    void command0xA0_sentProduct(QByteArray &data);

    void getPointSale(QByteArray &data);
    std::tuple<bool, int, QString> remove(QByteArray &data);

private slots:
    void slotConnected();
    void slotAuthorized();
    void slotDisconnected();
    void slotError (UnErr err);
    void slotUserInfoReceived();
    void slotNewExtPacket (quint8 plugin,quint8 command, quint16 idBusiness, QByteArray data);
    void sendData(QByteArray &data, int command_code, bool save);
    void databaseIsInit();

signals:
    void signalAuthorized();
    void signalError(QString);
    void signalUnError(UnErr err);
    void signalBeginSynchronization(); //Сигнал начала синхронизации данных с сервером
    void signalEndSynchronization(); //Сигнал окончания синхронизации
    void signalMessageSplashScreen(QString message); //Сообщение процесса синхронизации

    void signalPointSaleInformationLoaded(QPointSale);
    void signalShiftOpened();
    void signalShiftClosed();
    void signalCategoriesLoaded();
    void signalProductsLoaded();
    void signalPricesLoaded();
    void signalVolumesLoaded();
    void signalTypesLoaded();
    void signalUserInformationLoaded();
    void signalShiftsLoaded();
    void signalReceiptsLoaded();
    void signalSoldPositionsLoaded();
    void signalProductSent();
    void signalPictureSent();
    void signalPicturesLoaded();
    void signalRemovePicture(bool result, int id, QString name);
    void signalRemoveType(bool result, int id, QString name);
    void signalTypeSent();
    void signalRemoveVolume(bool result, int id, QString name);
    void signalVolumeSent();
    void signalRemoveUser(bool result, int id, QString login);
    void signalUserSent();
    void signalUsersLoaded();
    void signalPointSaleSent();
    void signalRemovePointSale(bool result, int id, QString name);
    void signalCategorySent();
    void signalRemoveCategory(bool result, int id, QString name);
    void signalPriceSent();
    void signalStatisticsLoaded(const QVector<QStatistics>&, double maxValue);
};
#endif // QNETMANAGER_H
