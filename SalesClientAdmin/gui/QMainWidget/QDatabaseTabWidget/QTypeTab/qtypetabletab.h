#ifndef QTYPETABLETAB_H
#define QTYPETABLETAB_H

#include <QWidget>
#include "../commonClientFiles/QNetManager/qnetmanager.h"
#include "QTypeEditDialog/qtypeeditdialog.h"
#include "../QAbstractTab/qabstracttabletab.h"

namespace Gui::DatabaseTabs {

class QTypeTableTab : public AbstractTableTab::QAbstractTableTab
{
    Q_OBJECT
public:
    explicit QTypeTableTab(QNetManager *networkManager,
                           QWidget *parent = nullptr);
    ~QTypeTableTab() override = default;

private:
    QNetManager *m_netManager = nullptr;

    void editProcess(QPaymentType &type);
    void addProcess(QPaymentType &type);
    QVector<QVariant> getSalesObjectVector() override;
    void processingAddItemsToTable(int row, const QVariant &) override;

private slots:
    void slotEditItem(int typeID);
    void slotAddItem();
};

}

#endif // QTYPETABLETAB_H
