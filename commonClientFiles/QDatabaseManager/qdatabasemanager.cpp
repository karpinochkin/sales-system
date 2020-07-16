#include "qdatabasemanager.h"

QDatabaseManager::QDatabaseManager(QObject *parent) : QObject(parent)
{
    mutexDataBase = new QMutex();
    mutexPictureDatabase = new QMutex();
    pictureDatabase = new QSqlDatabase();
}

QDatabaseManager::~QDatabaseManager()
{
    delete mutexDataBase;
    delete mutexPictureDatabase;
    delete pictureDatabase;
}

bool QDatabaseManager::initDataBase(quint8 pluginCode, QString pluginName, quint16 idBusiness)
{
    bool Output = false;

    mutexDataBase->lock();

    if (database == nullptr) {
        database = new QSqlDatabase();
        connectionNameDB = this->getCorrectName(pluginCode, pluginName, idBusiness);

        *database = QSqlDatabase::addDatabase("QSQLITE",connectionNameDB);
        database->setDatabaseName(":memory:");

        Output = database->open();
    }

    mutexDataBase->unlock();

    if(Output) {
        this->databaseIsInit();
    }

    return Output;
}

QString QDatabaseManager::getCorrectName(quint8 pluginCode, QString pluginName, quint16 idBusiness)
{
    QString output = pluginName + "_"
            + QString::number(pluginCode) + "_"
            + QString::number(idBusiness);
    return output;
}

void QDatabaseManager::databaseIsInit()
{
    commands = new QDatabaseConrol(database, this);
    emit(signalDatabaseIsInit());
}

void QDatabaseManager::deinitDataBase()
{
    mutexDataBase->lock();
    if (database != nullptr) {
        if (database->isOpen()) {
            database->close();
        }

        delete database;
        delete commands;
        commands = nullptr;

        QSqlDatabase::removeDatabase(connectionNameDB);
    }

    mutexDataBase->unlock();
}

void QDatabaseManager::clearAllTables()
{
    if (isCommandsValid()) {
        commands->type->clear();
        commands->user->clear();
        commands->price->clear();
        commands->shift->clear();
        commands->volume->clear();
        commands->product->clear();
        commands->receipt->clear();
        commands->category->clear();
        commands->pointSale->clear();
        commands->soldPosition->clear();
    }
}

bool QDatabaseManager::isCommandsValid()
{
    if (commands == nullptr) {
        return false;
    }
    else {
        return true;
    }
}

void QDatabaseManager::createProductTable()
{
    if(isCommandsValid()) {
        commands->product->createTable();
    }
}

void QDatabaseManager::createProductAndCategoryTable()
{
    if (isCommandsValid()) {
        commands->product->productAndCategoryTable->createTable();
    }
}

void QDatabaseManager::createProductAndPointSaleTable()
{
    if (isCommandsValid()) {
        commands->pointSale->createPointSaleAndProductTable();
    }
}

void QDatabaseManager::createProductAndVolumeTable()
{
    if(isCommandsValid()) {
        commands->product->productAndVolumeTable->createTable();
    }
}

void QDatabaseManager::createCategoryTable()
{
    if(isCommandsValid()) {
        commands->category->createTable();
    }
}

void QDatabaseManager::createPointSaleTable()
{
    if(isCommandsValid()) {
        commands->pointSale->createTable();
    }
}

void QDatabaseManager::createPointSaleAndCategoryTable()
{
    if (isCommandsValid()) {
        commands->pointSale->createPointSaleAndCategoryTable();
    }
}

void QDatabaseManager::createPointSaleAndPriceTable()
{
    if (isCommandsValid()) {
        commands->price->createPointSaleAndPriceTable();
    }
}

void QDatabaseManager::createPriceTable()
{
    if (isCommandsValid()) {
        commands->price->createTable();
    }
}

void QDatabaseManager::createReceiptTable()
{
    if (isCommandsValid()) {
        commands->receipt->createTable();
    }
}

void QDatabaseManager::createSoldPositionTable()
{
    if (isCommandsValid()) {
        commands->soldPosition->createTable();
    }
}

void QDatabaseManager::createTypeTable()
{
    if (isCommandsValid()) {
        commands->type->createTable();
    }
}

void QDatabaseManager::createUserTable()
{
    if (isCommandsValid()) {
        commands->user->createTable();
    }
}

void QDatabaseManager::createVolumeTable()
{
    if (isCommandsValid()) {
        commands->volume->createTable();
    }
}

void QDatabaseManager::createShiftTable()
{
    if (isCommandsValid()) {
        commands->shift->createTable();
    }
}

void QDatabaseManager::initPictureDatabase()
{
    *pictureDatabase = QSqlDatabase::addDatabase("QSQLITE", "connectionPicture");
    pictureDatabase->setDatabaseName("picture.db");
    if (pictureDatabase->open()) {
        commands->setPictureDatabase(pictureDatabase); // Заменяем бд для картинок на нужную
    }
    else {
        qDebug() << pictureDatabase->lastError();
    }
}

void QDatabaseManager::createPictureTable()
{
    if (isCommandsValid()) {
        this->initPictureDatabase();
        commands->picture->createTable();
    }
}
