#include "qmoneygraphicsprinter.h"

using namespace GraphicsPrinter;

QMoneyGraphicsPrinter::QMoneyGraphicsPrinter(QNetManager *manager, QWidget *parent)
    : GraphicsPrinterTemplate(parent),
      netManager(manager)
{
    connect(netManager, &QNetManager::signalReceiptsLoaded,
            this, &QMoneyGraphicsPrinter::dataReceived);
}

QVector<QVariant> QMoneyGraphicsPrinter::getFirstVector()
{
    QVector<QPointSale> pointSales = netManager->DatabaseCommands()
            ->pointSale->getPointSales();

    QVector<QVariant> output;
    for(auto pointSale : pointSales) {
        output.push_back(QVariant::fromValue(pointSale));
    }
    return output;
}

QBarSet *QMoneyGraphicsPrinter::getBarSet(QVariant &val)
{
    QBarSet *set = new QBarSet(unpack<QPointSale>(val).name, this);
    return set;
}

void QMoneyGraphicsPrinter::querySecondVectorFromServer(QDate startDate, QDate endDate)
{
    netManager->CommandsToServer()->receipt->load(startDate, endDate.addDays(1));
}

QVector<QVariant> QMoneyGraphicsPrinter::getSecondVector(QVariant &val, QDate startDate, QDate endDate)
{
    QPointSale pointSale = unpack<QPointSale>(val);
    QVector<QReceipt> receiptes = netManager->DatabaseCommands()
            ->receipt->getReceiptsForPointSaleByDateRange(pointSale.id,
                                                          startDate,
                                                          endDate);

    QVector<QVariant> output;
    for (auto receipt : receiptes) {
        output.push_back(QVariant::fromValue(receipt));
    }
    return output;
}

void QMoneyGraphicsPrinter::processing(double *result, QVariant &val, QDate date)
{
    QReceipt receipt = unpack<QReceipt>(val);

    if (receipt.dateTime.date() == date) {
        *result += receipt.sum;
    }
}
