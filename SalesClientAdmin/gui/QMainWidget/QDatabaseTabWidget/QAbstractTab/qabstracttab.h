#ifndef QABSTRACTTAB_H
#define QABSTRACTTAB_H

#include <QWidget>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QScrollArea>
#include <QListWidget>
#include <QFont>
#include <QPushButton>
#include <QTabWidget>
#include <QLabel>
#include <QLineEdit>
#include <QDebug>
#include <QMessageBox>
#include "../commonClientFiles/QNetManager/qnetmanager.h"
#include "QAbstractWidgetListItem.h"

namespace Gui::DatabaseTabs::AbstractTab {

class QAbstractTab : public QWidget
{
    Q_OBJECT
public:
    explicit QAbstractTab(QNetManager *m_networkManager, QWidget *parent = nullptr);
    ~QAbstractTab() override  = default;

protected:
    QNetManager *m_networkManager = nullptr;
    QAbstractWidgetListItem *currentItem = nullptr;
    QListWidget *m_listWidget = nullptr;

    void templateCreateNewItemOnDisplay(const QSalesObjects &object);
    void addWidgetToMainLayout(QWidget *);
    virtual void removeFromLocalDatabase(int id, const QString &name) = 0;
    virtual void listWidgetGuiSettings();
    virtual QString getCurrentItemName() = 0;
    virtual QAbstractWidgetListItem* createOwnItem(const QSalesObjects &object) = 0;
    void closeEvent(QCloseEvent *) override;

private:
    QVBoxLayout *mainLayout = nullptr;
    QHBoxLayout *upperLayout = nullptr;
    QPushButton *addItemButton = nullptr;
    QLabel *searchIconLabel = nullptr;
    QPixmap *searchIcon = nullptr;
    QLineEdit *searchEdit = nullptr;

    void createWidgets();
    void setGui();
    void connectsWidgets();
    void connectItems();
    void removeErrorMessage();

protected slots:
    void slotSearchTextChanged(QString);
    virtual void slotAddItem() = 0;
    virtual void slotEditItem(QSalesObjects&) = 0;
    virtual void slotRemoveItem(int id) = 0;
    virtual void slotUpdateItems();
    void slotRemoveAnswer(bool answer, int id, const QString &name);
};

}

#endif // QABSTRACTTAB_H
