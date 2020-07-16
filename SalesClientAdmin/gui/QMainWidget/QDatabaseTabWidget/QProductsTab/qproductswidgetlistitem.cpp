#include "qproductswidgetlistitem.h"

using namespace Gui::DatabaseTabs;

QProductsWidgetListItem::QProductsWidgetListItem(const QProduct &product, const QByteArray &pictureData,
                                                 QWidget *parent)
    : AbstractTab::QAbstractWidgetListItem(product.name,
                                           pictureData,
                                           false,
                                           parent),
      product(product),
      pictureData(pictureData)
{

}

void QProductsWidgetListItem::setInformation(const QProduct &product, const QByteArray &data)
{
    this->setProduct(product);
    this->setPicture(data);
}

void QProductsWidgetListItem::setProduct(const QProduct &product)
{
    this->product = product;
    updateItem();
}

QProduct QProductsWidgetListItem::getProduct() const
{
    return product;
}

void QProductsWidgetListItem::setPicture(const QByteArray &data)
{
    this->pictureData = data;
    updateItem();
}

QByteArray QProductsWidgetListItem::getPicture()
{
    return pictureData;
}

void QProductsWidgetListItem::updateItem()
{
    AbstractTab::QAbstractWidgetListItem::setItemName(product.name);
    AbstractTab::QAbstractWidgetListItem::setItemPicture(pictureData);
}

void QProductsWidgetListItem::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setBrush(QBrush(QColor(product.color.red(),
                                   product.color.green(),
                                   product.color.blue())));
    QRectF rectangle(5, 70, width() - 5, height() - 70);
    painter.drawRoundedRect(rectangle, 100, 100);
}

void QProductsWidgetListItem::mouseDoubleClickEvent(QMouseEvent *)
{
    emit (this->signalEdit(product));
}

void QProductsWidgetListItem::sendRemoveSignal()
{
    emit (this->signalRemove(product.id));
}
