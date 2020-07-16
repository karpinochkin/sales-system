#include "statisticshandlers.h"

using namespace Statistics;

QMoney::QMoney(QDatabaseConrol *db)
    : db(db)
{

}

QVector<QVariant> QMoney::getFirstVector()
{
    QVector<QPointSale> pointSales = db->pointSale->getPointSales();

    QVector<QVariant> output;
    for(auto pointSale : pointSales) {
        output.push_back(QVariant::fromValue(pointSale));
    }
    return output;
}

QString QMoney::getKey(QVariant &val)
{
    return unpack<QPointSale>(val).name;
}

QVector<QVariant> QMoney::getSecondVector(QVariant &val, QDateTime startDate, QDateTime endDate)
{
    QPointSale pointSale = unpack<QPointSale>(val);
    QVector<QReceipt> receipts = db->receipt->getReceiptsForPointSaleByDateRange(pointSale.id,
                                                                                 startDate,
                                                                                 endDate);
    QVector<QVariant> output;
    for (auto receipt : receipts) {
        output.push_back(QVariant::fromValue(receipt));
    }
    return output;
}

QDateTime QMoney::getItemDateTime(QVariant &item)
{
    QReceipt receipt = unpack<QReceipt>(item);
    return receipt.dateTime;
}

void QMoney::updateResult(double *result, QVariant &item)
{
    QReceipt receipt = unpack<QReceipt>(item);
    *result += receipt.sum;
}

Statistics::QUsersMoney::QUsersMoney(QDatabaseConrol *db)
    : db(db)
{
    receiptHash.clear();
}

void QUsersMoney::hook(const StatisticsInput &info)
{
    QMutex *mut = new QMutex;
    mut->lock();
    receiptHash.clear();
    receiptHash = db->receipt->getReceiptsHash(info.startDate, info.endDate.addDays(1));
    mut->unlock();
    delete mut;
}

QVector<QVariant> QUsersMoney::getFirstVector()
{
    QVector<QUser> users = db->user->getUsers();

    QVector<QVariant> output;
    for(auto user : users) {
        output.push_back(QVariant::fromValue(user));
    }
    return output;
}

QString QUsersMoney::getKey(QVariant &val)
{
    auto user = unpack<QUser>(val);
    return user.surname + " " + user.name[0] + ". " + user.patronymic[0] + ".";
}

QVector<QVariant> QUsersMoney::getSecondVector(QVariant &val, QDateTime startDate, QDateTime endDate)
{
    QUser user = unpack<QUser>(val);
    QVector<QSoldPosition> soldPositions = db->soldPosition->getSoldPositionsForUser(user.id, startDate, endDate);

    QVector<QVariant> output;
    for (auto soldPosition : soldPositions) {
        output.push_back(QVariant::fromValue(soldPosition));
    }
    return output;
}

QDateTime QUsersMoney::getItemDateTime(QVariant &item)
{
    QSoldPosition soldPosition = unpack<QSoldPosition>(item);

    return soldPosition.date;
}

void QUsersMoney::updateResult(double *result, QVariant &item)
{
    QSoldPosition soldPosition = unpack<QSoldPosition>(item);

    QMutex *mut = new QMutex;
    auto i = receiptHash.find(soldPosition.idReceipt);
    if (!i->isEmpty()) {
        *result += receiptHash.take(soldPosition.idReceipt) .sum;
    }
    receiptHash.remove(soldPosition.idReceipt);
    delete mut;
}

QNumberSoldProduct::QNumberSoldProduct(QDatabaseConrol *db, const int idProduct)
    : db(db),
      idProduct(idProduct)
{

}

QVector<QVariant> QNumberSoldProduct::getFirstVector()
{
    QVector<QPointSale> pointSales = db->pointSale->getPointSales();

    QVector<QVariant> output;
    for(auto pointSale : pointSales) {
        output.push_back(QVariant::fromValue(pointSale));
    }
    return output;
}

QString QNumberSoldProduct::getKey(QVariant &val)
{
    return unpack<QPointSale>(val).name;
}

QVector<QVariant> QNumberSoldProduct::getSecondVector(QVariant &val, QDateTime startDate, QDateTime endDate)
{
    QPointSale pointSale = unpack<QPointSale>(val);
    QVector<QSoldPosition> soldPositions = db->soldPosition->getSoldPositionsForPointSale(pointSale.id,
                                                                                         startDate,
                                                                                         endDate);
    QVector<QVariant> output;
    for (auto soldPosition : soldPositions) {
        output.push_back(QVariant::fromValue(soldPosition));
    }
    return output;
}

bool QNumberSoldProduct::checkHook(QVariant &item)
{
    QSoldPosition soldPosition = unpack<QSoldPosition>(item);

    if(soldPosition.idProduct == idProduct) {
        return true;
    }
    return false;
}

QDateTime QNumberSoldProduct::getItemDateTime(QVariant &item)
{
    QSoldPosition soldPosition = unpack<QSoldPosition>(item);
    return soldPosition.date;
}

void QNumberSoldProduct::updateResult(double *result, QVariant &item)
{
    QSoldPosition soldPosition = unpack<QSoldPosition>(item);
    *result += soldPosition.count;
}

QNumberSoldProductsForPointSale::QNumberSoldProductsForPointSale(QDatabaseConrol *db,
                                                                 const int idPointSale)
    : db(db),
      idPointSale(idPointSale)
{

}

QVector<QVariant> QNumberSoldProductsForPointSale::getFirstVector()
{
    QVector<QProduct> products = db->product->getProducts();

    QVector<QVariant> output;
    for(auto product : products) {
        output.push_back(QVariant::fromValue(product));
    }
    return output;
}

QString QNumberSoldProductsForPointSale::getKey(QVariant &val)
{
    return unpack<QProduct>(val).name;
}

QVector<QVariant> QNumberSoldProductsForPointSale::getSecondVector(QVariant &val, QDateTime startDate, QDateTime endDate)
{
    QProduct product = unpack<QProduct>(val);
    QVector<QSoldPosition> soldPositions = db->soldPosition->getSoldPositionsForProduct(product.id, startDate, endDate);

    QVector<QVariant> output;
    for (auto soldPosition : soldPositions) {
        output.push_back(QVariant::fromValue(soldPosition));
    }
    return output;
}

bool QNumberSoldProductsForPointSale::checkHook(QVariant &item)
{
    QSoldPosition soldPosition = unpack<QSoldPosition>(item);
    if (soldPosition.idPointSale == idPointSale) {
        return true;
    }
    return false;
}

QDateTime QNumberSoldProductsForPointSale::getItemDateTime(QVariant &item)
{
    QSoldPosition soldPosition = unpack<QSoldPosition>(item);
    return soldPosition.date;
}

void QNumberSoldProductsForPointSale::updateResult(double *result, QVariant &item)
{
    QSoldPosition soldPosition = unpack<QSoldPosition>(item);
    *result += soldPosition.count;
}
