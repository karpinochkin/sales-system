#include "middlewareqml.h"

MiddlewareQML::MiddlewareQML(QObject *parent)
    : QObject(parent)
{
    productImageProvider = new ProductImageProvider(QQmlImageProviderBase::Image, this);

    settings = new QSettings("Sales/SalesClient");

    // enter for get hosts
    netManager = new QNetManager(true, settings, this);

    qmlProperty = new QQmlPropertyMap(this);
    getLoginFromSettings();

}

void MiddlewareQML::saveIdPointSaleInSettings()
{
    if (qmlProperty->value("idPointSaleInOptions") != 0) {
        settings->setValue("idPointSaleInOptions", qmlProperty->value("idPointSaleInOptions"));
    }
    else {
        settings->setValue("idPointSaleInOptions", QVariant("255"));
    }
}

void MiddlewareQML::getIdPointSaleFromSettings()
{
    if (settings->contains("idPointSaleInOptions")) {
        qmlProperty->insert("idPointSaleInOptions", settings->value("idPointSaleInOptions"));
    }
    else {
        qmlProperty->insert("idPointSaleInOptions", QVariant(255));
    }
}

void MiddlewareQML::saveLoginInSettings()
{
    settings->setValue("login", qmlProperty->value("login"));
    settings->setValue("password", qmlProperty->value("password"));
}

void MiddlewareQML::getLoginFromSettings()
{
    if (settings->value("login") == "") {
        qmlProperty->insert("login", QVariant("admin"));
    }
    else {
        qmlProperty->insert("login", settings->value("login").toString());
    }

    if (settings->value("password") == "") {
        qmlProperty->insert("password", QVariant(""));
    }
    else {
        qmlProperty->insert("password", settings->value("password").toString());
    }
}

void MiddlewareQML::saveHostPortInMiddleware()
{
    HostInfo newHost;
    newHost.address = qmlProperty->value("address").toString();
    if ((qmlProperty->value("port").toInt() <0) ||
            (qmlProperty->value("port").toInt() >65535) ||
            (!qmlProperty->value("port").toInt()))
    {
        emit (signalPortInvalid());
        vectorForSaveHosts.clear();
        return;
    }
    newHost.port = qmlProperty->value("port").toInt();
    vectorForSaveHosts.append(newHost);
}

void MiddlewareQML::saveHostPortInSettings()
{
    netManager->setHosts(vectorForSaveHosts);
    vectorForSaveHosts.clear();
}

void MiddlewareQML::fillHostPortFromSetings()
{
    auto hosts = netManager->hosts();

    for (auto host : hosts) {
        qmlProperty->insert("address", host.address);
        qmlProperty->insert("port", QString::number(host.port));
        emit (signalHostPortCreate());
    }
}

bool MiddlewareQML::isAndroid()
{
#ifdef Q_OS_ANDROID
    return true;
#else
    return false;
#endif
}

void MiddlewareQML::getImage(int id)
{
    QImage image;
    QProductPicture picture = netManager->DatabaseCommands()->picture->get(
                netManager->DatabaseCommands()->product->get(id).idPicture
                );
    image.loadFromData(picture.data);

    emit (signalSendImage(image));
}

void MiddlewareQML::getWarnings(const QList<QQmlError>& err)
{
    qDebug() << err;
}

void MiddlewareQML::fillCategoryTabs()
{
    QVector<QSalesCategory> categories = netManager->DatabaseCommands()->
            category->getCategories();

    for (auto category : categories) {
        QColorConsole categoryColor = category.color;
        QColor color;
        color.setRgb(categoryColor.red(),categoryColor.green(),categoryColor.blue());

        qmlProperty->insert("tabsName", QVariant(category.name));
        qmlProperty->insert("idCategory", QVariant(category.id));
        qmlProperty->insert("colorForCategory", QVariant(color.name()));

        emit (signalCategoryTabsCreate());
    }
}

