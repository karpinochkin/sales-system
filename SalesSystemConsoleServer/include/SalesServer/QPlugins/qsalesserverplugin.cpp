#include "qsalesserverplugin.h"

Plugins::QSalesServerPlugin::QSalesServerPlugin(QUnNetProtokolServer *server, quint16 business, QObject *parent)
    : QServerPlugin(server, business, parent)

{
    initPluginInformation();
}

Plugins::QSalesServerPlugin::~QSalesServerPlugin()
{

}

void Plugins::QSalesServerPlugin::initPluginInformation()
{
    currentPluginCode = 0x07; //Задается уникальный код плагина
    currentPluginName = "QSalesServerPlugin"; //Уникальное имя плагина
    currentVersion = 0x00000001; //Версия плагина
}

void Plugins::QSalesServerPlugin::dataBaseIsInit()
{
    databaseControl = new QDatabaseConrol(&dataBase, this);
}

void Plugins::QSalesServerPlugin::processCommand(quint8 command,
                                                 QByteArray data,
                                                 QUnClientHandler *client)
{
    qDebug() << command;
    switch (command) {
    case 0x01: command0x01_sendPointSale(data, client);
        break;
    case 0x02: command0x02_sendCategories(data,client);
        break;
    case 0x03: command0x03_sendProducts(data,client);
        break;
    case 0x04: command0x04_sendVolumes(data,client);
        break;
    case 0x05: command0x05_sendTypes(data,client);
        break;
    case 0x06: command0x06_sendPrices(data,client);
        break;
    case 0x07: command0x07_sendUser(data,client);
        break;
    case 0x08: command0x08_openShift(data,client);
        break;
    case 0x09: command0x09_closeShift(data,client);
        break;
    case 0x0A: command0x0A_sendReceipts(data,client);
        break;
    case 0x0B: command0x0B_sendSoldPositions(data,client);
        break;
    case 0x0C: command0x0C_getSale(data,client);
        break;
    case 0x0D: command0x0D_uploadPicture(data, client);
        break;
    case 0x0E: command0x0E_sendPicture(data, client);
        break;
    case 0x0F: command0x0F_sendIdAllPointSales(data, client);
        break;
    case 0x10: command0x10_sendPointSale(data, client);
        break;
    case 0x11: command0x11_sendAllCategories(data,client);
        break;
    case 0x12: command0x12_sendAllProducts(data,client);
        break;
    case 0x13: command0x13_sendAllPrices(data,client);
        break;
    case 0x14: command0x14_sendAllShifts(data,client);
        break;
    case 0x15: command0x15_sendAllReceipts(data,client);
        break;
    case 0x16: command0x16_sendAllSoldPositions(data,client);
        break;
    case 0xA0: command0xA0_getProduct(data,client);
        break;
    case 0xA1: command0xA1_handshake(data, client);
        break;
    case 0xA2: command0xA2_endSynchronization(data, client);
        break;
    case 0xB0: command0xB0_sendPointSales(data, client);
        break;
    case 0xB1: command0xB1_sendAllPictures(data, client);
        break;
    case 0xB2: command0xB2_removePicture(data, client);
        break;
    case 0xB3: command0xB3_removeType(data, client);
        break;
    case 0xB4: command0xB4_getType(data, client);
        break;
    case 0xB5: command0xB5_removeVolume(data, client);
        break;
    case 0xB6: command0xB6_getVolume(data, client);
        break;
    case 0xB7: command0xB7_removeUser(data, client);
        break;
    case 0xB8: command0XB8_getUser(data, client);
        break;
    case 0xB9: command0xB9_sendAllUsers(data, client);
        break;
    case 0xC1: command0xC1_getPointSale(data, client);
        break;
    case 0XC2: command0xC2_removePointSale(data, client);
        break;
    case 0xC3: command0xC3_getCategory(data, client);
        break;
    case 0xC4: command0xC4_removeCategory(data, client);
        break;
    case 0xC5: command0xC5_getPrice(data, client);
        break;
    case 0xC6: command0xC6_sendReceiptsByDateRange(data, client);
        break;
    case 0xC7: command0xC7_sendSoldPositionsByDateRange(data, client);
        break;
    case 0xC8: command0xC8_sendStatistics(data, client);
        break;
    }
}

