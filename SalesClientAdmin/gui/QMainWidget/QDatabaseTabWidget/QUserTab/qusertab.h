#ifndef QUSERTAB_H
#define QUSERTAB_H

#include "../QAbstractTab/qabstracttab.h"
#include "../commonFiles/SalesSystem/QUser/quser.h"
#include "quserwidgetlistitem.h"
#include "qusereditdialog.h"

namespace Gui::DatabaseTabs {

class QUserTab : public AbstractTab::QAbstractTab
{
    Q_OBJECT
public:
    explicit QUserTab(QNetManager *m_networkManager,
                      QWidget *parent = nullptr);
    ~QUserTab() override = default;

    DatabaseCommands::QUserCommands *getDatabaseUserCommands() const;

private:
    AbstractTab::QAbstractWidgetListItem * createOwnItem(const QSalesObjects &object) override;
    void removeFromLocalDatabase(int id, const QString &name) override;
    QString getCurrentItemName() override;
    void updateItemOnDisplay(const QUser &user);
    void addProcess(QUser &user);
    void editProcess(QUser &user);
    bool isCurrentUser(const QUser &user);

private slots:
    void slotAddItem() override;
    void slotUpdateItems() override;
    void slotRemoveItem(int id) override;
    void slotEditItem(QSalesObjects &) override;
};

}

#endif // QUSERTAB_H
