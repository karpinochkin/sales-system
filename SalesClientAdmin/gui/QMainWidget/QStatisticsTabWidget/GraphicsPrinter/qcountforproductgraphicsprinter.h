#ifndef QCOUNTFORPRODUCTGRAPHICSPRINTER_H
#define QCOUNTFORPRODUCTGRAPHICSPRINTER_H

#include "graphicsprintertemplate.h"
#include "../commonClientFiles/QNetManager/qnetmanager.h"

namespace GraphicsPrinter {

class QCountForProductGraphicsPrinter : public GraphicsPrinterTemplate
{
public:
    ~QCountForProductGraphicsPrinter() override = default;
    QCountForProductGraphicsPrinter(int idProduct,
                                    QNetManager *manager,
                                    QWidget *parent = nullptr);

private:
    int idProduct = -1;
    QNetManager *netManager = nullptr;

    QVector<QVariant> getFirstVector() override;
    QBarSet * getBarSet(QVariant &val) override;
    void querySecondVectorFromServer(QDate startDate, QDate endDate) override;
    QVector<QVariant> getSecondVector(QVariant &val,
                                      QDate startDate,
                                      QDate endDate) override;
    void processing(double *result, QVariant &val, QDate date) override;
};

}

#endif // QCOUNTFORPRODUCTGRAPHICSPRINTER_H
