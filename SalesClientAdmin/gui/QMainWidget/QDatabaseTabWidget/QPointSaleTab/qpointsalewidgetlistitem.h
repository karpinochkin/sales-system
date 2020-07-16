#ifndef QPOINTSALEWIDGETLISTITEM_H
#define QPOINTSALEWIDGETLISTITEM_H

#include "../QAbstractTab/QAbstractWidgetListItem.h"
#include "../commonFiles/SalesSystem/QPointSale/qpointsale.h"

namespace Gui::DatabaseTabs {

class QPointSaleWidgetListItem : public AbstractTab::QAbstractWidgetListItem
{
    Q_OBJECT
public:
    explicit QPointSaleWidgetListItem(const QPointSale &pointSale,
                                      QWidget *parent = nullptr);
    ~QPointSaleWidgetListItem() override = default;

    void updateItem();
    void setPointSale(const QPointSale &pointSale);
    QPointSale getPointSale() const;

private:
    QPointSale pointSale;
    void mouseDoubleClickEvent(QMouseEvent *) override;

private slots:
    void sendRemoveSignal() override;
};

}
#endif // QPOINTSALEWIDGETLISTITEM_H
