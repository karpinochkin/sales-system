#include "qcountforusergraphicsprinter.h"

using namespace GraphicsPrinter;

QCountForUserGraphicsPrinter::QCountForUserGraphicsPrinter(int idUser,
                                                           QNetManager *manager,
                                                           QWidget *parent) :
    GraphicsPrinterTemplate(parent),
    idUser(idUser),
    netManager(manager)
{
    connect(netManager, &QNetManager::signalSoldPositionsLoaded,
            this, &QCountForUserGraphicsPrinter::dataReceived);
}

QVector<QVariant> QCountForUserGraphicsPrinter::getFirstVector()
{
    QVector<QProduct> products = netManager->DatabaseCommands()
            ->product->getProducts();

    QVector<QVariant> output;
    for(auto product : products) {
        output.push_back(QVariant::fromValue(product));
    }
    return output;
}

QBarSet *QCountForUserGraphicsPrinter::getBarSet(QVariant &val)
{
    return new QBarSet(unpack<QProduct>(val).name, this);
}

void QCountForUserGraphicsPrinter::querySecondVectorFromServer(QDate startDate, QDate endDate)
{
    this->querySecondVectorFromServer(startDate, endDate.addDays(1));
}

QVector<QVariant> QCountForUserGraphicsPrinter::getSecondVector(QVariant &val, QDate startDate, QDate endDate)
{
    QProduct product = unpack<QProduct>(val);
    QVector<QSoldPosition> soldPositions = netManager->DatabaseCommands()
            ->soldPosition->getSoldPositionsForProduct(product.id, startDate, endDate);

    QVector<QVariant> output;
    for (auto soldPosition : soldPositions) {
        output.push_back(QVariant::fromValue(soldPosition));
    }
    return output;
}

void QCountForUserGraphicsPrinter::processing(double *result,
                                              QVariant &val,
                                              QDate date)
{
    QSoldPosition soldPosition = unpack<QSoldPosition>(val);

    if (soldPosition.idUser == idUser) {
        if (soldPosition.date.date() == date) {
            *result += soldPosition.count;
        }
    }
}
