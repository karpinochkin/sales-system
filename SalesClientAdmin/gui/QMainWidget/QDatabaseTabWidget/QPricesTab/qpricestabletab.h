#ifndef QPRICESTABLETAB_H
#define QPRICESTABLETAB_H

#include <QWidget>
#include "../commonClientFiles/QNetManager/qnetmanager.h"
#include "../QAbstractTab/qabstracttabletab.h"
#include "../commonFiles/SalesSystem/QPrice/qprice.h"
#include "../commonFiles/SalesSystem/QVolumeProduct/qvolumeproduct.h"
#include "qpriceseditdialog.h"
#include "qpriceseditforproductdialog.h"

namespace Gui::DatabaseTabs {

class QPricesTableTab : public AbstractTableTab::QAbstractTableTab
{
    Q_OBJECT
public:
    explicit QPricesTableTab(QNetManager *networkManager,
                        const PricesTab::Product &product,
                        QWidget *parent = nullptr);
    explicit QPricesTableTab(QNetManager *networkManager,
                             QWidget *parent = nullptr);
    ~QPricesTableTab() override = default;

private:
    QNetManager *m_netManager = nullptr;
    const PricesTab::Product product;

    void connects();
    void editProcess(QPrice &value);
    void addProcess(QPrice &value);
    void selectedPricesUpdate();
    void allPricesUpdate();
    QVector<QVariant> getSalesObjectVector() override;
    void processingAddItemsToTable(int row, const QVariant &value) override;

protected:
    void closeEvent(QCloseEvent *) override;

private slots:
    void slotEditItem(int ID);
    void slotAddItem();
signals:
    void signalClose();
};

}

#endif // QPRICESTABLETAB_H