void Plugins::QSalesServerPlugin::command0xA1_handshake(QByteArray &data,
                                                        QUnClientHandler *client)
{
    qDebug() << "\n   command0xA1 ";
    qDebug()<<client->getCurrentAccountInfo()->login<<":"<<" Рукопожатие ";

    qDebug() << QString(data);
    client->sendExtData(currentPluginCode, 0xA1, currentIdBusiness, data, true);
}

void Plugins::QSalesServerPlugin::command0x01_sendPointSale(QByteArray &data,
                                                            QUnClientHandler *client)
{
    qDebug() << "\n   command0x01";
    QByteArray Output = getCorrectPointSaleOutput(data, client);
    sendExtData(0x01,Output,client);
}

QByteArray Plugins::QSalesServerPlugin::getCorrectPointSaleOutput(QByteArray &data,
                                                                  QUnClientHandler *client)
{
    qDebug()<<client->getCurrentAccountInfo()->login<<":"<<" Получение информации о точке продаж ";
    QByteArray Output;
    QDataStream streamIn (&data,QIODevice::ReadOnly);

    int currentPointId;
    streamIn >> currentPointId;

    QPointSale currentPointSale = databaseControl->pointSale->get(currentPointId);

    Output = currentPointSale.toByteArray();
    return Output;
}

void Plugins::QSalesServerPlugin::command0x02_sendCategories(QByteArray &data,
                                                             QUnClientHandler *client)
{
    qDebug() << "\n   command0x02";
    qDebug()<<client->getCurrentAccountInfo()->login<<":"<<" Получение категорий ";

    QByteArray Output;
    quint16 count;
    QVector<int> idCategories;
    int currentIdCategory;

    QDataStream streamIn (&data,QIODevice::ReadOnly);
    streamIn.device()->seek(0);

    streamIn >> count;

    while (!streamIn.atEnd()) {
        streamIn >> currentIdCategory;
        idCategories.push_back(currentIdCategory);
    }

    QDataStream streamOut (&Output,QIODevice::ReadWrite);

    QSalesCategory category;
    for (int i = 0; i < idCategories.length(); i++) {
        category = databaseControl->category->get(idCategories.at(i));
        category >> streamOut;
    }

    sendExtData(0x02, Output, client);
}

void Plugins::QSalesServerPlugin::command0x03_sendProducts(QByteArray &data,
                                                           QUnClientHandler *client)
{
    qDebug() << "\n   command0x03";
    qDebug()<<client->getCurrentAccountInfo()->login<<":"<<" Получение списка товаров ";

    quint16 count;
    QByteArray Output;
    QDataStream streamIn (&data,QIODevice::ReadOnly);

    streamIn.device()->seek(0);
    streamIn >> count;

    QVector<int> idProducts;
    int idProduct;
    while (!streamIn.atEnd()) {
        streamIn >> idProduct;
        idProducts.push_back(idProduct);
    }

    QDataStream streamOut (&Output,QIODevice::ReadWrite);
    streamOut << count;
    QProduct product;
    for (int i=0;i<idProducts.length();i++) {
        product = databaseControl->product->get(idProducts.at(i));
        product >> streamOut;
    }

    sendExtData(0x03, Output, client);
}

void Plugins::QSalesServerPlugin::command0x04_sendVolumes(QByteArray &data,
                                                          QUnClientHandler *client)
{
    qDebug() << "\n   command0x04";
    qDebug()<<client->getCurrentAccountInfo()->login<<":"<<" Получение списка объемов товаров (единиц измерения и значений) ";

    quint16 count;
    QByteArray Output;
    QDataStream streamIn (&data,QIODevice::ReadOnly);

    streamIn.device()->seek(0);
    streamIn >> count;

    QVector<int> idProducts;
    int idProduct;
    while (!streamIn.atEnd()) {
        streamIn >> idProduct;
        idProducts.push_back(idProduct);
    }

    QVector<int> idVolumes;
    for (int i = 0; i < idProducts.size(); i++) {
        QVector<int> buf = databaseControl->product->getIdVolumes(idProducts.at(i));

        for (int j = 0; j < buf.size(); j++) {
            if(idVolumes.indexOf(buf.at(j)) < 0) {
                idVolumes.push_back(buf.at(j));
            }
        }
    }

    QDataStream streamOut (&Output,QIODevice::ReadWrite);
    streamOut << static_cast<quint16>(idVolumes.size());

    QVolumeProduct volume;
    for (int i = 0; i < idVolumes.size(); i++) {
        volume = databaseControl->volume->get(idVolumes.at(i));
        volume >> streamOut;
        qDebug() << volume.id << volume.description;
    }

    sendExtData(0x04, Output, client);
}