void MiddlewareQML::fillProducts(int idCategory)
{
    auto a = netManager->DatabaseCommands()->product->getProducts();

    QVector<QProduct> products = netManager->DatabaseCommands()
            ->product->getProducts(idCategory);

    for (auto product : products) {
        QColorConsole productColor = product.color;
        QColor color;
        color.setRgb(productColor.red(),
                     productColor.green(),
                     productColor.blue());

        qmlProperty->insert("name", QVariant(product.name));
        qmlProperty->insert("idProduct", QVariant(product.id));
        qmlProperty->insert("colorCode", QVariant(color.name()));
        qmlProperty->insert("idCategory", QVariant(idCategory));

        emit (signalProductsListCreate());
    }
}

void MiddlewareQML::fillVolumes(int idProduct)
{
    QVector<QVolumeProduct> volumes = netManager->DatabaseCommands()
            ->volume->getVolumes(idProduct);
    for (auto volume : volumes) {
        qmlProperty->insert("nameVolume", QVariant(volume.name));
        qmlProperty->insert("idVolume", QVariant(volume.id));
        qmlProperty->insert("volume", QVariant(volume.volume));
        qmlProperty->insert("volumeUnits", QVariant(volume.units));

        emit (signalVolumesListCreate());
    }
}

void MiddlewareQML::fillPaymentTypes()
{
    QVector<QPaymentType> types = netManager->DatabaseCommands()
            ->type->getTypes();
    for (auto type : types) {
        qmlProperty->insert("nameVarietyOfPay", QVariant(type.name));
        qmlProperty->insert("idVarietyOfPay", QVariant(type.id));

        emit (signalPaymentTypesListCreate());
    }
}

void MiddlewareQML::fillReceipts()
{
    // cash payment
    int cash = 0;
    double sumCash = 0.0;

    // non-cash payment
    int nonCash = 0;
    double sumNonCash = 0;

    // free product
    int free = 0;

    QVector<QReceipt> receipts = netManager->DatabaseCommands()
            ->receipt->getReceipts(netManager->currentShift().id);

    for (int i = 0; i < receipts.size(); i++) {
        QVector<QSoldPosition> soldPositions = netManager->DatabaseCommands()
                ->soldPosition->getSoldPositions(receipts.at(i).id);

        for (auto soldPosition : soldPositions) {
            QPaymentType paymentType = netManager->DatabaseCommands()
                    ->type->get(soldPosition.idTypeProduct);

            if (paymentType.id == PaymentType::Cash) {
                ++cash;
                sumCash += netManager->DatabaseCommands()
                        ->price->get(soldPosition.idPrice).value;
            }
            else if (paymentType.id == PaymentType::NonCash) {
                ++nonCash;
                sumNonCash += netManager->DatabaseCommands()
                        ->price->get(soldPosition.idPrice).value;
            }
            else if (paymentType.id == PaymentType::Free) {
                ++free;
            }
        }

        qmlProperty->insert("countReceipt", QVariant(i+1));

        QString productsCountString = tr("Товаров: ") + QString::number(soldPositions.count()) + tr(" шт.");
        qmlProperty->insert("countProductsString", QVariant(productsCountString));

        QString receiptSumString = tr("Сумма: ") + QString::number(receipts.at(i).sum) + tr(" руб.");
        qmlProperty->insert("sumReceiptString", QVariant(receiptSumString));
        qmlProperty->insert("dateReceiptString", QVariant(receipts.at(i).dateTime.toString("d MMM в hh:mm:ss")));
        qmlProperty->insert("idReceipt", QVariant(receipts.at(i).id));

        emit (signalReceiptsCreate());
    }

    QString cashString = tr("За наличные: ") + QString::number(cash) + tr(" шт. на сумму ") + QString::number(sumCash) + tr(" руб.");
    qmlProperty->insert("cashString", QVariant(cashString));

    QString nonCashString = tr("За безналичные: ") + QString::number(nonCash) + tr(" шт. на сумму ") + QString::number(sumNonCash) + tr(" руб.");
    qmlProperty->insert("nonCashString", QVariant(nonCashString));

    QString freeString = tr("Бесплатные ") + QString::number(free) + tr(" шт.");
    qmlProperty->insert("freeString", QVariant(freeString));

    emit (signalFillSomePropertyInReportView());
}

