#ifndef QPRICESTAB_H
#define QPRICESTAB_H

#include <QMessageBox>
#include "../QAbstractTab/qabstracttab.h"
#include "../commonFiles/SalesSystem/QPrice/qprice.h"
#include "qpriceseditdialog.h"
#include "qpriceseditforproductdialog.h"
#include "qpriceswidgetlistitem.h"

namespace Gui::DatabaseTabs {

class QPricesTab : public AbstractTab::QAbstractTab
{
    Q_OBJECT
public:
    explicit QPricesTab(QNetManager *m_networkManager,
                        const PricesTab::Product &product,
                        QWidget *parent = nullptr);
    explicit QPricesTab(QNetManager *m_networkManager,
                        QWidget *parent = nullptr);
    ~QPricesTab() override = default;

    DatabaseCommands::QPriceCommands *getDatabasePriceCommands() const;

private:
    const PricesTab::Product product;
    AbstractTab::QAbstractWidgetListItem * createOwnItem(const QSalesObjects &object) override;
    void removeFromLocalDatabase(int id, const QString &name) override;
    QString getCurrentItemName() override;
    void setGui();
    void selectedPricesUpdate();
    void allPricesUpdate();
    void updateItemOnDisplay(const QPrice &price);
    void addProcess(QPrice &price);
    void editProcess(QPrice &price);
protected:
    void closeEvent(QCloseEvent *) override;

private slots:
    void slotAddItem() override;
    void slotUpdateItems() override;
    void slotRemoveItem(int id) override;
    void slotEditItem(QSalesObjects &) override;

signals:
    void signalClose();
};

}
#endif // QPRICESTAB_H
