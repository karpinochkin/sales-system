#ifndef QUSERTABLETAB_H
#define QUSERTABLETAB_H

#include "../commonClientFiles/QNetManager/qnetmanager.h"
#include "../QAbstractTab/qabstracttabletab.h"
#include "qusereditdialog.h"

namespace Gui::DatabaseTabs {

class QUserTableTab : public AbstractTableTab::QAbstractTableTab
{
    Q_OBJECT
public:
    explicit QUserTableTab(QNetManager *networkManager,
                           QWidget *parent = nullptr);
    ~QUserTableTab() override = default;

private:
    QNetManager *m_netManager = nullptr;

    void editProcess(QUser &value);
    void addProcess(QUser &value);
    QVector<QVariant> getSalesObjectVector() override;
    void processingAddItemsToTable(int row, const QVariant &) override;

private slots:
    void slotEditItem(int ID);
    void slotAddItem();
};

}

#endif // QUSERTABLETAB_H
