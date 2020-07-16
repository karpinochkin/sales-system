#include "qnetmanager.h"

/// Create client without init bd, synchronization and connection
/// use this contructor if you need to get hosts info
QNetManager::QNetManager(bool isClientCreate,
                         QSettings *settings,
                         QObject *parent)
    : QObject(parent),
      currentPluginCode(0x07),
      currentBusinessCode(0x08),
      currentSettings(settings)
{
    if (isClientCreate) {
        qDebug() << "QNetManager start";
        this->createObjects();
    }
}

/// create admin client with auto synch,
/// auto init db, auto get account settings,
/// auto get hosts and auto client connect
/// use this constructor for the admin client
QNetManager::QNetManager(QSettings *settings, QObject *parent)
    : QObject (parent),
      currentPluginCode(0x07),
      currentBusinessCode(0x08),
      isAdminClient(true),
      currentSettings (settings)
{
    qDebug() << "QNetManager start";
    this->createSynchronizationObject();
}

/// create client with init bd,
/// but without auto connection
/// for connection : setHosts(..), setAccount(..)
/// and clientConnect()
/// use this constructor for the point sale client
QNetManager::QNetManager(int IdPointSale, QSettings *settings, QObject *parent)
    : QObject(parent),
      currentPluginCode(0x07),
      currentBusinessCode(0x08),
      idPointSale(IdPointSale),
      currentSettings(settings)
{
    this->createSynchronizationObject();

}

QNetManager::~QNetManager()
{
    qDebug() << "~QNetManager";
    delete mutexCurrentUser;
}

void QNetManager::loadSettings()
{
    if (isAdminClient) {
        connectionUserInformation.login = currentSettings->value("/SalesAdminClient/login").toString();
        connectionUserInformation.password = currentSettings->value("/SalesAdminClient/password").toString();
        connectionUserInformation.port = currentSettings->value("/SalesAdminClient/port").toString();
        connectionUserInformation.address = currentSettings->value("/SalesAdminClient/address").toString();
    }

}

void QNetManager::setAccount(QString login, QString password)
{
    client->setAccount(login, password);
}

void QNetManager::setHosts(const QVector<HostInfo> &hosts)
{
    client->setHosts(hosts);
}

QVector<HostInfo> QNetManager::hosts() const
{
    return client->hosts();
}

void QNetManager::createSynchronizationObject()
{
    ClientInformation info;
    info.isAdmin = isAdminClient;
    info.idPointSale = idPointSale;
    info.pluginCode = currentPluginCode;
    info.pluginName = currentPluginName;
    info.businessCode = currentBusinessCode;
    info.settings = currentSettings;

    synchronization = new QSynchronization(info, this);
    connect(synchronization, &QSynchronization::mainDatabaseIsReady,
            this, &QNetManager::databaseIsInit);
    synchronization->initMainDatabase();
}

void QNetManager::createObjects()
{
    client = new QUnNetProtokolCLient("SalesClient", currentSettings, this);
    mutexCurrentUser = new QMutex();
    client->flagClearOnDisconnect = true;
}

void QNetManager::slotsConnect()
{
    connect(client, &QUnNetProtokolCLient::signalConnected,
            this,   &QNetManager::slotConnected);
    connect(client, &QUnNetProtokolCLient::signalAuthorized,
            this,   &QNetManager::slotAuthorized);
    connect(client, &QUnNetProtokolCLient::signalDisconnected,
            this,   &QNetManager::slotDisconnected);
    connect(client, &QUnNetProtokolCLient::signalError,
            this,   &QNetManager::slotError);
    connect(client, &QUnNetProtokolCLient::signalNewExtPacket,
            this,   &QNetManager::slotNewExtPacket);
    connect(client, &QUnNetProtokolCLient::signalUserInfoReceived,
            this,   &QNetManager::slotUserInfoReceived);

    connect(synchronization->getCommandsToServer(), &QClientCommandsToServer::signalSendCommand,
            this, &QNetManager::sendData);
    connect(synchronization, &QSynchronization::signalMessage,
            this, &QNetManager::signalMessageSplashScreen);
}

void QNetManager::databaseIsInit()
{
    if (isAdminClient) {
        this->createObjects();
        this->slotsConnect();
        this->loadSettings();
        this->checkHosts();
        this->setAccount(connectionUserInformation.login,
                         connectionUserInformation.password);
        this->clientConnect();
        return;
    }

    this->createObjects();
    this->slotsConnect();
}

