#ifndef QMONEYFORUSERSGRAPHICSPRINTER_H
#define QMONEYFORUSERSGRAPHICSPRINTER_H

#include "graphicsprintertemplate.h"
#include "../commonClientFiles/QNetManager/qnetmanager.h"

namespace GraphicsPrinter {

class QMoneyForUsersGraphicsPrinter : public GraphicsPrinterTemplate
{
    Q_OBJECT
public:
    QMoneyForUsersGraphicsPrinter(QNetManager *manager,
                                  QWidget *parent = nullptr);
    ~QMoneyForUsersGraphicsPrinter() override = default;

private:
    QNetManager *netManager = nullptr;
    QHash <int, QReceipt> receiptsHash;
    int loadFlag = 0;

    QVector<QVariant> getFirstVector() override;
    QBarSet * getBarSet(QVariant &val) override;
    void querySecondVectorFromServer(QDate startDate, QDate endDate) override;
    QVector<QVariant> getSecondVector(QVariant &, QDate startDate, QDate endDate) override;
    void processing(double *result, QVariant &val, QDate date) override;
    void received();

private slots:
    void receiptsLoaded();
    void soldPositionsLoaded();
};

}

#endif // QMONEYFORUSERSGRAPHICSPRINTER_H
