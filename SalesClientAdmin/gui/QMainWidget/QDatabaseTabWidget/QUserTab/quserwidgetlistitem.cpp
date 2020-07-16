#include "quserwidgetlistitem.h"

using namespace Gui::DatabaseTabs;

QUserWidgetListItem::QUserWidgetListItem(const QUser &user,
                                         QWidget *parent)
    : AbstractTab::QAbstractWidgetListItem(user.login,
                                           "",
                                           true,
                                           parent),
      user(user)
{

}

void QUserWidgetListItem::setUser(const QUser &user)
{
    this->user = user;
    updateItem();
}

QUser QUserWidgetListItem::getUser() const
{
    return user;
}

void QUserWidgetListItem::updateItem()
{
    AbstractTab::QAbstractWidgetListItem::setItemName(user.login);
}

void QUserWidgetListItem::mouseDoubleClickEvent(QMouseEvent *)
{
    emit (this->signalEdit(user));
}

void QUserWidgetListItem::sendRemoveSignal()
{
    emit (this->signalRemove(user.id));
}