void QNetManager::clientConnect()
{
    if  (client->connectToHost()) {
        qDebug()<<"Connect to host: true";
    } else {
        qDebug()<<"Connect to host: false";
    }
}

void QNetManager::checkHosts()
{
    qDebug()<<"add hosts";

    QVector<HostInfo> hosts;
    HostInfo A;
    A.address = connectionUserInformation.address;
    A.port = connectionUserInformation.port.toInt();
    A.description = "server";
    hosts.push_back(A);

    client->setHosts(hosts);
}

void QNetManager::slotConnected()
{
    qDebug()<<"Connected";
}

void QNetManager::slotAuthorized()
{
    qDebug()<<"Authorized";
    emit(signalAuthorized());
}

void QNetManager::Disconnect()
{
    client->disconnectFromHost();
    client->waitForDisconnected();
}

QString QNetManager::host() const
{
    QVector<HostInfo> hosts = client->hosts();
    int currentHost = client->currentHostIndex();
    return hosts.at(currentHost).address;
}

int QNetManager::port() const
{
    QVector<HostInfo> hosts = client->hosts();
    int currentHost = client->currentHostIndex();
    return hosts.at(currentHost).port;
}

QShift QNetManager::currentShift() const
{
    return synchronization->getCurrentShift();
}

void QNetManager::setCurrentShift(const QShift &shift)
{
    synchronization->setCurrentShift(shift);
}

QPointSale QNetManager::currentPointSale() const
{
    return synchronization->getCurrentPointSale();
}

void QNetManager::closeShift()
{
    QShift shift = currentShift();
    CommandsToServer()->shift->close(shift);
}

void QNetManager::sale(QReceipt &receipt, const QVector<QSoldPosition> &soldPositions)
{
    signalMessageSplashScreen(tr("Отправка продажи"));
    receipt.id = -1;
    receipt.dateTime = QDateTime::currentDateTime();
    receipt.idPointSale = currentPointSale().id;
    receipt.idShift = currentShift().id;
    receipt.id = DatabaseCommands()->receipt->add(receipt);

    QVector<QSoldPosition> outputSoldPositions;
    for (auto value : soldPositions) {
        value.id = -1;
        value.idReceipt = receipt.id;
        value.date = receipt.dateTime;
        value.idPointSale = currentPointSale().id;
        value.idUser = getCurrentUser().id;

        value.id = DatabaseCommands()->soldPosition->add(value);
        outputSoldPositions.push_back(value);
    }

    CommandsToServer()->receipt->sendSale(receipt, outputSoldPositions);
}

QDatabaseConrol* QNetManager::DatabaseCommands() const
{
    if (synchronization != nullptr) {
        return synchronization->getLocalDatabase()->commands;
    }
    return nullptr;
}

QClientCommandsToServer* QNetManager::CommandsToServer() const
{
    if (synchronization != nullptr) {
        return synchronization->getCommandsToServer();
    }
    return nullptr;
}

void QNetManager::setCurrentUser(const QUser &user)
{
    synchronization->setCurrentUser(user);
}

QUser QNetManager::getCurrentUser() const
{
    return synchronization->getCurrentUser();
}

bool QNetManager::isAuthorized()
{
    return client->isAuthorizes();
}

void QNetManager::slotDisconnected()
{
    qDebug()<<"Disconnected";
}


void QNetManager::slotError (UnErr err)
{
    qDebug()<<"Error client: " + QString::number(err);
    emit (signalUnError(err));
    emit(signalError(QString::number(err)));
}

void QNetManager::slotUserInfoReceived()
{
    this->startSynchronization();
}

void QNetManager::startSynchronization()
{
    emit(signalBeginSynchronization());
    synchronization->startSynchronization();
}

void QNetManager::sendData(QByteArray &data, int command_code, bool save)
{
    client->sendExtData(static_cast<quint8>(currentPluginCode),
                        static_cast<quint8>(command_code),
                        data,
                        static_cast<quint16>(currentBusinessCode),
                        save);
}

void QNetManager::slotNewExtPacket (quint8 plugin,quint8 command, quint16 idBusiness, QByteArray data)
{
    if(plugin == currentPluginCode &&
            idBusiness == currentBusinessCode) {
        processCommand(command,data);
    }
}

