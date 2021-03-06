#ifndef QMONEYGRAPHICSPRINTER_H
#define QMONEYGRAPHICSPRINTER_H

#include "graphicsprintertemplate.h"
#include "../commonFiles/SalesSystem/QPointSale/qpointsale.h"
#include "../commonClientFiles/QNetManager/qnetmanager.h"

namespace GraphicsPrinter {

class QMoneyGraphicsPrinter : public GraphicsPrinterTemplate
{
public:
    ~QMoneyGraphicsPrinter() override = default;
    QMoneyGraphicsPrinter(QNetManager *manager,
                          QWidget *parent = nullptr);

private:
    QNetManager *netManager = nullptr;

    QVector<QVariant> getFirstVector() override;
    QBarSet * getBarSet(QVariant &val) override;
    void querySecondVectorFromServer(QDate startDate, QDate endDate) override;
    QVector<QVariant> getSecondVector(QVariant &val, QDate startDate, QDate endDate) override;
    void processing(double *result,
                    QVariant &val,
                    QDate date) override;
};

}
#endif // QMONEYGRAPHICSPRINTER_H
