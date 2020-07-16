#ifndef QPOINTSALETAB_H
#define QPOINTSALETAB_H

#include <QWidget>
#include <QMessageBox>
#include "../QAbstractTab/qabstracttab.h"
#include "../commonFiles/SalesSystem/QPointSale/qpointsale.h"
#include "qpointsaleeditdialog.h"
#include "qpointsalewidgetlistitem.h"

namespace Gui::DatabaseTabs {

class QPointSaleTab : public AbstractTab::QAbstractTab
{
    Q_OBJECT
public:
    explicit QPointSaleTab(QNetManager *m_networkManager, QWidget *parent = nullptr);
    ~QPointSaleTab() override = default;

    DatabaseCommands::QPointSaleCommands *getDatabasePointSaleCommands() const;

private:
    AbstractTab::QAbstractWidgetListItem * createOwnItem(const QSalesObjects &object) override;
    void removeFromLocalDatabase(int id, const QString &name) override;
    QString getCurrentItemName() override;

    void updateItemOnDisplay(const QPointSale &pointSale);
    void addProcess(QPointSale &pointSale);
    void editProcess(QPointSale &pointSale);

private slots:
    void slotAddItem() override;
    void slotUpdateItems() override;
    void slotRemoveItem(int id) override;
    void slotEditItem(QSalesObjects &) override;
};

}

#endif // QPOINTSALETAB_H
