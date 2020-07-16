#ifndef QCOUNTFORPOINTSALEGRAPHICSPRINTER_H
#define QCOUNTFORPOINTSALEGRAPHICSPRINTER_H

#include "graphicsprintertemplate.h"
#include "../commonClientFiles/QNetManager/qnetmanager.h"

namespace GraphicsPrinter {

class QCountForPointSaleGraphicsPrinter : public GraphicsPrinterTemplate
{
public:
    ~QCountForPointSaleGraphicsPrinter() override = default;
    QCountForPointSaleGraphicsPrinter(int idPointSale,
                                      QNetManager *manager,
                                      QWidget *parent = nullptr);

private:
    int idPointSale = -1;
    QNetManager *netManager = nullptr;

    QVector<QVariant> getFirstVector() override;
    QBarSet * getBarSet(QVariant &val) override;
    void querySecondVectorFromServer(QDate startDate, QDate endDate) override;
    QVector<QVariant> getSecondVector(QVariant &, QDate startDate, QDate endDate) override;
    void processing(double *result, QVariant &val, QDate date) override;
};

}

#endif // QCOUNTFORPOINTSALEGRAPHICSPRINTER_H
