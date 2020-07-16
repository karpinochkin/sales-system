#include "qdatabasetabwidget.h"

using namespace Gui::DatabaseTabs;

QDatabaseTabsWidget::QDatabaseTabsWidget(QNetManager *networkManager, QWidget *parent)
    : QWidget(parent),
      networkManager(networkManager)
{
    this->setGui();
}

QDatabaseTabsWidget::~QDatabaseTabsWidget()
{

}

void QDatabaseTabsWidget::createWidgets()
{
    mainLayout = new QHBoxLayout(this);
    tabWidget = new QTabWidget(this);
    pictureTab = new QPictureTab(networkManager, this);
    typeTableTab = new QTypeTableTab(networkManager, this);
    volumeTableTab = new QVolumeTableTab(networkManager, this);
    userTableTab = new QUserTableTab(networkManager, this);
    pointSaleTableTab = new QPointSaleTableTab(networkManager, this);
    categoryTab = new QCategoryTab(networkManager, this);
    productsTab = new QProductsTab(networkManager, this);
    pricesTableTab = new QPricesTableTab(networkManager, this);

    tabWidget->addTab(productsTab, tr("Товары"));
    tabWidget->addTab(categoryTab, tr("Категории"));
    tabWidget->addTab(pointSaleTableTab, tr("Точки продаж"));
    tabWidget->addTab(pictureTab, tr("Изображения"));
    tabWidget->addTab(typeTableTab, tr("Типы оплаты"));
    tabWidget->addTab(volumeTableTab, tr("Величины"));
    tabWidget->addTab(userTableTab, tr("Пользователи"));
    tabWidget->addTab(pricesTableTab, tr("Цены"));

    mainLayout->addWidget(tabWidget);
}

void QDatabaseTabsWidget::setGui()
{
    this->createWidgets();
    this->connectWidgets();
}

void QDatabaseTabsWidget::connectWidgets()
{

}