void Plugins::QSalesServerPlugin::command0x05_sendTypes(QByteArray &data,
                                                        QUnClientHandler *client)
{
    Q_UNUSED(data)
    qDebug() << "\n   command0x05";
    qDebug()<<client->getCurrentAccountInfo()->login<<":"<<" Получение типов товаров ";

    QByteArray Output;
    QVector<QPaymentType> types;
    QDataStream streamOut (&Output,QIODevice::ReadWrite);

    types = databaseControl->type->getTypes();
    streamOut << static_cast<quint16>(types.size());

    QPaymentType type;
    for (int i = 0; i < types.size(); ++i) {
        type = types.at(i);
        type >> streamOut;
    }

    sendExtData(0x05, Output, client);
}

void Plugins::QSalesServerPlugin::command0x06_sendPrices(QByteArray &data,
                                                         QUnClientHandler *client)
{
    qDebug() << "\n   command0x06";
    qDebug()<<client->getCurrentAccountInfo()->login<<":"<<" Получение цен ";
    int idPointSale;
    QByteArray Output;
    QVector<QPrice> prices;
    QDataStream streamIn (&data,QIODevice::ReadOnly);

    streamIn.device()->seek(0);
    streamIn >> idPointSale;
    prices = databaseControl->price->getPrices(idPointSale);

    QDataStream streamOut (&Output,QIODevice::ReadWrite);
    streamOut << static_cast<quint16>(prices.size());

    QPrice price;
    for (int i = 0; i < prices.size(); i++) {
        price = prices.at(i);
        price >> streamOut;
    }

    sendExtData(0x06, Output, client);
}

void Plugins::QSalesServerPlugin::command0x07_sendUser(QByteArray &data,
                                                       QUnClientHandler *client)
{
    Q_UNUSED(data)
    qDebug() << "\n   command0x07";
    qDebug()<<client->getCurrentAccountInfo()->login<<":"<<" Получение информации о пользователе ";

    QString login = client->getCurrentAccountInfo()->login;
    QUser user = databaseControl->user->get(login);

    QByteArray Output;
    QDataStream streamOut (&Output,QIODevice::ReadWrite);
    user >> streamOut;

    sendExtData(0x07, Output, client);
}

void Plugins::QSalesServerPlugin::command0x08_openShift(QByteArray &data,
                                                        QUnClientHandler *client)
{
    qDebug() << "\n   command0x08";
    qDebug()<<client->getCurrentAccountInfo()->login<<":"<<" Открытие смены ";

    QByteArray Output;
    int idUser;
    int idPointSale;
    QDataStream streamIn (&data,QIODevice::ReadOnly);

    streamIn.device()->seek(0);
    streamIn >> idPointSale;
    idUser = databaseControl->user->get(client->getCurrentAccountInfo()->login).id;

    bool newShift;
    QShift shift = databaseControl->shift->open(idUser, idPointSale, &newShift);

    QDataStream streamOut (&Output,QIODevice::ReadWrite);
    streamOut << newShift;
    shift >> streamOut;

    sendExtData(0x08, Output, client);
}

void Plugins::QSalesServerPlugin::command0x09_closeShift(QByteArray &data,
                                                         QUnClientHandler *client)
{
    qDebug() << "\n   command0x09";
    qDebug() << client->getCurrentAccountInfo()->login << ":" << " Закрытие смены ";

    QByteArray Output;
    QDataStream streamIn (&data,QIODevice::ReadOnly);
    streamIn.device()->seek(0);

    QShift shift;
    shift << streamIn;
    databaseControl->shift->close(shift);

    QDataStream streamOut (&Output,QIODevice::ReadWrite);
    shift >> streamOut;

    sendExtData(0x09, Output, client);
}

void Plugins::QSalesServerPlugin::command0x0A_sendReceipts(QByteArray &data,
                                                           QUnClientHandler *client)
{
    qDebug() << "\n   command0x0A";
    qDebug() << client->getCurrentAccountInfo()->login << ":" << " Получение чеков для смены ";

    QByteArray Output;
    QDataStream streamIn (&data,QIODevice::ReadOnly);
    streamIn.device()->seek(0);

    QShift shift;
    shift << streamIn;

    QVector<QReceipt> receipts = databaseControl->receipt->getReceipts(shift.id);

    bool result = true;
    QDataStream streamOut (&Output,QIODevice::ReadWrite);
    streamOut << result;
    streamOut << static_cast<quint16>(receipts.size());

    QReceipt receipt;
    for (int i = 0; i < receipts.size(); i++) {
        receipt = receipts.at(i);
        receipt >> streamOut;
    }

    sendExtData(0x0A, Output, client);
}

