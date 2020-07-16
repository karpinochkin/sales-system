#ifndef QTYPETAB_H
#define QTYPETAB_H

#include <QWidget>
#include <QMessageBox>
#include "../QAbstractTab/qabstracttab.h"
#include "../commonFiles/SalesSystem/QPaymentType/qpaymenttype.h"
#include "QTypeWidgetListItem/qtypewidgetlistitem.h"
#include "QTypeEditDialog/qtypeeditdialog.h"

namespace Gui::DatabaseTabs {

class QTypeTab : public AbstractTab::QAbstractTab
{
    Q_OBJECT
public:
    explicit QTypeTab(QNetManager *m_networkManager, QWidget *parent = nullptr);
    ~QTypeTab() override = default;

    DatabaseCommands::QPaymentTypeCommands *getDatabaseTypeCommands() const;

private:
    AbstractTab::QAbstractWidgetListItem * createOwnItem(const QSalesObjects &object) override;
    void removeFromLocalDatabase(int id, const QString &name) override;
    QString getCurrentItemName() override;
    void updateItemOnDisplay(const QPaymentType &type);
    void addProcess(QPaymentType &type);
    void editProcess(QPaymentType &type);

private slots:
    void slotAddItem() override;
    void slotUpdateItems() override;
    void slotRemoveItem(int id) override;
    void slotEditItem(QSalesObjects &) override;
};

}

#endif // QTYPETAB_H
