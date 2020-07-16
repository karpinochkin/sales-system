#ifndef QCATEGORYWIDGETLISTITEM_H
#define QCATEGORYWIDGETLISTITEM_H

#include "../QAbstractTab/QAbstractWidgetListItem.h"
#include "../commonFiles/SalesSystem/QSalesСategory/qsalescategory.h"

namespace Gui::DatabaseTabs {

class QCategoryWidgetListItem : public AbstractTab::QAbstractWidgetListItem
{
    Q_OBJECT
public:
    QCategoryWidgetListItem(const QSalesCategory &category, QWidget *parent = nullptr);
    ~QCategoryWidgetListItem() override = default;

    void setCategory(const QSalesCategory &category);
    QSalesCategory getCategory() const;
    void updateItem();

private:
    QSalesCategory category;
    void paintEvent(QPaintEvent *) override;
    void mouseDoubleClickEvent(QMouseEvent *) override;

private slots:
    void sendRemoveSignal() override;
};

}

#endif // QCATEGORYWIDGETLISTITEM_H