void QNetManager::processCommand(quint8 command,QByteArray data)
{
    switch (command) {
    case 0xA1: command0xA1_handshake(data);
        break;
    case 0x01: command0x01_getPointSale(data);
        break;
    case 0x02: command0x02_getCategories(data);
        break;
    case 0x03: command0x03_getProducts(data);
        break;
    case 0x04: command0x04_getVolumes(data);
        break;
    case 0x05: command0x05_getTypes(data);
        break;
    case 0x06 : command0x06_getPrices(data);
        break;
    case 0x07: command0x07_getUser(data);
        break;
    case 0x08: command0x08_openShift(data);
        break;
    case 0x09: command0x09_closeShift(data);
        break;
    case 0x0A: command0x0A_getReceipts(data);
        break;
    case 0x0B: command0x0B_getSoldPositions(data);
        break;
    case 0x0C: command0x0C_sentSale(data);
        break;
    case 0x0D: command0x0D_sentPicture(data);
        break;
    case 0x0E: command0x0E_getPicture(data);
        break;
    case 0x0F: command0x0F_getIdAllPointSales(data);
        break;
    case 0x10: command0x10_getPointSale(data);
        break;
    case 0x11: command0x11_getAllCategories(data);
        break;
    case 0x12: command0x12_getAllProducts(data);
        break;
    case 0x13: command0x13_getAllPrices(data);
        break;
    case 0x14: command0x14_getAllShifts(data);
        break;
    case 0x15: command0x15_getAllReceipts(data);
        break;
    case 0x16: command0x16_getAllSoldPositions(data);
        break;
    case 0xA2: command0xA2_endSynchronization(data);
        break;
    case 0xA0: command0xA0_sentProduct(data);
        break;
    case 0xB0: command0xB0_getPointSales(data);
        break;
    case 0xB1: command0xB1_getAllPictures(data);
        break;
    case 0xB2: command0xB2_removePicture(data);
        break;
    case 0xB3: command0xB3_removeType(data);
        break;
    case 0xB4: command0xB4_sentType(data);
        break;
    case 0xB5: command0xB5_removeVolume(data);
        break;
    case 0xB6: command0xB6_sentVolume(data);
        break;
    case 0xB7: command0xB7_removeUser(data);
        break;
    case 0xB8: command0xB8_sentUser(data);
        break;
    case 0xB9: command0xB9_getAllUsers(data);
        break;
    case 0xC1: command0xC1_sentPointSale(data);
        break;
    case 0xC2: command0xC2_removePointSale(data);
        break;
    case 0xC3: command0xC3_sentCategory(data);
        break;
    case 0xC4: command0xC4_removeCategory(data);
        break;
    case 0xC5: command0xC5_sentPrice(data);
        break;
    case 0xC6: command0xC6_getReceiptsByDateRange(data);
        break;
    case 0xC7: command0xC7_getSoldPositionsByDateRange(data);
        break;
    case 0xC8: command0xC8_getStatistics(data);
        break;
    }
}

void QNetManager::command0xA1_handshake(QByteArray &data)
{
    this->signalMessageSplashScreen(tr("Рукопожатие"));
    qDebug()<<"\n   command0xA1 : handshake ";

    qDebug()<<"Server answer: ";
    qDebug()<<QString(data);
    synchronization->synchronizationProcess();
}

void QNetManager::command0x01_getPointSale(QByteArray &data)
{
    this->signalMessageSplashScreen(tr("Прием информации о точке продаж"));
    getPointSale(data);
    synchronization->synchronizationProcess();
}

void QNetManager::command0x02_getCategories(QByteArray &data)
{
    this->signalMessageSplashScreen(tr("Прием категорий..."));
    QDataStream streamIn (&data,QIODevice::ReadOnly);
    streamIn.device()->seek(0);

    QSalesCategory category;
    int id = -1;

    while (!streamIn.atEnd()) {
        category << streamIn;
        id = DatabaseCommands()->category->getId(category);
        if (id <= 0) {
            DatabaseCommands()->category->add(category.id, category);
        }
        else {
            DatabaseCommands()->category->edit(category);
        }
    }

    emit (signalCategoriesLoaded());
    synchronization->synchronizationProcess();
}

void QNetManager::command0x03_getProducts(QByteArray &data)
{
    this->signalMessageSplashScreen(tr("Прием товаров..."));
    QDataStream streamIn (&data,QIODevice::ReadOnly);
    streamIn.device()->seek(0);
    QProduct product;

    quint16 count;
    streamIn>>count;
    int id = -1;

    while (!streamIn.atEnd()) {
        product << streamIn;

        id = DatabaseCommands()->product->getId(product);
        if (id <=0) {
            DatabaseCommands()->product->add(product.id, product);
        } else {
            DatabaseCommands()->product->edit(product);
        }
    }

    emit (signalProductsLoaded());
    synchronization->synchronizationProcess();
}

