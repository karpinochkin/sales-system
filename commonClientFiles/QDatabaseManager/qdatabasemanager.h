#ifndef QDATABASEMANAGER_H
#define QDATABASEMANAGER_H

#include <QObject>
#include <QSqlDatabase>
#include <QMutex>
#include "../commonFiles/QDatabaseControl/qdatabaseconrol.h"

class QDatabaseManager : public QObject
{
    Q_OBJECT
public:
    explicit QDatabaseManager(QObject *parent = nullptr);
    ~QDatabaseManager();

    bool initDataBase(quint8 pluginCode, QString pluginName, quint16 idBusiness); //Запускает инициализацию внутренней оперативной БД
    void deinitDataBase();
    void clearAllTables();

    void createProductTable();
    void createProductAndCategoryTable();
    void createProductAndPointSaleTable();
    void createProductAndVolumeTable();
    void createCategoryTable();
    void createPointSaleTable();
    void createPointSaleAndCategoryTable();
    void createPointSaleAndPriceTable();
    void createPriceTable();
    void createReceiptTable();
    void createSoldPositionTable();
    void createTypeTable();
    void createUserTable();
    void createVolumeTable();
    void createShiftTable();

    void initPictureDatabase();
    void createPictureTable();

    QDatabaseConrol *commands = nullptr;

private:
    QSqlDatabase *database = nullptr;
    QSqlDatabase *pictureDatabase = nullptr;
    QMutex *mutexPictureDatabase = nullptr;
    QMutex *mutexDataBase = nullptr;
    QString connectionNameDB;

    QString getCorrectName(quint8 pluginCode, QString pluginName, quint16 idBusiness);
    void databaseIsInit();
    bool isCommandsValid();

signals:
    void signalDatabaseIsInit();
};

#endif // QDATABASEMANAGER_H