void Plugins::QSalesServerPlugin::command0x0B_sendSoldPositions(QByteArray &data,
                                                                QUnClientHandler *client)
{
    qDebug() << "\n   command0x0B";
    qDebug() << client->getCurrentAccountInfo()->login << ":" << " Получение проданных позиций ";

    quint16 count;
    QByteArray Output;
    QDataStream streamIn (&data,QIODevice::ReadOnly);
    streamIn.device()->seek(0);

    streamIn >> count;

    QVector<int> idReceipts;
    int id;
    while (!streamIn.atEnd()) {
        streamIn >> id;
        idReceipts.push_back(id);
    }

    QVector<QSoldPosition> soldPositions;
    QVector<QSoldPosition> currentSoldPositions;

    for (int i = 0; i < idReceipts.size(); i++) {
        currentSoldPositions = databaseControl->soldPosition->getSoldPositions(idReceipts.at(i));
        for (int j = 0; j < currentSoldPositions.size(); j++) {
            soldPositions.push_back(currentSoldPositions.at(j));
        }
    }

    QDataStream streamOut (&Output,QIODevice::ReadWrite);
    streamOut << static_cast<quint16>(soldPositions.size());

    QSoldPosition soldPosition;
    for (int i = 0; i < soldPositions.size(); i++) {
        soldPosition = soldPositions.at(i);
        soldPosition >> streamOut;
    }

    sendExtData(0x0B, Output, client);
}

void Plugins::QSalesServerPlugin::command0x0C_getSale(QByteArray &data,
                                                      QUnClientHandler *client)
{
    qDebug() << "\n   command0x0C";
    qDebug() << client->getCurrentAccountInfo()->login << ":" << " Получение продажи ";

    QDataStream streamIn (&data,QIODevice::ReadOnly);
    streamIn.device()->seek(0);
    QReceipt receipt;
    receipt << streamIn;

    int idReceipt = databaseControl->receipt->getId(receipt);
    if (idReceipt <= 0) {
        idReceipt = databaseControl->receipt->add(receipt);
    } else {
        databaseControl->receipt->edit(receipt);
    }
    receipt.id = idReceipt;

    QSoldPosition soldPosition;
    QVector<QSoldPosition> soldPositions;

    while (!streamIn.atEnd()) {
        soldPosition << streamIn;
        soldPosition.idReceipt = receipt.id;
        soldPosition.id = databaseControl->soldPosition->add(soldPosition);
        soldPositions.push_back(soldPosition);
    }

    QByteArray Output;
    QDataStream streamOut (&Output,QIODevice::ReadWrite);

    receipt >> streamOut;
    for (int i = 0; i < soldPositions.size(); i++) {
        soldPosition = soldPositions.at(i);
        soldPosition >> streamOut;
    }

    sendExtData(0x0C, Output, client);
}

void Plugins::QSalesServerPlugin::command0x0D_uploadPicture(QByteArray &data,
                                                            QUnClientHandler *client)
{
    qDebug() << "\n   command0x0D";
    qDebug() << client->getCurrentAccountInfo()->login << ":" << " Загрузка изображения ";
    QDataStream streamIn (&data,QIODevice::ReadOnly);
    streamIn.device()->seek(0);

    QProductPicture picture;
    picture << streamIn;

    bool result = false;
    quint32 code;
    if (picture.id <= 0) {
        picture.id = databaseControl->picture->add(picture);
        code = static_cast<quint32>(Database::Commands::ADD);
        if (picture.id != 0
                || picture.id != -1) {
            result = true;
        }
    }
    else {
        result = databaseControl->picture->edit(picture);
        code = static_cast<quint32>(Database::Commands::EDIT);
    }

    QByteArray output;
    QDataStream streamOut (&output, QIODevice::ReadWrite);
    qDebug() << picture.name << picture.id;

    streamOut << result;
    streamOut << code;
    picture >> streamOut;

    sendExtData(0x0D, output, client);
}