void QNetManager::command0x04_getVolumes(QByteArray &data)
{
    this->signalMessageSplashScreen(tr("Прием информации об объемах"));
    QDataStream streamIn (&data,QIODevice::ReadOnly);
    streamIn.device()->seek(0);

    QVolumeProduct volume;
    quint16 count;
    streamIn >> count;
    int id;

    while (!streamIn.atEnd()) {
        volume << streamIn;

        id = this->DatabaseCommands()->volume->getId(volume);
        if (id <= 0) {
            this->DatabaseCommands()->volume->add(volume.id, volume);
        }
        else {
            this->DatabaseCommands()->volume->edit(volume);
        }
    }
    emit (this->signalVolumesLoaded());
    synchronization->synchronizationProcess();
}

void QNetManager::command0x05_getTypes(QByteArray &data)
{
    this->signalMessageSplashScreen(tr("Прием всех типов товаров"));
    QDataStream streamIn (&data,QIODevice::ReadOnly);
    streamIn.device()->seek(0);

    quint16 count;
    streamIn >> count;

    QPaymentType type;
    while (!streamIn.atEnd()) {
        type << streamIn;

        int id = this->DatabaseCommands()->type->getId(type);

        if (id <= 0) {
            this->DatabaseCommands()->type->add(type.id, type);
        }
        else {
            this->DatabaseCommands()->type->edit(type);
        }
    }
    emit (this->signalTypesLoaded());
    synchronization->synchronizationProcess();
}

void QNetManager::command0x06_getPrices(QByteArray &data)
{
    this->signalMessageSplashScreen(tr("Прием цен для точки продаж..."));
    QDataStream streamIn (&data,QIODevice::ReadOnly);
    streamIn.device()->seek(0);

    QPrice price;
    quint16 count;
    streamIn >> count;
    int id;

    while (!streamIn.atEnd()) {
        price << streamIn;
        id = DatabaseCommands()->price->getId(price);
        if (id <=0) {
            DatabaseCommands()->price->add(price.id, price);
        } else {
            DatabaseCommands()->price->edit(price);
        }
    }

    emit (signalPricesLoaded());
    synchronization->synchronizationProcess();
}

void QNetManager::command0x07_getUser(QByteArray &data)
{
    this->signalMessageSplashScreen(tr("Прием информации о пользователе"));
    QDataStream streamIn (&data,QIODevice::ReadOnly);
    streamIn.device()->seek(0);

    mutexCurrentUser->lock();
    QUser user;
    user << streamIn;
    synchronization->setCurrentUser(user);

    int id = this->DatabaseCommands()->user->getId(user);
    if (id <= 0) {
        this->DatabaseCommands()->user->add(user.id, user);
    }
    else {
        this->DatabaseCommands()->user->edit(user);
    }
    mutexCurrentUser->unlock();

    emit (this->signalUserInformationLoaded());
    synchronization->synchronizationProcess();
}

void QNetManager::command0x08_openShift(QByteArray &data)
{
    QDataStream streamIn (&data,QIODevice::ReadOnly);
    streamIn.device()->seek(0);

    bool isNewShift;
    streamIn >> isNewShift;

    if (isNewShift) {
        signalMessageSplashScreen(tr("Открыта новая смена"));
    } else {
        signalMessageSplashScreen(tr("Уже имеется открытая смена"));
    }

    QShift shift;
    shift << streamIn;
    synchronization->setCurrentShift(shift);

    int id = -1;
    id = DatabaseCommands()->shift->getId(currentShift());

    if (id <= 0) {
        DatabaseCommands()->shift->add(currentShift().id, currentShift());
    } else {
        DatabaseCommands()->shift->edit(currentShift());
    }

    emit (signalShiftOpened());
    synchronization->synchronizationProcess();
}

void QNetManager::command0x09_closeShift(QByteArray &data)
{
    signalMessageSplashScreen(tr("Закрытие смены..."));
    QDataStream streamIn (&data,QIODevice::ReadOnly);
    streamIn.device()->seek(0);

    QShift shift;
    shift << streamIn;
    setCurrentShift(shift);

    DatabaseCommands()->shift->edit(shift);

    emit (signalShiftClosed());
}

