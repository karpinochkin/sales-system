#include "qcountforproductgraphicsprinter.h"

using namespace GraphicsPrinter;

QCountForProductGraphicsPrinter::QCountForProductGraphicsPrinter(int idProduct,
                                                                 QNetManager *manager,
                                                                 QWidget *parent)
    : GraphicsPrinterTemplate(parent),
      idProduct(idProduct),
      netManager(manager)
{
    connect(netManager, &QNetManager::signalSoldPositionsLoaded,
            this, &QCountForProductGraphicsPrinter::dataReceived);
}

QVector<QVariant> QCountForProductGraphicsPrinter::getFirstVector()
{
    QVector<QPointSale> pointSales = netManager->DatabaseCommands()
            ->pointSale->getPointSales();

    QVector<QVariant> output;
    for(auto pointSale : pointSales) {
        output.push_back(QVariant::fromValue(pointSale));
    }
    return output;

}

QBarSet *QCountForProductGraphicsPrinter::getBarSet(QVariant &val)
{
    return new QBarSet(unpack<QPointSale>(val).name, this);
}

void QCountForProductGraphicsPrinter::querySecondVectorFromServer(QDate startDate, QDate endDate)
{
    netManager->CommandsToServer()->soldPosition->load(startDate, endDate.addDays(1));
}

QVector<QVariant> QCountForProductGraphicsPrinter::getSecondVector(QVariant &val,
                                                                   QDate startDate,
                                                                   QDate endDate)
{
    QPointSale pointSale = unpack<QPointSale>(val);
    QVector<QSoldPosition> soldPositions = netManager->DatabaseCommands()
            ->soldPosition->getSoldPositionsForPointSale(pointSale.id,
                                                         startDate,
                                                         endDate);

    QVector<QVariant> output;
    for (auto soldPosition : soldPositions) {
        output.push_back(QVariant::fromValue(soldPosition));
    }
    return output;
}

void QCountForProductGraphicsPrinter::processing(double *result,
                                                 QVariant &val,
                                                 QDate date)
{
    QSoldPosition soldPosition = unpack<QSoldPosition>(val);

    if (soldPosition.idProduct == idProduct) {
        if (soldPosition.date.date() == date) {
            *result += soldPosition.count;
        }
    }
}


