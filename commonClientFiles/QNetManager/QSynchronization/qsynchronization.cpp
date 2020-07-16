#include "qsynchronization.h"
#include <QDebug>

QSynchronization::QSynchronization(ClientInformation info,
                                   QObject *parent)
    : QObject(parent),
      info(info)
{
    this->getDateRange();
    localDatabase = new QDatabaseManager(this);
    commandsToServer = new QClientCommandsToServer(this);

    connect(localDatabase, &QDatabaseManager::signalDatabaseIsInit,
            this, &QSynchronization::databaseIsInit);
}

QSynchronization::~QSynchronization()
{

}

void QSynchronization::initMainDatabase()
{
    this->initDataBase();
}

bool QSynchronization::initDataBase()
{
    bool result = localDatabase->initDataBase
            (info.pluginCode, info.pluginName, info.businessCode);

    return result;
}

void QSynchronization::deinitDataBase()
{
    localDatabase->deinitDataBase();
}

void QSynchronization::databaseIsInit()
{
    this->createLocalTables();
    emit (mainDatabaseIsReady());

    /// emit startSynchronization(); ???
}

void QSynchronization::createLocalTables()
{
    localDatabase->createProductTable();
    localDatabase->createProductAndCategoryTable();
    localDatabase->createProductAndPointSaleTable();
    localDatabase->createProductAndVolumeTable();
    localDatabase->createCategoryTable();
    localDatabase->createPointSaleTable();
    localDatabase->createPointSaleAndCategoryTable();
    localDatabase->createPointSaleAndPriceTable();
    localDatabase->createPriceTable();
    localDatabase->createReceiptTable();
    localDatabase->createSoldPositionTable();
    localDatabase->createTypeTable();
    localDatabase->createUserTable();
    localDatabase->createVolumeTable();
    localDatabase->createShiftTable();
    localDatabase->createPictureTable();
}

void QSynchronization::startSynchronization()
{
    //    localDatabase->clearAllTables();
    info.currentPointSale.clear();
    info.currentUser.clear();
    info.loadedReceipts.clear();
    info.idPictures.clear();
    currentSynchronizationStep = 0;
    firstRun = true;

    this->synchronizationProcess();
}

void QSynchronization::synchronizationProcess()
{
    if (isFirstRun()) {
        this->executeCurrentSynchronizationStep();
        this->increaseCurrentSynchronizationStepValue();
    }
}

QDatabaseManager *QSynchronization::getLocalDatabase() const
{
    return localDatabase;
}

QVector<QReceipt>& QSynchronization::getLoadedReceipts()
{
    return info.loadedReceipts;
}

void QSynchronization::setLoadedReceipts(const QVector<QReceipt> &receipts)
{
    info.loadedReceipts = receipts;
}

void QSynchronization::getDateRange()
{
    info.dateRange.startDate = info.settings->value("/SalesAdminClient/dateRange/startDate").toDate();
    info.dateRange.endDate = info.settings->value("/SalesAdminClient/dateRange/endDate").toDate();
    info.dateRange.allDates = info.settings->value("/SalesAdminClient/dateRange/allDates").toBool();
}

QUser QSynchronization::getCurrentUser() const
{
    return info.currentUser;
}

void QSynchronization::setCurrentUser(const QUser &value)
{
    info.currentUser = value;
    emit (signalCurrentUserChanged());
}

QPointSale QSynchronization::getCurrentPointSale() const
{
    return info.currentPointSale;
}

void QSynchronization::setCurrentPointSale(const QPointSale &value)
{
    info.currentPointSale = value;
}

QShift QSynchronization::getCurrentShift() const
{
    return info.currentShift;
}

void QSynchronization::setCurrentShift(const QShift &shift)
{
    info.currentShift = shift;
}

QVector<QReceipt> *QSynchronization::receipts()
{
    return &info.loadedReceipts;
}

QClientCommandsToServer *QSynchronization::getCommandsToServer() const
{
    return commandsToServer;
}

bool QSynchronization::isFirstRun()
{
    return firstRun;
}

void QSynchronization::increaseCurrentSynchronizationStepValue()
{
    currentSynchronizationStep++;
}

void QSynchronization::executeCurrentSynchronizationStep()
{
    if (info.isAdmin) {
        this->adminSynchronizationCommands();
    }
    else {
        this->clientSynchronizationCommands();
    }
}

