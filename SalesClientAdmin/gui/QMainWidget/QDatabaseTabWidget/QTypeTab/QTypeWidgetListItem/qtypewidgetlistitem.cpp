#include "qtypewidgetlistitem.h"

using namespace Gui::DatabaseTabs;

QTypeWidgetListItem::QTypeWidgetListItem(const QPaymentType &type, QWidget *parent)
    : AbstractTab::QAbstractWidgetListItem(type.name,
                                           "",
                                           true,
                                           parent),
      type(type)
{

}

void QTypeWidgetListItem::setType(const QPaymentType &type)
{
    this->type = type;
    updateItem();
}

QPaymentType QTypeWidgetListItem::getType() const
{
    return type;
}

void QTypeWidgetListItem::updateItem()
{
    AbstractTab::QAbstractWidgetListItem::setItemName(type.name);
}

void QTypeWidgetListItem::mouseDoubleClickEvent(QMouseEvent *)
{
    emit (this->signalEdit(type));
}

void QTypeWidgetListItem::sendRemoveSignal()
{
    emit (this->signalRemove(type.id));
}