void QNetManager::command0x0A_getReceipts(QByteArray &data)
{
    signalMessageSplashScreen(tr("Прием чеков..."));
    QDataStream streamIn (&data,QIODevice::ReadOnly);
    streamIn.device()->seek(0);

    bool result;
    quint16 count;

    streamIn >> result;
    streamIn >> count;

    int id;

    synchronization->receipts()->clear();
    QReceipt receipt;

    while (!streamIn.atEnd()) {
        receipt << streamIn;
        id = DatabaseCommands()->receipt->getId(receipt);
        synchronization->receipts()->push_back(receipt);

        if (id<=0) {
            DatabaseCommands()->receipt->add(receipt.id, receipt);
        } else {
            DatabaseCommands()->receipt->edit(receipt.id, receipt);
        }
    }

    emit (signalReceiptsLoaded());
    synchronization->synchronizationProcess();
}

void QNetManager::command0x0B_getSoldPositions(QByteArray &data)
{
    signalMessageSplashScreen(tr("Прием проданных позиций..."));
    QDataStream streamIn (&data,QIODevice::ReadOnly);
    streamIn.device()->seek(0);

    quint16 count;
    streamIn >> count;

    int id;
    QSoldPosition soldPos;
    while (!streamIn.atEnd()) {
        soldPos << streamIn;
        id = DatabaseCommands()->soldPosition->getId(soldPos);
        if (id <= 0) {
            DatabaseCommands()->soldPosition->add(soldPos.id, soldPos);
        } else {
            DatabaseCommands()->soldPosition->edit(soldPos.id, soldPos);
        }
    }

    emit (signalSoldPositionsLoaded());
    synchronization->synchronizationProcess();
}

void QNetManager::command0x0C_sentSale(QByteArray &data)
{
    signalMessageSplashScreen(tr("Получена информация о продаже"));

    QDataStream streamIn (&data,QIODevice::ReadOnly);
    streamIn.device()->seek(0);

    QReceipt currentReceipt;
    currentReceipt << streamIn;

    int id = DatabaseCommands()->receipt->getId(currentReceipt);
    if (id <= 0) {
        DatabaseCommands()->receipt->add(currentReceipt.id, currentReceipt);
    }
    else {
        DatabaseCommands()->receipt->edit(currentReceipt.id, currentReceipt);
    }

    QSoldPosition soldPos;
    while (!streamIn.atEnd()) {
        soldPos << streamIn;

        id = DatabaseCommands()->soldPosition->getId(soldPos);
        if (id <= 0) {
            DatabaseCommands()->soldPosition->add(soldPos.id, soldPos);
        }
        else {
            DatabaseCommands()->soldPosition->edit(soldPos.id, soldPos);
        }
    }
}

void QNetManager::command0x0F_getIdAllPointSales(QByteArray &data)
{
    this->signalMessageSplashScreen(tr("Получение всех айди точек продаж"));
    qDebug()<<"\n   command0x0F : Получение всех айди точек продаж ";
    QDataStream streamIn (&data,QIODevice::ReadOnly);
    streamIn.device()->seek(0);

    QVector<int> idPointSales;
    streamIn >> idPointSales;

    for(int i = 0; i < idPointSales.count(); i++) {
        this->CommandsToServer()->pointSale->loadInformation_0x10(idPointSales.at(i));
    }

    synchronization->synchronizationProcess();
}

void QNetManager::command0xB0_getPointSales(QByteArray &data)
{
    this->signalMessageSplashScreen(tr("Получение всех точек продаж"));
    qDebug()<<"\n   command0xB0 : Получение всех точек продаж ";
    QDataStream streamIn (&data,QIODevice::ReadOnly);
    streamIn.device()->seek(0);

    QPointSale pointSale;
    while (!streamIn.atEnd()) {
        QByteArray buf;
        streamIn >> buf;

        pointSale.fromByteArray(buf);
        int id = this->DatabaseCommands()->pointSale->getId(pointSale);
        if (id <= 0) {
            this->DatabaseCommands()->pointSale->add(pointSale.id, pointSale);
        }
        else {
            this->DatabaseCommands()->pointSale->edit(pointSale);
        }
    }

    synchronization->synchronizationProcess();
}

void QNetManager::command0x10_getPointSale(QByteArray &data)
{
    qDebug()<<"\n   command0x10 : " << "Прием информации о точке продаж";

    this->getPointSale(data);
}

void QNetManager::getPointSale(QByteArray &data)
{
    this->signalMessageSplashScreen(tr("Прием информации о точке продаж"));

    QPointSale pointSale;
    pointSale.fromByteArray(data);

    synchronization->setCurrentPointSale(pointSale);

    int id = this->DatabaseCommands()->pointSale->getId(pointSale);
    if (id <= 0) {
        this->DatabaseCommands()->pointSale->add(pointSale.id, pointSale);
    }
    else {
        this->DatabaseCommands()->pointSale->edit(pointSale);
    }

    emit(signalPointSaleInformationLoaded(pointSale));
}

