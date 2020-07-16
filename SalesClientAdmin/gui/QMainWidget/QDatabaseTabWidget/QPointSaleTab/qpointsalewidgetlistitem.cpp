#include "qpointsalewidgetlistitem.h"

using namespace Gui::DatabaseTabs;

QPointSaleWidgetListItem::QPointSaleWidgetListItem(const QPointSale &pointSale,
                                                   QWidget *parent)
    : AbstractTab::QAbstractWidgetListItem(pointSale.name,
                                           "",
                                           true,
                                           parent),
      pointSale(pointSale)
{

}

void QPointSaleWidgetListItem::updateItem()
{
    AbstractTab::QAbstractWidgetListItem::setItemName(pointSale.name);
}

void QPointSaleWidgetListItem::setPointSale(const QPointSale &pointSale)
{
    this->pointSale = pointSale;
    updateItem();
}

QPointSale QPointSaleWidgetListItem::getPointSale() const
{
    return pointSale;
}

void QPointSaleWidgetListItem::mouseDoubleClickEvent(QMouseEvent *)
{
    emit (this->signalEdit(pointSale));
}

void QPointSaleWidgetListItem::sendRemoveSignal()
{
    emit (this->signalRemove(pointSale.id));
}