void MiddlewareQML::fillSoldPositions(int idReceipt)
{
    QVector<QSoldPosition> soldPositions = netManager->DatabaseCommands()
            ->soldPosition->getSoldPositions(idReceipt);

    int counter = 0;
    for (auto soldPosition : soldPositions) {
        QProduct product = netManager->DatabaseCommands()
                ->product->get(soldPosition.idProduct);

        QColorConsole drinkColor = product.color;
        QColor color;
        color.setRgb(drinkColor.red(),drinkColor.green(),drinkColor.blue());

        QPaymentType type = netManager->DatabaseCommands()
                ->type->get(soldPosition.idTypeProduct);
        QString priceString;

        if (type.id == PaymentType::Cash) {
            priceString = QString::number(
                        netManager->DatabaseCommands()
                        ->price->get(soldPosition.idPrice).value
                        )
                    + tr(" руб.\nНаличные");
        }
        else if (type.id == PaymentType::NonCash) {
            priceString = QString::number(
                        netManager->DatabaseCommands()
                        ->price->get(soldPosition.idPrice).value
                        )
                    + tr(" руб.\nБезналичные");
        }
        else if (type.id == PaymentType::Free) {
            priceString = tr("\nБесплатный");
        }

        QVolumeProduct volume = netManager->DatabaseCommands()
                ->volume->get(soldPosition.idVolumeProduct);

        QString categoryString = netManager->DatabaseCommands()
                ->category->get(
                    netManager->DatabaseCommands()
                    ->price->get(soldPosition.idPrice).idProductCategory
                    ).name;
        QString volumeString = volume.name + "\n"
                + QString::number(volume.volume)
                + " " + volume.units;
        QString productNameString = QString::number(counter + 1) + ") "
                + product.name;


        qmlProperty->insert("categoryString", QVariant(categoryString));
        qmlProperty->insert("volumeString",QVariant(volumeString));
        qmlProperty->insert("priceString",QVariant(priceString));
        qmlProperty->insert("nameProductString", QVariant(productNameString));
        qmlProperty->insert("colorCode", QVariant(color.name()));
        qmlProperty->insert("idProduct", QVariant(product.id));

        ++counter;
        emit (signalSoldPositionsCreate());
    }
}

void MiddlewareQML::createReceipt(int countSoldPositions)
{
    QVector<QSoldPosition> soldPositions;
    int currentUserID = netManager->getCurrentUser().id;
    QString totalSum = qmlProperty->value("rubles").toString()
            + "." + qmlProperty->value("coins").toString();

    for (int i = 0; i < countSoldPositions; ++i) {
        QSoldPosition newSoldPosition;
        emit (signalGetSomePropertyForSoldPosition(i));
        newSoldPosition.idUser = currentUserID;
        newSoldPosition.count = 1;
        newSoldPosition.idProduct = qmlProperty->value("idProductForSoldPosition").toInt();
        newSoldPosition.idTypeProduct = qmlProperty->value("idTypeProductForSoldPosition").toInt();
        newSoldPosition.idPrice  = qmlProperty->value("idPriceForSoldPosition").toInt();
        newSoldPosition.idVolumeProduct =  qmlProperty->value("idVolumeForSoldPosition").toInt();
        newSoldPosition.numberInReceipt = i + 1;

        soldPositions.append(newSoldPosition);
    }

    QReceipt newReceipt;
    int currentShiftID = netManager->currentShift().id;

    newReceipt.idShift = currentShiftID;
    newReceipt.dateTime = QDateTime::currentDateTimeUtc();
    newReceipt.sum = totalSum.toDouble();

    netManager->sale(newReceipt, soldPositions);
}

