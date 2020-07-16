#ifndef QCATEGORYTAB_H
#define QCATEGORYTAB_H

#include <QMessageBox>
#include "../QAbstractTab/qabstracttab.h"
#include "../commonFiles/SalesSystem/QSalesСategory/qsalescategory.h"
#include "qcategoryeditdialog.h"
#include "qcategorywidgetlistitem.h"

namespace Gui::DatabaseTabs {

class QCategoryTab : public AbstractTab::QAbstractTab
{
    Q_OBJECT
public:
    explicit QCategoryTab(QNetManager *m_networkManager, QWidget *parent = nullptr);
    ~QCategoryTab() override = default;

    DatabaseCommands::QSalesCategoryCommands *getDatabaseCategoryCommands() const;

private:
    AbstractTab::QAbstractWidgetListItem * createOwnItem(const QSalesObjects &object) override;
    void removeFromLocalDatabase(int id, const QString &name) override;
    QString getCurrentItemName() override;
    void updateItemOnDisplay(const QSalesCategory &category);
    void addProcess(QSalesCategory &category);
    void editProcess(QSalesCategory &category);
protected:


private slots:
    void slotAddItem() override;
    void slotUpdateItems() override;
    void slotRemoveItem(int id) override;
    void slotEditItem(QSalesObjects &) override;
};

}

#endif // QCATEGORYTAB_H
