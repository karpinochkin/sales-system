#ifndef QTYPEWIDGETLISTITEM_H
#define QTYPEWIDGETLISTITEM_H

#include "../../QAbstractTab/QAbstractWidgetListItem.h"
#include "../commonFiles/SalesSystem/QPaymentType/qpaymenttype.h"

namespace Gui::DatabaseTabs {

class QTypeWidgetListItem : public AbstractTab::QAbstractWidgetListItem
{
    Q_OBJECT

public:
    QTypeWidgetListItem(const QPaymentType &type, QWidget *parent = nullptr);
    ~QTypeWidgetListItem() override = default;

    void setType(const QPaymentType &type);
    QPaymentType getType() const;
    void updateItem();

private:
    QPaymentType type;
    void mouseDoubleClickEvent(QMouseEvent *) override;

private slots:
    void sendRemoveSignal() override;
};

}

#endif