void Plugins::QSalesServerPlugin::command0x0E_sendPicture(QByteArray &data,
                                                          QUnClientHandler *client)
{
    qDebug() << "\n   command0x0E";
    qDebug() << client->getCurrentAccountInfo()->login << ":" << " Отправка клиенту изображения ";
    QDataStream streamIn (&data,QIODevice::ReadOnly);
    streamIn.device()->seek(0);

    int currentIdPicture;
    streamIn >> currentIdPicture;
    QProductPicture picture = databaseControl->picture->get(currentIdPicture);

    QByteArray Output;
    QDataStream streamOut (&Output,QIODevice::ReadWrite);

    picture >> streamOut;
    sendExtData(0x0E, Output, client);
}

void Plugins::QSalesServerPlugin::command0x0F_sendIdAllPointSales(QByteArray &data,
                                                                  QUnClientHandler *client)
{
    Q_UNUSED(data)
    qDebug() << "\n   command0x0F ";
    qDebug()<<client->getCurrentAccountInfo()->login<<":"<<" Получение id всех точек продаж ";

    QByteArray Output;
    QDataStream streamOut (&Output,QIODevice::ReadWrite);

    QVector<QPointSale> pointSales;
    QVector<int> idPointSales;
    pointSales = databaseControl->pointSale->getPointSales();

    for (int i = 0; i < pointSales.count(); i++) {
        if (pointSales.at(i).id != 255) {
            idPointSales.push_back(pointSales.at(i).id);
        }
    }
    streamOut << idPointSales;

    sendExtData(0x0F, Output, client);
}

void Plugins::QSalesServerPlugin::command0x10_sendPointSale(QByteArray &data,
                                                            QUnClientHandler *client)
{
    qDebug() << "\n   command0x10";
    QByteArray Output = getCorrectPointSaleOutput(data, client);
    sendExtData(0x10,Output,client);
}

void Plugins::QSalesServerPlugin::command0xB0_sendPointSales(QByteArray &data,
                                                             QUnClientHandler *client)
{
    Q_UNUSED(data)
    qDebug() << "\n   command0xB0 ";
    qDebug()<<client->getCurrentAccountInfo()->login<<":"<<" Получение всех точек продаж ";

    QByteArray Output;
    QDataStream streamOut (&Output,QIODevice::ReadWrite);

    QVector<QPointSale> pointSales;
    pointSales = databaseControl->pointSale->getPointSales();

    QPointSale pointSale;
    for (int i = 0; i < pointSales.size(); i++) {
        if (pointSales.at(i).id == 255) {
            pointSales.remove(i);
        } else {
            pointSale = pointSales.at(i);
            streamOut << pointSale.toByteArray();
        }
    }

    sendExtData(0xB0, Output, client);
}

void Plugins::QSalesServerPlugin::command0x11_sendAllCategories(QByteArray &data,
                                                                QUnClientHandler *client)
{
    Q_UNUSED(data)
    qDebug() << "\n   command0x11 ";
    qDebug() << client->getCurrentAccountInfo()->login << ":" << " Получение всех категорий ";

    QByteArray output = templateSendAll(databaseControl->category->getCategories(), data);
    sendExtData(0x11, output, client);
}

void Plugins::QSalesServerPlugin::command0x12_sendAllProducts(QByteArray &data,
                                                              QUnClientHandler *client)
{
    qDebug() << "\n   command0x12 ";
    qDebug() << client->getCurrentAccountInfo()->login << ":" << " Получение всех товаров ";

    QByteArray output = templateSendAll(databaseControl->product->getProducts(), data);
    sendExtData(0x12, output, client);
}

void Plugins::QSalesServerPlugin::command0x13_sendAllPrices(QByteArray &data,
                                                            QUnClientHandler *client)
{
    qDebug() << "\n   command0x13 ";
    qDebug() << client->getCurrentAccountInfo()->login << ":" << " Получение всех цен ";

    QByteArray output = templateSendAll(databaseControl->price->getPrices(), data);
    sendExtData(0x13, output, client);
}

void Plugins::QSalesServerPlugin::command0x14_sendAllShifts(QByteArray &data,
                                                            QUnClientHandler *client)
{
    qDebug() << "\n   command0x14 ";
    qDebug() << client->getCurrentAccountInfo()->login << ":" << " Получение всех смен ";

    QByteArray output = templateSendAll(databaseControl->shift->getShifts(), data);
    sendExtData(0x14, output, client);
}

