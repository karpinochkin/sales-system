#ifndef QPICTURETAB_H
#define QPICTURETAB_H

#include "../QAbstractTab/qabstracttab.h"
#include "../commonFiles/SalesSystem/QProductPicture/qproductpicture.h"
#include "qpicturewidgetlistitem.h"
#include "QPictureEditDialog/qpictureeditdialog.h"

namespace Gui::DatabaseTabs {

class QPictureTab : public AbstractTab::QAbstractTab
{
    Q_OBJECT
public:
    QPictureTab(QNetManager *m_networkManager, QWidget *parent = nullptr);
    ~QPictureTab() override = default;

private:
    QPushButton *updateButton = nullptr;
    DatabaseCommands::QProductPictureCommands* getDatabasePictureCommands() const;

    AbstractTab::QAbstractWidgetListItem * createOwnItem(const QSalesObjects &object) override;
    void removeFromLocalDatabase(int id, const QString &name) override;
    QString getCurrentItemName() override;

private slots:
    void slotUpdateFromServer();
    void slotAddItem() override;
    void slotUpdateItems() override;
    void slotRemoveItem(int id) override;
    void slotEditItem(QSalesObjects &) override;
};

}

#endif // QPICTURETAB_H
