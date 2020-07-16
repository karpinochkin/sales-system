#ifndef QCOUNTFORUSERGRAPHICSPRINTER_H
#define QCOUNTFORUSERGRAPHICSPRINTER_H

#include "graphicsprintertemplate.h"
#include "../commonClientFiles/QNetManager/qnetmanager.h"

namespace GraphicsPrinter {

class QCountForUserGraphicsPrinter : public GraphicsPrinterTemplate
{
public:
    QCountForUserGraphicsPrinter(int idUser,
                                 QNetManager *manager,
                                 QWidget *parent = nullptr);
    ~QCountForUserGraphicsPrinter() override = default;

private:
    int idUser = -1;
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
#endif // QCOUNTFORUSERGRAPHICSPRINTER_H