void QNetManager::command0x11_getAllCategories(QByteArray &data)
{
    this->signalMessageSplashScreen(tr("Прием всех категорий"));

    QDataStream streamIn (&data, QIODevice::ReadOnly);
    streamIn.device()->seek(0);

    QSalesCategory category;
    int id;
    while (!streamIn.atEnd()) {

        category << streamIn;

        id = this->DatabaseCommands()->category->getId(category);
        if (id <= 0) {
            this->DatabaseCommands()->category->add(category.id, category);
        }
        else {
            this->DatabaseCommands()->category->edit(category);
        }
    }
    emit(signalCategoriesLoaded());

    synchronization->synchronizationProcess();
}

void QNetManager::command0x12_getAllProducts(QByteArray &data)
{
    this->signalMessageSplashScreen(tr("Прием всех товаров"));
    QDataStream streamIn (&data, QIODevice::ReadOnly);
    streamIn.device()->seek(0);

    QProduct product;
    int id;
    while (!streamIn.atEnd()) {
        product << streamIn;

        id = this->DatabaseCommands()->product->getId(product);
        if (id <= 0) {
            this->DatabaseCommands()->product->add(product.id, product);
        }
        else {
            this->DatabaseCommands()->product->edit(product);
        }
    }
    emit (this->signalProductsLoaded());

    synchronization->synchronizationProcess();
}

void QNetManager::command0x13_getAllPrices(QByteArray &data)
{
    this->signalMessageSplashScreen(tr("Прием всех цен"));
    QDataStream streamIn (&data,QIODevice::ReadOnly);
    streamIn.device()->seek(0);

    QPrice price;
    int id;

    while (!streamIn.atEnd()) {
        price << streamIn;

        id = this->DatabaseCommands()->price->getId(price);

        if (id <= 0) {
            this->DatabaseCommands()->price->add(price.id, price);
        }
        else {
            this->DatabaseCommands()->price->edit(price);
        }
    }
    emit (this->signalPricesLoaded());
    synchronization->synchronizationProcess();
}

void QNetManager::command0x14_getAllShifts(QByteArray &data)
{
    this->signalMessageSplashScreen(tr("Прием смен"));
    QDataStream streamIn (&data,QIODevice::ReadOnly);
    streamIn.device()->seek(0);

    QShift shift;
    while (!streamIn.atEnd()) {
        shift << streamIn;

        int id = this->DatabaseCommands()->shift->getId(shift);
        if (id <= 0) {
            this->DatabaseCommands()->shift->add(shift.id, shift);
        }
        else {
            this->DatabaseCommands()->shift->edit(shift);
        }
    }
    emit (this->signalShiftsLoaded());
    synchronization->synchronizationProcess();
}

void QNetManager::command0x15_getAllReceipts(QByteArray &data)
{
    this->signalMessageSplashScreen(tr("Прием всех чеков"));
    QDataStream streamIn (&data,QIODevice::ReadOnly);
    streamIn.device()->seek(0);
    qDebug() << "get all receipts";
    QReceipt receipt;
    while (!streamIn.atEnd()) {
        receipt << streamIn;

        if (receipt.id > 0) {
            int id = this->DatabaseCommands()->receipt->getId(receipt);
            if (id <= 0) {
                this->DatabaseCommands()->receipt->add(receipt.id, receipt);
            }
            else {
                this->DatabaseCommands()->receipt->edit(receipt.id, receipt);
            }
        }
    }

    emit (this->signalReceiptsLoaded());
    synchronization->synchronizationProcess();
}

void QNetManager::command0x16_getAllSoldPositions(QByteArray &data)
{
    this->signalMessageSplashScreen(tr("Прием всех проданных позиций"));
    qDebug() << "get all sold pos";
    QDataStream streamIn (&data,QIODevice::ReadOnly);
    streamIn.device()->seek(0);

    QSoldPosition soldPosition;
    while (!streamIn.atEnd()) {
        soldPosition << streamIn;

        if (soldPosition.id > 0) {
            int id = this->DatabaseCommands()->soldPosition->getIdWithoutReceipt(soldPosition);
            if (id <= 0) {
                this->DatabaseCommands()->soldPosition->add(soldPosition.id, soldPosition);
            }
            else {
                this->DatabaseCommands()->soldPosition->edit(soldPosition.id, soldPosition);
            }
        }
    }
    emit (this->signalSoldPositionsLoaded());
    synchronization->synchronizationProcess();
}

