#ifndef QPICTUREWIDGETLISTITEM_H
#define QPICTUREWIDGETLISTITEM_H

#include "../QAbstractTab/QAbstractWidgetListItem.h"
#include "../commonFiles/SalesSystem/QProductPicture/qproductpicture.h"

namespace Gui::DatabaseTabs {

class QPictureWidgetListItem : public AbstractTab::QAbstractWidgetListItem
{
public:
    QPictureWidgetListItem(const QProductPicture& picture, QWidget *parent = nullptr);
    ~QPictureWidgetListItem() override = default;

    void setPictureInformation(const QProductPicture &value);
    QProductPicture getPictureInformation() const;
    void updateItem();

private:
    QProductPicture picture;

    void mouseDoubleClickEvent(QMouseEvent *) override;

private slots:
    void sendRemoveSignal() override;

};

}

#endif // QPICTUREWIDGETLISTITEM_H
