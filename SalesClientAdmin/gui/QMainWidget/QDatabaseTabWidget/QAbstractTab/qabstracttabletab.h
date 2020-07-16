#ifndef QABSTRACTTABLETAB_H
#define QABSTRACTTABLETAB_H

#include <QWidget>
#include "../commonClientFiles/QNetManager/qnetmanager.h"
#include <QTableWidget>
#include <QLineEdit>
#include <QShortcut>
#include <QMenu>
#include <QAction>
#include <QItemSelectionModel>
#include <QApplication>
#include <QClipboard>

namespace Gui::DatabaseTabs::AbstractTableTab {

struct ColumnsSettings {
    int columnCount = 0;
    QStringList labels;
};

class QAbstractTableTab : public QWidget
{
    Q_OBJECT
public:
    explicit QAbstractTableTab(const ColumnsSettings&,
                               QWidget *parent = nullptr);
    ~QAbstractTableTab() override  = default;

protected:
    void closeEvent(QCloseEvent *) override;
    void setColumnsSettings(const ColumnsSettings &);
    virtual QVector<QVariant> getSalesObjectVector() = 0;
    virtual void processingAddItemsToTable(int row, const QVariant&) = 0;
    QTableWidgetItem *createItem(const QString &text,
                                int id);
    void setItemToTable(int row, int column, QTableWidgetItem *item);

    template< typename T >
    T unpack( const QVariant& var, const T& defVal = T() ) {
        if( var.isValid() && var.canConvert< T >() ) {
            return var.value< T >();
        }
        return defVal;
    }

private:
    QTableWidget *table = nullptr;
    QVBoxLayout *mainLayout = nullptr;
    QHBoxLayout *upperLayout = nullptr;
    QPushButton *addItemButton = nullptr;
    QLabel *searchIconLabel = nullptr;
    QPixmap *searchIcon = nullptr;
    QLineEdit *searchEdit = nullptr;

    QMenu *menuTable = nullptr ;
    QAction *actionSelectAll = nullptr;
    QAction *actionCopy = nullptr;
    QShortcut *shortcutCopy = nullptr;
    QShortcut *shortcutSelectAll = nullptr;
    QItemSelectionModel *selectionModel;

    void createWidgets();
    void setGui();
    void connects();
    void setColumnsCount(int count);
    void setColumnsLabel(const QStringList &list);

private slots:
    void slotSearchTextChanged(QString);
    void slotUpdateItems();
    void slotMenuRequested(QPoint);
    void slotSelectAll();
    void slotCopy();

signals:
    /// updateItems : this signal call slotUpdateItems
    void updateItems();

    void editItem(int ItemID);
    void addItem();
};

}

#endif // QABSTRACTTABLETAB_H