void QNetManager::command0xA0_sentProduct(QByteArray &data)
{
    signalMessageSplashScreen(tr("Данные о товаре отправлены на сервер"));

    QDataStream streamIn (&data,QIODevice::ReadOnly);
    streamIn.device()->seek(0);

    bool result;
    streamIn >> result;

    quint32 code;
    streamIn >> code;

    QProduct product;
    product << streamIn;

    emit(signalProductSent());
}

void QNetManager::command0x0D_sentPicture(QByteArray &data)
{
    this->signalMessageSplashScreen(tr("Картинка отправлена на сервер"));
    QDataStream streamIn (&data,QIODevice::ReadOnly);
    streamIn.device()->seek(0);

    bool result;
    QProductPicture picture;
    quint32 code;

    streamIn >> result;
    streamIn >> code;
    picture << streamIn;

    if (result) {
        if (static_cast<Database::Commands>(code) == Database::Commands::ADD) {
            this->DatabaseCommands()->picture->add(picture.id, picture);
        }
        else if (static_cast<Database::Commands>(code) == Database::Commands::EDIT) {
            this->DatabaseCommands()->picture->edit(picture);
        }
        emit (this->signalPictureSent());
    }
}

void QNetManager::command0x0E_getPicture(QByteArray &data)
{
    this->signalMessageSplashScreen(tr("Прием картинки"));
    QDataStream streamIn (&data,QIODevice::ReadOnly);
    streamIn.device()->seek(0);

    QProductPicture picture;
    picture << streamIn;

    this->DatabaseCommands()->picture->add(picture.id, picture);
    synchronization->getNextPictureIfExistOrNextStep();
}

void QNetManager::command0xB1_getAllPictures(QByteArray &data)
{
    this->signalMessageSplashScreen(tr("Прием всех картинок"));
    QDataStream streamIn (&data,QIODevice::ReadOnly);
    streamIn.device()->seek(0);

    DatabaseCommands()->picture->clear();
    QProductPicture picture;
    while (!streamIn.atEnd()) {
        picture << streamIn;
        if (picture.data != "") {
            DatabaseCommands()->picture->add(picture.id, picture);
        }
    }
    emit (signalPicturesLoaded());
}

void QNetManager::command0xB2_removePicture(QByteArray &data)
{
    this->signalMessageSplashScreen(tr("Ответ на удаление картинки от сервера"));
    auto removeData = remove(data);
    emit (signalRemovePicture(std::get<0>(removeData),
                              std::get<1>(removeData),
                              std::get<2>(removeData)));
}

void QNetManager::command0xB3_removeType(QByteArray &data)
{
    this->signalMessageSplashScreen(tr("Ответ на удаление типа от сервера"));
    auto removeData = remove(data);
    emit (signalRemoveType(std::get<0>(removeData),
                           std::get<1>(removeData),
                           std::get<2>(removeData)));
}

void QNetManager::command0xB4_sentType(QByteArray &data)
{
    this->signalMessageSplashScreen(tr("Картинка отправлена на сервер"));
    QDataStream streamIn (&data,QIODevice::ReadOnly);
    streamIn.device()->seek(0);

    bool result;
    QPaymentType type;
    quint32 code;

    streamIn >> result;
    streamIn >> code;
    type << streamIn;

    if (result) {
        emit (this->signalTypeSent());
    }
}

void QNetManager::command0xB5_removeVolume(QByteArray &data)
{
    this->signalMessageSplashScreen(tr("Ответ на удаление величины от сервера"));
    auto removeData = remove(data);
    emit (signalRemoveVolume(std::get<0>(removeData),
                             std::get<1>(removeData),
                             std::get<2>(removeData)));
}

void QNetManager::command0xB6_sentVolume(QByteArray &data)
{
    this->signalMessageSplashScreen(tr("Величина отправлена на сервер"));
    QDataStream streamIn (&data,QIODevice::ReadOnly);
    streamIn.device()->seek(0);

    bool result;

    streamIn >> result;

    if (result) {
        emit (this->signalVolumeSent());
    }
}

void QNetManager::command0xB7_removeUser(QByteArray &data)
{
    this->signalMessageSplashScreen(tr("Ответ на удаление пользователя от сервера"));
    auto removeData = remove(data);
    emit (signalRemoveUser(std::get<0>(removeData),
                           std::get<1>(removeData),
                           std::get<2>(removeData)));
}

