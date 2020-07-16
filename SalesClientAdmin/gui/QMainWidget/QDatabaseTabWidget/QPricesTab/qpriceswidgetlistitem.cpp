#include "qpriceswidgetlistitem.h"

using namespace Gui::DatabaseTabs;

QPricesWidgetListItem::QPricesWidgetListItem(const QPrice &price,
                                             const QVolumeProduct &volume,
                                             QWidget *parent)
    : AbstractTab::QAbstractWidgetListItem((tr("Цена: ") + QString::number(price.value) + "\n"
                                           + tr(" Величина: ") + volume.units + "\n"
                                           + tr(" ") + price.description),
                                           "",
                                           false,
                                           parent),
      price(price),
      volume(volume)
{

}

void QPricesWidgetListItem::setPrice(const QPrice &price)
{
    this->price = price;
    this->updateItem();
}

QPrice QPricesWidgetListItem::getPrice()
{
    return price;
}

void QPricesWidgetListItem::setVolume(const QVolumeProduct &volume)
{
    this->volume = volume;
    this->updateItem();
}

QVolumeProduct QPricesWidgetListItem::getVolume()
{
    return volume;
}

void QPricesWidgetListItem::updateItem()
{
    AbstractTab::QAbstractWidgetListItem::setItemName(price.description
                                                      + QString::number(price.value));

}

void QPricesWidgetListItem::mouseDoubleClickEvent(QMouseEvent *)
{
    emit (this->signalEdit(price));
}

void QPricesWidgetListItem::sendRemoveSignal()
{
    emit (this->signalRemove(price.id));
}
