#ifndef QPRODUCTSWIDGETLISTITEM_H
#define QPRODUCTSWIDGETLISTITEM_H

#include "../QAbstractTab/QAbstractWidgetListItem.h"
#include "../commonFiles/SalesSystem/QProduct/qproduct.h"

namespace Gui::DatabaseTabs {

class QProductsWidgetListItem : public AbstractTab::QAbstractWidgetListItem
{
    Q_OBJECT
public:
    QProductsWidgetListItem(const QProduct &product,
                            const QByteArray &pictureData,
                            QWidget *parent = nullptr);
    ~QProductsWidgetListItem() override = default;

    void setInformation(const QProduct &product,
                        const QByteArray &data);
    void setProduct(const QProduct &product);
    QProduct getProduct() const;
    void setPicture(const QByteArray &data);
    QByteArray getPicture();
    void updateItem();

private:
    QProduct product;
    QByteArray pictureData;
    void paintEvent(QPaintEvent *) override;
    void mouseDoubleClickEvent(QMouseEvent *) override;

private slots:
    void sendRemoveSignal() override;
};

}

#endif // QPRODUCTSWIDGETLISTITEM_H
