#ifndef QVOLUMEWIDGETLISTITEM_H
#define QVOLUMEWIDGETLISTITEM_H

#include "../QAbstractTab/QAbstractWidgetListItem.h"
#include "../commonFiles/SalesSystem/QVolumeProduct/qvolumeproduct.h"

namespace Gui::DatabaseTabs {

class QVolumeWidgetListItem : public AbstractTab::QAbstractWidgetListItem
{
    Q_OBJECT
public:
    explicit QVolumeWidgetListItem(const QVolumeProduct &volume,
                                   QWidget *parent = nullptr);
    ~QVolumeWidgetListItem() override = default;

    void setVolume(const QVolumeProduct &volume);
    QVolumeProduct getVolume() const;
    void updateItem();

private:
    QVolumeProduct volume;
    void mouseDoubleClickEvent(QMouseEvent *) override;

private slots:
    void sendRemoveSignal() override;
};

}

#endif // QVOLUMEWIDGETLISTITEM_H
