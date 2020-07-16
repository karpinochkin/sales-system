#ifndef QUSERWIDGETLISTITEM_H
#define QUSERWIDGETLISTITEM_H

#include "../QAbstractTab/QAbstractWidgetListItem.h"
#include "../commonFiles/SalesSystem/QUser/quser.h"

namespace Gui::DatabaseTabs {

class QUserWidgetListItem : public AbstractTab::QAbstractWidgetListItem
{
    Q_OBJECT
public:
    explicit QUserWidgetListItem(const QUser &user,
                                 QWidget *parent = nullptr);
    ~QUserWidgetListItem() override = default;

    void setUser(const QUser &user);
    QUser getUser() const;
    void updateItem();

private:
    QUser user;
    void mouseDoubleClickEvent(QMouseEvent *) override;

private slots:
    void sendRemoveSignal() override;
};

}

#endif // QUSERWIDGETLISTITEM_H
