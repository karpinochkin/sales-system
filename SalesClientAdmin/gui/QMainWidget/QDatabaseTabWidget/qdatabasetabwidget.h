#ifndef QDATABASETABWIDGET_H
#define QDATABASETABWIDGET_H

#include <QWidget>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QScrollArea>
#include <QListWidget>
#include <QFont>
#include <QPushButton>
#include <QTabWidget>
#include "QCategoryTab/qcategorytab.h"
#include "QProductsTab/qproductstab.h"
#include "QPricesTab/qpricestabletab.h"
#include "QTypeTab/qtypetabletab.h"
#include "QPointSaleTab/qpointsaletabletab.h"
#include "QUserTab/qusertabletab.h"
#include "QVolumeTab/qvolumetabletab.h"
#include "QPictureTab/qpicturetab.h"

namespace Gui::DatabaseTabs {

class QDatabaseTabsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit QDatabaseTabsWidget(QNetManager *networkManager, QWidget *parent = nullptr);
    ~QDatabaseTabsWidget();

private:
    QNetManager *networkManager = nullptr;
    QHBoxLayout *mainLayout = nullptr;
    QTabWidget *tabWidget = nullptr;
    QPictureTab *pictureTab = nullptr;
    QTypeTableTab *typeTableTab = nullptr;
    QVolumeTableTab *volumeTableTab = nullptr;
    QUserTableTab *userTableTab = nullptr;
    QPointSaleTableTab *pointSaleTableTab= nullptr;
    QCategoryTab *categoryTab = nullptr;
    QProductsTab *productsTab = nullptr;
    QPricesTableTab *pricesTableTab = nullptr;

    void setGui();
    void createWidgets();
    void connectWidgets();
};

}

#endif // QDATABASETABWIDGET_H
