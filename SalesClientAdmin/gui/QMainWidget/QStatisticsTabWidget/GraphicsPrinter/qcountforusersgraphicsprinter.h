#ifndef QCOUNTFORUSERSGRAPHICSPRINTER_H
#define QCOUNTFORUSERSGRAPHICSPRINTER_H

#include "graphicsprintertemplate.h"
#include "../commonClientFiles/QNetManager/qnetmanager.h"

namespace GraphicsPrinter {

class QCountForUsersGraphicsPrinter : public GraphicsPrinterTemplate
{
public:
    QCountForUsersGraphicsPrinter(QNetManager *manager,
                                 QWidget *parent = nullptr);
    ~QCountForUsersGraphicsPrinter() override = default;

private:
    QNetManager *netManager = nullptr;

    QVector<QVariant> getFirstVector() override;
    QBarSet * getBarSet(QVariant &val) override;
    void querySecondVectorFromServer(QDate startDate, QDate endDate) override;
    QVector<QVariant> getSecondVector(QVariant &val, QDate startDate, QDate endDate) override;
    void processing(double *result, QVariant &val, QDate date) override;
};

}

#endif // QCOUNTFORUSERSGRAPHICSPRINTER_H