void QSynchronization::adminSynchronizationCommands()
{
    switch (currentSynchronizationStep) {

    case 0: {
        this->signalMessage(tr("Рукопожатие"));
        commandsToServer->getHandshake();
    }
        break;
    case 1: {
        this->signalMessage(tr("Запрос всех точек продаж..."));
        //        commandsToServer->pointSale->loadAll_0x0F(); // можно вернуть этот вариант
        commandsToServer->pointSale->loadAll_0xB0();
    }
        break;
    case 2:  {
        this->signalMessage(tr("Запрос всех категорий..."));
        commandsToServer->category->loadAll();
    }
        break;
    case 3: {
        this->signalMessage(tr("Запрос всех товаров..."));
        commandsToServer->product->loadAll();
    }
        break;
    case 4: {
        this->signalMessage(tr("Запрос всех объемов..."));
        QVector<int> idProducts = localDatabase->commands->product->getAllId();
        commandsToServer->volume->loadVolumes(idProducts);
    }
        break;
    case 5: {
        this->signalMessage(tr("Запрос всех типов продаж..."));
        commandsToServer->type->loadAll();
    }
        break;
    case 6: {
        this->signalMessage(tr("Запрос информации о пользователе..."));
        commandsToServer->user->loadInformation();
    }
        break;
    case 7: {
        this->signalMessage(tr("Запрос всех цен..."));
        commandsToServer->price->loadAll();
    }
        break;
    case 8: {
        this->signalMessage(tr("Запрос всех смен..."));
        commandsToServer->shift->loadAll();
    }
        break;
    case 9: {
        this->signalMessage(tr("Запрос всех чеков..."));

        if (info.dateRange.allDates) {
            commandsToServer->receipt->loadAll();
        }
        else {
            commandsToServer->receipt->load(info.dateRange.startDate,
                                            info.dateRange.endDate);
        }
    }
        break;
    case 10: {
        this->signalMessage(tr("Запрос всех проданных позиций..."));

        if (info.dateRange.allDates) {
            commandsToServer->soldPosition->loadAll();
        }
        else {
            commandsToServer->soldPosition->load(info.dateRange.startDate,
                                            info.dateRange.endDate);
        }
    }
        break;
    case 11: {
        this->signalMessage(tr("Запрос всех пользователей..."));
        commandsToServer->user->loadAll();
    }
        break;
    case 12: {
        this->signalMessage(tr("Синхронизация изображений товаров..."));
        this->updatePicturesForProducts();
    }
        break;
    default: {
        this->stopSynchronization();
        commandsToServer->endSynchronization();
    }
        break;
    }
}

void QSynchronization::clientSynchronizationCommands()
{
    switch (currentSynchronizationStep) {

    case 0: {
        this->signalMessage(tr("Запрос информации о точке продаж..."));
        commandsToServer->pointSale->loadInformation(info.idPointSale);
    }
        break;
    case 1 : {
        this->signalMessage(tr("Запрос категорий..."));
        QVector<int> idCategory = info.currentPointSale.idCategories;
        commandsToServer->category->load(idCategory);
    }
        break;
    case 2: {
        this->signalMessage(tr("Запрос информации о товаре..."));
        QVector<int> idProducts = localDatabase->commands->pointSale->getProductsId(info.currentPointSale.id);
        commandsToServer->product->load(idProducts);
    }
        break;
    case 3 : {
        this->signalMessage(tr("Запрос объемов..."));
        QVector<int> idProducts = localDatabase->commands->product->getAllId();
        commandsToServer->volume->loadVolumes(idProducts);
    }
        break;
    case 4 : {
        this->signalMessage(tr("Запрос типов продаж..."));
        commandsToServer->type->loadAll();
    }
        break;
    case 5 : {
        this->signalMessage(tr("Запрос цен..."));
        commandsToServer->price->load(info.currentPointSale.id);
    }
        break;
    case 6 : {
        this->signalMessage(tr("Запрос информации о пользователе..."));
        commandsToServer->user->loadInformation();
    }
        break;
    case 7 : {
        this->signalMessage(tr("Открытие смены..."));
        commandsToServer->shift->open(info.currentPointSale.id);
    }
        break;
    case 8 : {
        this->signalMessage(tr("Загрузка чеков..."));
        commandsToServer->receipt->load(info.currentShift);
    }
        break;
    case 9 : {
        this->signalMessage(tr("Загрузка проданных позиций..."));
        commandsToServer->soldPosition->load(info.loadedReceipts);
    }
        break;
    case 10: {
        this->signalMessage(tr("Загрузка изображения..."));
        this->updatePicturesForProducts();
    }
        break;
    default:
        this->stopSynchronization();
        commandsToServer->endSynchronization();
        break;
    }
}

void QSynchronization::stopSynchronization()
{
    if (isFirstRun()) {
        emit(this->signalMessage(tr("Синхронизация завершена")));
        firstRun = false;
    }
}

void QSynchronization::updatePicturesForProducts()
{
    increaseCurrentSynchronizationStepValue();
    info.idPictures.clear();

    QVector<QProduct> products = localDatabase->commands->product->getProducts();

    QVector<int> buf;
    QProduct product;
    for (int i = 0; i < products.length(); i++) {
        product = products.at(i);

        if ((buf.indexOf(product.idPicture) <0) &&
                (product.idPicture > 0))
            buf.push_back(product.idPicture);
    }

    QProductPicture currentPicture;
    for (int i = 0; i < buf.length(); i++) {
        currentPicture = localDatabase->commands->picture->get(buf.at(i));

        if (currentPicture.id == -1)
            info.idPictures.push_back(buf.at(i));
    }

    this->getNextPictureIfExistOrNextStep();
}

void QSynchronization::getNextPictureIfExistOrNextStep()
{
    if (isNewPicturesEmpty()) {
        this->synchronizationProcess();
    }
    else {
        this->requestNextNewPicture();
    }
}

bool QSynchronization::isNewPicturesEmpty()
{
    bool result = true;
    if (info.idPictures.size() > 0) {
        result = false;
    }
    return result;
}

void QSynchronization::requestNextNewPicture()
{
    commandsToServer->picture->loadInformation(info.idPictures.at(0));
    info.idPictures.remove(0,1);
}