void Plugins::QSalesServerPlugin::command0x15_sendAllReceipts(QByteArray &data,
                                                              QUnClientHandler *client)
{
    qDebug() << "\n   command0x15 ";
    qDebug() << client->getCurrentAccountInfo()->login << ":" << " Получение всех чеков ";

    QByteArray output = templateSendAll(databaseControl->receipt->getReceipts(), data);
    sendExtData(0x15, output, client);
}

void Plugins::QSalesServerPlugin::command0x16_sendAllSoldPositions(QByteArray &data,
                                                                   QUnClientHandler *client)
{
    qDebug() << "\n   command0x16 ";
    qDebug() << client->getCurrentAccountInfo()->login << ":" << " Получение всех проданных позиций ";

    QByteArray output = this->templateSendAll(databaseControl->soldPosition->getSoldPositions(), data);
    sendExtData(0x16, output, client);
}

void Plugins::QSalesServerPlugin::command0xA0_getProduct(QByteArray &data,
                                                         QUnClientHandler *client)
{
    qDebug() << "\n   command0xA0 ";
    qDebug() << client->getCurrentAccountInfo()->login << ":" << " Получение товара ";

    quint32 code;
    QProduct product;
    QDataStream streamIn (&data,QIODevice::ReadOnly);

    streamIn.device()->seek(0);
    streamIn >> code;
    product << streamIn;

    switch (static_cast<Database::Commands>(code)) {
    case Database::Commands::ADD: databaseControl->product->add(product);
        break;
    case Database::Commands::EDIT: databaseControl->product->edit(product);
        break;
    case Database::Commands::REMOVE: qDebug()<<"delete drink info";
        break;
    }

    QByteArray Output;
    bool result = true;
    QDataStream streamOut (&Output, QIODevice::ReadWrite);

    streamOut << result;
    streamOut << code;
    product >> streamOut;

    sendExtData(0xA0, Output, client);
}

void Plugins::QSalesServerPlugin::command0xA2_endSynchronization(QByteArray &data,
                                                                 QUnClientHandler *client)
{
    qDebug() << "\n   command0xA2 ";
    qDebug()<<client->getCurrentAccountInfo()->login<<":"<<" Завершение синхронизации ";

    qDebug() << QString(data);
    client->sendExtData(currentPluginCode, 0xA2, currentIdBusiness, data, true);
}

void Plugins::QSalesServerPlugin::command0xB1_sendAllPictures(QByteArray &data,
                                                              QUnClientHandler *client)
{
    qDebug() << "\n   command0xB1 ";
    qDebug()<<client->getCurrentAccountInfo()->login<<":"<<" Запрос всех картинок ";

    QByteArray output = templateSendAll(databaseControl->picture->getPictures(), data);
    sendExtData(0xB1, output, client);
}

void Plugins::QSalesServerPlugin::command0xB2_removePicture(QByteArray &data,
                                                            QUnClientHandler *client)
{
    qDebug() << "\n   command0xB2 ";
    qDebug()<<client->getCurrentAccountInfo()->login<<":"<<" Удаление картинки ";

    QByteArray output = templateRemove(databaseControl->picture, data);
    sendExtData(0xB2, output, client);

}

void Plugins::QSalesServerPlugin::command0xB3_removeType(QByteArray &data, QUnClientHandler *client)
{
    qDebug() << "\n   command0xB3 ";
    qDebug()<<client->getCurrentAccountInfo()->login<<":"<<" Удаление типа продажи ";

    QByteArray output = templateRemove(databaseControl->type, data);
    sendExtData(0xB3, output, client);
}

void Plugins::QSalesServerPlugin::command0xB4_getType(QByteArray &data, QUnClientHandler *client)
{
    qDebug() << "\n   command0xB4";
    qDebug() << client->getCurrentAccountInfo()->login << ":" << " Загрузка типа оплаты ";
    QDataStream streamIn (&data,QIODevice::ReadOnly);
    streamIn.device()->seek(0);

    QPaymentType type;
    type << streamIn;

    bool result = false;
    quint32 code;

    if (type.id <= 0) {
        type.id = databaseControl->type->add(type);
        code = static_cast<quint32>(Database::Commands::ADD);
        if (type.id != 0
                || type.id != -1) {
            result = true;
        }
    }
    else {
        result = databaseControl->type->edit(type);
        code = static_cast<quint32>(Database::Commands::EDIT);
    }

    QByteArray output;
    QDataStream streamOut (&output, QIODevice::ReadWrite);

    streamOut << result;
    streamOut << code;
    type >> streamOut;

    sendExtData(0xB4, output, client);
}

