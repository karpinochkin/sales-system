#include "qvolumewidgetlistitem.h"

using namespace Gui::DatabaseTabs;

QVolumeWidgetListItem::QVolumeWidgetListItem(const QVolumeProduct &volume,
                                             QWidget *parent)
    : AbstractTab::QAbstractWidgetListItem(volume.description,
                                           "",
                                           true,
                                           parent),
      volume(volume)
{

}

void QVolumeWidgetListItem::setVolume(const QVolumeProduct &volume)
{
    this->volume = volume;
    updateItem();
}

QVolumeProduct QVolumeWidgetListItem::getVolume() const
{
    return volume;
}

void QVolumeWidgetListItem::updateItem()
{
    AbstractTab::QAbstractWidgetListItem::setItemName(volume.description);
}

void QVolumeWidgetListItem::mouseDoubleClickEvent(QMouseEvent *)
{
    emit (this->signalEdit(volume));
}

void QVolumeWidgetListItem::sendRemoveSignal()
{
    emit (this->signalRemove(volume.id));
}
