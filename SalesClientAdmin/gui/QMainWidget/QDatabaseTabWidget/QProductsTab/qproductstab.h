#ifndef QPRODUCTSTAB_H
#define QPRODUCTSTAB_H

#include "../QAbstractTab/qabstracttab.h"
#include "../commonFiles/SalesSystem/QProduct/qproduct.h"
#include "qproductswidgetlistitem.h"
#include "qproductseditdialog.h"
#include "../QPricesTab/qpricestab.h"

namespace Gui::DatabaseTabs {

class QProductsTab : public AbstractTab::QAbstractTab
{
    Q_OBJECT
public:
    explicit QProductsTab(QNetManager *m_networkManager,
                          QWidget *parent = nullptr);
    ~QProductsTab() override = default;

    DatabaseCommands::QProductCommands *getDatabaseProductCommands() const;
    DatabaseCommands::QProductPictureCommands *getDatabasePictureCommands() const;

private:
    AbstractTab::QAbstractWidgetListItem * createOwnItem(const QSalesObjects &object) override;
    void removeFromLocalDatabase(int id, const QString &name) override;
    QString getCurrentItemName() override;
    void updateItemOnDisplay(const QProduct &product);
    void addProcess(QProduct &product);
    void editProcess(QProduct &product);
    void shawPriceWidget(const QProduct &product);

private slots:
    void slotAddItem() override;
    void slotUpdateItems() override;
    void slotRemoveItem(int id) override;
    void slotEditItem(QSalesObjects &object) override;
};

}

#endif // QPRODUCTSTAB_H
