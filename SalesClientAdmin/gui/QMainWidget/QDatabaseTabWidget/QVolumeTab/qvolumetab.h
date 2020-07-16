#ifndef QVOLUMETAB_H
#define QVOLUMETAB_H

#include "../QAbstractTab/qabstracttab.h"
#include "qvolumewidgetlistitem.h"
#include "qvolumeeditdialog.h"

namespace Gui::DatabaseTabs {

class QVolumeTab : public AbstractTab::QAbstractTab
{
    Q_OBJECT
public:
    explicit QVolumeTab(QNetManager *m_networkManager,
                        QWidget *parent = nullptr);
    ~QVolumeTab() override = default;

     DatabaseCommands::QVolumeProductCommands *getDatabaseVolumeCommands() const;

private:
     AbstractTab::QAbstractWidgetListItem * createOwnItem(const QSalesObjects &object) override;
     void removeFromLocalDatabase(int id, const QString &name) override;
     QString getCurrentItemName() override;
     void updateItemOnDisplay(const QVolumeProduct &value);
     void addProcess(QVolumeProduct &value);
     void editProcess(QVolumeProduct &value);

private slots:
     void slotAddItem() override;
     void slotEditItem(QSalesObjects &) override;
     void slotRemoveItem(int id) override;
     void slotUpdateItems() override;
};

}

#endif // QVOLUMETAB_H