bool MiddlewareQML::getPrice(int idCategory,
                             int idProduct,
                             int idVolume)
{
    QPrice price = netManager->DatabaseCommands()->price->get(idCategory,
                                                              idProduct,
                                                              idVolume);
    qmlProperty->insert("idPrice", QVariant(price.id));

    QStringList list;
    for (auto item : QString::number(price.value, 'g', 2).split(".")) {
        list.push_back(item);
    }
    qmlProperty->insert("rubles", QVariant(list[0]));

    if (list.size() > 1) {
        if (list[1].length() == 1) {
            list[1] += '0';
        }

        qmlProperty->insert("coins", QVariant(list[1]));
        return true;
    }
    return false;
}

void MiddlewareQML::connectToHost()
{
    // delete old net manager if exist
    if (netManager != nullptr) {
        delete netManager;
    }

    // enter from specific point sale
    int pointSaleID = settings->value("idPointSaleInOptions").toInt();
    netManager = new QNetManager(pointSaleID, settings, this);
    netManager->setObjectName("netManager");

    connect(productImageProvider, &ProductImageProvider::signalGetImageFromDB,
            this, &MiddlewareQML::getImage);
    connect(this, &MiddlewareQML::signalSendImage,
            productImageProvider, &ProductImageProvider::slotGetImageFromDB);
    connect(netManager, &QNetManager::signalAuthorized,
            this, &MiddlewareQML::authorized);
    connect(netManager, &QNetManager::signalUnError,
            this, &MiddlewareQML::error);
    connect(netManager, &QNetManager::signalMessageSplashScreen,
            this, &MiddlewareQML::signalMessageSplashScreen);
    connect(netManager, &QNetManager::signalEndSynchronization,
            this, &MiddlewareQML::endSynchronization);

    qDebug() << 1;
    netManager->setAccount(qmlProperty->value("login").toString(),qmlProperty->value("password").toString());
    qDebug() << 2;
    qDebug() << vectorForSaveHosts.size();
    for (auto i : vectorForSaveHosts) {
        qDebug () << i.port << i .address;
    }
    netManager->clientConnect();
    qDebug() << 3;
}

void MiddlewareQML::disconnectFromHost()
{
    netManager->closeShift();
    netManager->Disconnect();
}

void MiddlewareQML::exitApp()
{
    qmlProperty->deleteLater();
    qGuiApp->quit();
}

void MiddlewareQML::authorized()
{

}

void MiddlewareQML::error(UnErr err)
{
    switch (err) {
    case UnErr::errAuthNone : {
        qDebug() << "none error";
    }
        break;
    case UnErr::errAuthLogin: {
        qmlProperty->insert("errorString", "Логин введён неправильно");
        qDebug()<<"Login Error";
    }
        break;
    case UnErr::errAuthPassword: {
        qDebug()<<"Password Error";
        qmlProperty->insert("errorString", "Пароль введён неправильно");
    }
        break;
    case UnErr::errAuthBlock: {
        qDebug()<<"User is blocked";
        qmlProperty->insert("errorString", "Этот аккаунт заблокирован");
    }
        break;
    case UnErr::errAuthServWork: {
        qDebug()<<"Server not work";
        qmlProperty->insert("errorString", "Сервер не работает");
    }
        break;
    case UnErr::errNoRights: {
        qDebug()<<"Not rights";
        qmlProperty->insert("errorString", "У вас нет прав");
    }
        break;
    case UnErr::errNoAuthorized: {
        qDebug()<<"No authorized";
        qmlProperty->insert("errorString", "Авторизация не прошла");
    }
        break;

    }

    emit (signalBadAuthorized());
}

void MiddlewareQML::endSynchronization()
{
    fillCategoryTabs();

    QShift shift = netManager->currentShift();
    shift.openTime.setTimeSpec(Qt::UTC);
    QDateTime localTime = shift.openTime.toLocalTime();

    QUser user = netManager->DatabaseCommands()->user->get(shift.idUser);
    qmlProperty->insert("patronymicAndName", QVariant(user.patronymic +" "+user.name));
    qmlProperty->insert("openData", localTime.toString("d MMM в hh:mm:ss"));

    emit (signalFillOpenDate());
    emit (signalFinishCreateTabs());
    emit (signalGoodAuthorized());
}
