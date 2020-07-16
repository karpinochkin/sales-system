#ifndef QPRICESWIDGETLISTITEM_H
#define QPRICESWIDGETLISTITEM_H

#include "../QAbstractTab/QAbstractWidgetListItem.h"
#include "../commonFiles/SalesSystem/QPrice/qprice.h"
#include "../commonFiles/SalesSystem/QVolumeProduct/qvolumeproduct.h"

namespace Gui::DatabaseTabs {

class QPricesWidgetListItem : public AbstractTab::QAbstractWidgetListItem
{
    Q_OBJECT
public:
    explicit QPricesWidgetListItem(const QPrice &price,
                                   const QVolumeProduct &volume,
                                   QWidget *parent = nullptr);
    ~QPricesWidgetListItem() override = default;

    void setPrice(const QPrice &price);
    QPrice getPrice();

    void setVolume(const QVolumeProduct &volume);
    QVolumeProduct getVolume();
    void updateItem();

private:
    QPrice price;
    QVolumeProduct volume;
    void mouseDoubleClickEvent(QMouseEvent *) override;

private slots:
    void sendRemoveSignal() override;
};

}

#endif // QPRICESWIDGETLISTITEM_H