void Plugins::QSalesServerPlugin::command0xB5_removeVolume(QByteArray &data, QUnClientHandler *client)
{
    qDebug() << "\n   command0xB5 ";
    qDebug()<<client->getCurrentAccountInfo()->login<<":"<<" Удаление величины ";

    QByteArray output = templateRemove(databaseControl->volume, data);
    sendExtData(0xB5, output, client);
}

void Plugins::QSalesServerPlugin::command0xB6_getVolume(QByteArray &data, QUnClientHandler *client)
{
    qDebug() << "\n   command0xB6";
    qDebug() << client->getCurrentAccountInfo()->login << ":" << " Загрузка величины ";
    QVolumeProduct volume;
    QByteArray output = templateGet(databaseControl->volume, volume, data);
    sendExtData(0xB6, output, client);
}

void Plugins::QSalesServerPlugin::command0xB7_removeUser(QByteArray &data, QUnClientHandler *client)
{
    qDebug() << "\n   command0xB7 ";
    qDebug()<<client->getCurrentAccountInfo()->login<<":"<<" Удаление пользователя ";

    QByteArray output = templateRemove(databaseControl->user, data);
    sendExtData(0xB7, output, client);
}

void Plugins::QSalesServerPlugin::command0XB8_getUser(QByteArray &data, QUnClientHandler *client)
{
    qDebug() << "\n   command0xB8";
    qDebug() << client->getCurrentAccountInfo()->login << ":" << " Загрузка пользователя ";

    QUser user;
    QByteArray output = templateGet(databaseControl->user, user, data);
    sendExtData(0xB8, output, client);
}

void Plugins::QSalesServerPlugin::command0xB9_sendAllUsers(QByteArray &data, QUnClientHandler *client)
{
    qDebug() << "\n   command0xB9 ";
    qDebug() << client->getCurrentAccountInfo()->login << ":" << " Получение всех пользователей ";

    QByteArray output = templateSendAll(databaseControl->user->getUsers(), data);
    sendExtData(0xB9, output, client);
}

void Plugins::QSalesServerPlugin::command0xC1_getPointSale(QByteArray &data, QUnClientHandler *client)
{
    qDebug() << "\n   command0xC1";
    qDebug() << client->getCurrentAccountInfo()->login << ":" << " Загрузка точки продаж ";
    QDataStream streamIn (&data,QIODevice::ReadOnly);
    streamIn.device()->seek(0);

    QByteArray buf;
    streamIn >> buf;

    QPointSale pointSale;
    pointSale.fromByteArray(buf);

    bool result = false;
    if (pointSale.id <= 0) {
        pointSale.id = databaseControl->pointSale->add(pointSale);

        if (pointSale.id != 0
                || pointSale.id != -1) {
            result = true;
        }
    }
    else {
        result = databaseControl->pointSale->edit(pointSale);
    }

    QByteArray output;
    QDataStream streamOut (&output, QIODevice::ReadWrite);

    streamOut << result;

    sendExtData(0xC1, output, client);
}

void Plugins::QSalesServerPlugin::command0xC2_removePointSale(QByteArray &data, QUnClientHandler *client)
{
    qDebug() << "\n   command0xC2 ";
    qDebug()<<client->getCurrentAccountInfo()->login<<":"<<" Удаление точки продаж ";

    QByteArray output = templateRemove(databaseControl->pointSale, data);
    sendExtData(0xC2, output, client);
}

void Plugins::QSalesServerPlugin::command0xC3_getCategory(QByteArray &data, QUnClientHandler *client)
{
    qDebug() << "\n   command0xC3";
    qDebug() << client->getCurrentAccountInfo()->login << ":" << " Загрузка категории ";

    QSalesCategory category;
    QByteArray output = templateGet(databaseControl->category, category, data);
    sendExtData(0xC3, output, client);
}

void Plugins::QSalesServerPlugin::command0xC4_removeCategory(QByteArray &data, QUnClientHandler *client)
{
    qDebug() << "\n   command0xC4 ";
    qDebug()<<client->getCurrentAccountInfo()->login<<":"<<" Удаление категории ";

    QByteArray output = templateRemove(databaseControl->category, data);
    sendExtData(0xC4, output, client);
}

void Plugins::QSalesServerPlugin::command0xC5_getPrice(QByteArray &data, QUnClientHandler *client)
{
    qDebug() << "\n   command0xC5";
    qDebug() << client->getCurrentAccountInfo()->login << ":" << " Загрузка цены ";

    QPrice price;
    QByteArray output = templateGet(databaseControl->price, price, data);
    sendExtData(0xC5, output, client);
}

