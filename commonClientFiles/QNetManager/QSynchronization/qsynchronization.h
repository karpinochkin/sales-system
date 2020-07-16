#ifndef QSYNCHRONIZATION_H
#define QSYNCHRONIZATION_H

#include <QObject>
#include <QSettings>
#include "../commonClientFiles/QDatabaseManager/qdatabasemanager.h"
#include "../QClientCommandsToServer/qclientcommandstoserver.h"
#include "../SalesClientAdmin/gui/loader/QDateRangeDialog/qdaterangedialog.h"

struct ClientInformation {
    bool isAdmin;
    int idPointSale;
    quint8 pluginCode;
    quint16 businessCode;
    QString pluginName;
    QSettings *settings = nullptr;

    QPointSale currentPointSale;
    QUser currentUser;
    QShift currentShift;
    QVector<QReceipt> loadedReceipts; //Список чеков
    QVector<int> idPictures; //id картинок напитков
    Gui::Loader::DateRange dateRange;
};

class QSynchronization : public QObject
{
    Q_OBJECT
public:
    explicit QSynchronization(ClientInformation info,
                              QObject *parent = nullptr);
    ~QSynchronization();

    void startSynchronization();
    void initMainDatabase();
    void synchronizationProcess();
    void getNextPictureIfExistOrNextStep();

    QClientCommandsToServer *getCommandsToServer() const;
    QDatabaseManager *getLocalDatabase() const;

    QVector<QReceipt> &getLoadedReceipts();
    void setLoadedReceipts(const QVector<QReceipt>& receipts);
    QUser getCurrentUser() const;
    void setCurrentUser(const QUser &value);
    QPointSale getCurrentPointSale() const;
    void setCurrentPointSale(const QPointSale &value);
    QShift getCurrentShift() const;
    void setCurrentShift(const QShift &shift);
    QVector<QReceipt> *receipts();

private:
    ClientInformation info;

    int currentSynchronizationStep = 0; //Текущий шаг синхронизации
    bool firstRun = true; //Флаг первого подключения

    QDatabaseManager *localDatabase = nullptr;
    QClientCommandsToServer *commandsToServer = nullptr;

private:
    bool initDataBase(); //Запускает инициализацию внутренней оперативной БД
    void deinitDataBase();
    void createLocalTables();

    bool isFirstRun();
    void executeCurrentSynchronizationStep(); //Выполнение текущего шага синхронизации
    void increaseCurrentSynchronizationStepValue(); //Следующий шаг синхронизации
    void adminSynchronizationCommands();
    void clientSynchronizationCommands();
    void stopSynchronization(); //Завершение синхронизации

    void updatePicturesForProducts();
    bool isNewPicturesEmpty();
    void requestNextNewPicture();
    void getDateRange();

private slots:
    void databaseIsInit();

signals:
    void signalMessage(QString);
    void mainDatabaseIsReady();
    void signalCurrentUserChanged();
};

#endif // QSYNCHRONIZATION_H