void QNetManager::command0xB8_sentUser(QByteArray &data)
{
    this->signalMessageSplashScreen(tr("ПОльзователь отправлен на сервер"));
    QDataStream streamIn (&data,QIODevice::ReadOnly);
    streamIn.device()->seek(0);

    bool result;
    QUser user;

    streamIn >> result;
    user << streamIn;

    if (result) {
        if (user.id == synchronization->getCurrentUser().id) {
            synchronization->setCurrentUser(user);
        }
        emit (this->signalUserSent());
    }
}

void QNetManager::command0xB9_getAllUsers(QByteArray &data)
{
    this->signalMessageSplashScreen(tr("Прием смен"));
    QDataStream streamIn (&data,QIODevice::ReadOnly);
    streamIn.device()->seek(0);

    QUser user;
    while (!streamIn.atEnd()) {
        user << streamIn;

        int id = this->DatabaseCommands()->user->getId(user);
        if (id <= 0) {
            this->DatabaseCommands()->user->add(user.id, user);
        }
        else {
            this->DatabaseCommands()->user->edit(user);
        }
    }
    emit (this->signalUsersLoaded());
    synchronization->synchronizationProcess();
}

void QNetManager::command0xC1_sentPointSale(QByteArray &data)
{
    this->signalMessageSplashScreen(tr("Точка продаж отправлена на сервер"));
    QDataStream streamIn (&data,QIODevice::ReadOnly);
    streamIn.device()->seek(0);

    bool result;

    streamIn >> result;

    if (result) {
        emit (this->signalPointSaleSent());
    }
}

void QNetManager::command0xC2_removePointSale(QByteArray &data)
{
    this->signalMessageSplashScreen(tr("Ответ на удаление точки продаж от сервера"));

    auto removeData = remove(data);
    emit (signalRemovePointSale(std::get<0>(removeData),
                                std::get<1>(removeData),
                                std::get<2>(removeData)));
}

void QNetManager::command0xC3_sentCategory(QByteArray &data)
{
    this->signalMessageSplashScreen(tr("Категория отправлена на сервер"));
    QDataStream streamIn (&data,QIODevice::ReadOnly);
    streamIn.device()->seek(0);

    bool result;

    streamIn >> result;

    if (result) {
        emit (this->signalCategorySent());
    }
}

void QNetManager::command0xC4_removeCategory(QByteArray &data)
{
    this->signalMessageSplashScreen(tr("Ответ на удаление категории от сервера"));

    auto removeData = remove(data);
    emit (signalRemoveCategory(std::get<0>(removeData),
                               std::get<1>(removeData),
                               std::get<2>(removeData)));
}

void QNetManager::command0xC5_sentPrice(QByteArray &data)
{
    this->signalMessageSplashScreen(tr("Цена отправлена на сервер"));
    QDataStream streamIn (&data,QIODevice::ReadOnly);
    streamIn.device()->seek(0);

    bool result;

    streamIn >> result;

    if (result) {
        emit (this->signalPriceSent());
    }
}

void QNetManager::command0xC6_getReceiptsByDateRange(QByteArray &data)
{
    this->command0x15_getAllReceipts(data);
}

void QNetManager::command0xC7_getSoldPositionsByDateRange(QByteArray &data)
{
    this->command0x16_getAllSoldPositions(data);
}

void QNetManager::command0xC8_getStatistics(QByteArray &data)
{
    this->signalMessageSplashScreen(tr("Прием статистики"));
    QDataStream streamIn (&data,QIODevice::ReadOnly);
    streamIn.device()->seek(0);

    double maxValue;
    streamIn >> maxValue;

    QVector<QStatistics> statistics;
    while (!streamIn.atEnd()) {
        QStatistics stat;
        stat << streamIn;
        qDebug() << stat.toString();
        statistics.push_back(stat);
    }

    emit (this->signalStatisticsLoaded(statistics, maxValue));
}

void QNetManager::command0xA2_endSynchronization(QByteArray &data)
{
    this->signalMessageSplashScreen(tr("Конец синхронизации"));
    qDebug()<<"\n   command0xA2 : Конец синхронизации ";

    qDebug()<<"Server answer: ";
    qDebug()<<QString(data);

    emit(this->signalEndSynchronization());
}


std::tuple<bool, int, QString> QNetManager::remove(QByteArray &data)
{
    QDataStream streamIn (&data,QIODevice::ReadOnly);
    streamIn.device()->seek(0);

    bool result = false;
    int id;
    QString name;

    streamIn >> result;
    streamIn >> id;
    streamIn >> name;

    return {result, id, name};
}