void Plugins::QSalesServerPlugin::command0xC6_sendReceiptsByDateRange(QByteArray &data, QUnClientHandler *client)
{
    qDebug() << "\n   command0xC6 ";
    qDebug() << client->getCurrentAccountInfo()->login << ":" << " Получение всех чеков из диапазона дат ";
    QDataStream streamIn (&data,QIODevice::ReadOnly);
    streamIn.device()->seek(0);

    QDateTime startDate;
    QDateTime endDate;
    streamIn >> startDate;
    streamIn >> endDate;
    QByteArray output = templateSendAllByDateRange(
                databaseControl->receipt->getReceipts(startDate, endDate));
    sendExtData(0xC6, output, client);
}

void Plugins::QSalesServerPlugin::command0xC7_sendSoldPositionsByDateRange(QByteArray &data, QUnClientHandler *client)
{
    qDebug() << "\n   command0xC7 ";
    qDebug() << client->getCurrentAccountInfo()->login << ":" << " Получение всех проданных позиций из диапазона дат ";
    QDataStream streamIn (&data,QIODevice::ReadOnly);
    streamIn.device()->seek(0);

    QDateTime startDate;
    QDateTime endDate;
    streamIn >> startDate;
    streamIn >> endDate;

    QByteArray output = templateSendAllByDateRange(
                databaseControl->soldPosition->getSoldPositions(startDate, endDate));
    sendExtData(0xC7, output, client);
}

void Plugins::QSalesServerPlugin::command0xC8_sendStatistics(QByteArray &data, QUnClientHandler *client)
{
    qDebug() << "\n   command0xC8 ";
    qDebug() << client->getCurrentAccountInfo()->login << ":" << " Запрос на получение статистики из диапазона дат ";
    QDataStream streamIn (&data,QIODevice::ReadOnly);
    streamIn.device()->seek(0);

    StatisticsInput info;
    info << streamIn;

    QStatisticsGetter statGetter(databaseControl, info);
    double maxValue = statGetter.getMaxValue();
    QVector<QStatistics> statistics  = statGetter.get();

    QByteArray output;
    QDataStream streamOut (&output, QIODevice::ReadWrite);

    streamOut << maxValue;
    for (auto val : statistics) {
        val >> streamOut;
    }

    qDebug() << "send";
    sendExtData(0xC8, output, client);
}


template<typename T>
QByteArray Plugins::QSalesServerPlugin::templateSendAll(const QVector<T> &vector,
                                                        QByteArray &data)
{
    QByteArray Output;
    QDataStream streamIn (&data, QIODevice::ReadOnly);
    streamIn.device()->seek(0);

    QDataStream streamOut (&Output, QIODevice::ReadWrite);
    for (auto val : vector) {
        val >> streamOut;
    }
    return Output;
}

template<typename T>
QByteArray Plugins::QSalesServerPlugin::templateSendAllByDateRange(const QVector<T> &vector)
{
    QByteArray Output;

    QDataStream streamOut (&Output,QIODevice::ReadWrite);
    for (auto val : vector) {
        val >> streamOut;
    }

    return Output;
}

template<typename T>
QByteArray Plugins::QSalesServerPlugin::templateRemove(T *command, QByteArray &data)
{
    int id;
    QString name;
    QDataStream streamIn (&data, QIODevice::ReadOnly);
    streamIn.device()->seek(0);

    streamIn >> id;
    streamIn >> name;

    bool result = command->remove(id, name);

    QByteArray Output;
    QDataStream streamOut (&Output, QIODevice::ReadWrite);

    streamOut << result;
    streamOut << id;
    streamOut << name;

    return Output;
}

template<typename TCommand, typename TValue>
QByteArray Plugins::QSalesServerPlugin::templateGet(TCommand *command, TValue &value, QByteArray &data)
{
    QDataStream streamIn (&data,QIODevice::ReadOnly);
    streamIn.device()->seek(0);
    value << streamIn;

    bool result = false;
    if (value.id <= 0) {
        value.id = command->add(value);

        if (value.id != 0
                || value.id != -1) {
            result = true;
        }
    }
    else {
        result = command->edit(value);
    }
    QByteArray output;
    QDataStream streamOut (&output, QIODevice::ReadWrite);
    streamOut << result;

    return output;
}
