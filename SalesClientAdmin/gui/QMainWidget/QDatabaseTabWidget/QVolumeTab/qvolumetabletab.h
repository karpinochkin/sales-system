#ifndef QVOLUMETABLETAB_H
#define QVOLUMETABLETAB_H

#include "../commonClientFiles/QNetManager/qnetmanager.h"
#include "../QAbstractTab/qabstracttabletab.h"
#include "qvolumeeditdialog.h"

namespace Gui::DatabaseTabs {

class QVolumeTableTab : public AbstractTableTab::QAbstractTableTab
{
    Q_OBJECT
public:
    explicit QVolumeTableTab(QNetManager *networkManager,
                             QWidget *parent = nullptr);
    ~QVolumeTableTab() override = default;

private:
    QNetManager *m_netManager = nullptr;

    void editProcess(QVolumeProduct &value);
    void addProcess(QVolumeProduct &value);
    QVector<QVariant> getSalesObjectVector() override;
    void processingAddItemsToTable(int row, const QVariant &) override;

private slots:
    void slotEditItem(int ID);
    void slotAddItem();
};

}

#endif // QVOLUMETABLETAB_H
