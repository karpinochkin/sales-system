#include "qcategorywidgetlistitem.h"

using namespace Gui::DatabaseTabs;

QCategoryWidgetListItem::QCategoryWidgetListItem(const QSalesCategory &category,
                                                 QWidget *parent)
    : AbstractTab::QAbstractWidgetListItem(category.name,
                                           "",
                                           false,
                                           parent),
      category(category)
{

}

void QCategoryWidgetListItem::setCategory(const QSalesCategory &category)
{
    this->category = category;
    this->updateItem();
}

QSalesCategory QCategoryWidgetListItem::getCategory() const
{
    return category;
}

void QCategoryWidgetListItem::updateItem()
{
    AbstractTab::QAbstractWidgetListItem::setItemName(category.name);
}

void QCategoryWidgetListItem::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setBrush(QBrush(QColor(category.color.red(),
                                   category.color.green(),
                                   category.color.blue())));
    QRectF rectangle(5, 70, width() - 5, height() - 70);
    painter.drawRoundedRect(rectangle, 100, 100);
}

void QCategoryWidgetListItem::mouseDoubleClickEvent(QMouseEvent *)
{
    emit (this->signalEdit(category));
}

void QCategoryWidgetListItem::sendRemoveSignal()
{
    emit (this->signalRemove(category.id));
}
