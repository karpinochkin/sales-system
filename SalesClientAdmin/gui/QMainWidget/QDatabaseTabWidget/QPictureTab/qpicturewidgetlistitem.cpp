#include "qpicturewidgetlistitem.h"

using namespace Gui::DatabaseTabs;

QPictureWidgetListItem::QPictureWidgetListItem(const QProductPicture &picture,
                                               QWidget *parent)
    : AbstractTab::QAbstractWidgetListItem(picture.name,
                                           picture.data,
                                           false,
                                           parent),
      picture(picture)
{

}

void QPictureWidgetListItem::setPictureInformation(const QProductPicture &value)
{
    picture = value;
    updateItem();
}

void QPictureWidgetListItem::updateItem()
{
    AbstractTab::QAbstractWidgetListItem::setItemName(picture.name);
    AbstractTab::QAbstractWidgetListItem::setItemPicture(picture.data);
}

QProductPicture QPictureWidgetListItem::getPictureInformation() const
{
    return picture;
}

void QPictureWidgetListItem::mouseDoubleClickEvent(QMouseEvent *)
{
    emit (this->signalEdit(picture));
}

void QPictureWidgetListItem::sendRemoveSignal()
{
    emit (this->signalRemove(picture.id));
}


