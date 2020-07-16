#include "qcountforpointsalegraphicsprinter.h"

using namespace GraphicsPrinter;

QCountForPointSaleGraphicsPrinter::QCountForPointSaleGraphicsPrinter(int idPointSale,
                                                                     QNetManager *manager,
                                                                     QWidget *parent)
    : GraphicsPrinterTemplate(parent),
      idPointSale(idPointSale),
      netManager(manager)
{

    connect(netManager, &QNetManager::signalSoldPositionsLoaded,
            this, &QCountForPointSaleGraphicsPrinter::dataReceived);
}

QVector<QVariant> QCountForPointSaleGraphicsPrinter::getFirstVector()
{
    QVector<QProduct> products = netManager->DatabaseCommands()
            ->product->getProducts();

    QVector<QVariant> output;
    for(auto product : products) {
        output.push_back(QVariant::fromValue(product));
    }
    return output;
}

QBarSet *QCountForPointSaleGraphicsPrinter::getBarSet(QVariant &val)
{
    QBarSet *set = new QBarSet(unpack<QProduct>(val).name, this);
    return set;
}

void QCountForPointSaleGraphicsPrinter::querySecondVectorFromServer(QDate startDate, QDate endDate)
{
    netManager->CommandsToServer()->soldPosition->load(startDate, endDate.addDays(1));
}

QVector<QVariant> QCountForPointSaleGraphicsPrinter::getSecondVector(QVariant &val, QDate startDate, QDate endDate)
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

void QCountForPointSaleGraphicsPrinter::processing(double *result, QVariant &val, QDate date)
{
    QSoldPosition soldPosition = unpack<QSoldPosition>(val);
    if (soldPosition.idPointSale == idPointSale) {
        if (soldPosition.date.date() == date) {
            *result += soldPosition.count;
        }
    }
}
