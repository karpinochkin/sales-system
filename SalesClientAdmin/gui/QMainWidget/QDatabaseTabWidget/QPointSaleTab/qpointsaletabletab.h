#ifndef QPOINTSALETABLETAB_H
#define QPOINTSALETABLETAB_H

#include <QWidget>
#include "../commonClientFiles/QNetManager/qnetmanager.h"
#include "../QAbstractTab/qabstracttabletab.h"
#include "qpointsaleeditdialog.h"

namespace Gui::DatabaseTabs {

class QPointSaleTableTab : public AbstractTableTab::QAbstractTableTab
{
    Q_OBJECT
public:
    explicit QPointSaleTableTab(QNetManager *networkManager,
                                QWidget *parent = nullptr);
    ~QPointSaleTableTab() override = default;

private:
    QNetManager *m_netManager = nullptr;

    void editProcess(QPointSale &value);
    void addProcess(QPointSale &value);
    QVector<QVariant> getSalesObjectVector() override;
    void processingAddItemsToTable(int row, const QVariant &) override;

private slots:
    void slotEditItem(int ID);
    void slotAddItem();
};

}

#endif // QPOINTSALETABLETAB_H
