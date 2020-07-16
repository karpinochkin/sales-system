#include "qabstracttab.h"

using namespace Gui::DatabaseTabs::AbstractTab;

QAbstractTab::QAbstractTab(QNetManager *networkManager, QWidget *parent)
    : QWidget(parent),
      m_networkManager(networkManager)
{
    this->createWidgets();
    this->setGui();
    this->connectsWidgets();
}

void QAbstractTab::createWidgets()
{
    mainLayout = new QVBoxLayout(this);
    upperLayout = new QHBoxLayout;
    addItemButton = new QPushButton(tr("Добавить"), this);
    searchIconLabel = new QLabel(this);
    searchEdit = new QLineEdit(this);
    searchIcon = new QPixmap(":/images/icons/other/Search.png");
    m_listWidget = new QListWidget(this);
}

void QAbstractTab::setGui()
{
    this->setLayout(mainLayout);
    *searchIcon = searchIcon->scaled(24,24,Qt::KeepAspectRatio);
    searchIconLabel->setPixmap(*searchIcon);

    this->listWidgetGuiSettings();

    upperLayout->addWidget(searchIconLabel);
    upperLayout->addWidget(searchEdit, 1);
    upperLayout->addWidget(addItemButton);

    mainLayout->addLayout(upperLayout);
    mainLayout->addWidget(m_listWidget);
}

void QAbstractTab::listWidgetGuiSettings()
{
    m_listWidget->setFlow(QListView::LeftToRight);
    m_listWidget->setResizeMode(QListView::Adjust);
    m_listWidget->setGridSize(QSize(180, 230));
    m_listWidget->setSpacing(10);
    m_listWidget->setViewMode(QListView::IconMode);
}

void QAbstractTab::closeEvent(QCloseEvent *)
{

}

void QAbstractTab::connectItems()
{
    connect(currentItem, &AbstractTab::QAbstractWidgetListItem::signalEdit,
            this, &QAbstractTab::slotEditItem);
    connect(currentItem, &AbstractTab::QAbstractWidgetListItem::signalRemove,
            this, &QAbstractTab::slotRemoveItem);
}

void QAbstractTab::removeErrorMessage()
{
    QMessageBox::critical(this,
                          tr("Ошибка"),
                          tr("Этот элемент нельзя удалить. Проверьте связи."));
}

void QAbstractTab::slotSearchTextChanged(QString text)
{
    for (int i = 0; i < m_listWidget->count(); i++) {
        currentItem = dynamic_cast<AbstractTab::QAbstractWidgetListItem*>
                (m_listWidget->itemWidget(m_listWidget->item(i)));

        QString name = getCurrentItemName();
        if (name.contains(text)
                || text == nullptr
                || text == "") {
            m_listWidget->item(i)->setHidden(false);
        }
        else {
            m_listWidget->item(i)->setHidden(true);
        }
    }
}

void QAbstractTab::templateCreateNewItemOnDisplay(const QSalesObjects &object)
{
    QListWidgetItem *item = new QListWidgetItem(m_listWidget);
    m_listWidget->addItem(item);
    currentItem = createOwnItem(object);
    connectItems();
    item->setSizeHint(currentItem->sizeHint());
    m_listWidget->setItemWidget(item, currentItem);
}

void QAbstractTab::slotUpdateItems()
{

}

void QAbstractTab::slotRemoveAnswer(bool answer, int id, const QString &name)
{
    if (answer) {
        this->removeFromLocalDatabase(id, name);
        this->slotUpdateItems();
    }
    else {
        this->removeErrorMessage();
    }
}

void QAbstractTab::connectsWidgets()
{
    connect(addItemButton, &QPushButton::clicked,
            this, &QAbstractTab::slotAddItem);
    connect(searchEdit, &QLineEdit::textChanged,
            this, &QAbstractTab::slotSearchTextChanged);
    connect(m_networkManager, &QNetManager::signalProductsLoaded,
            this, &QAbstractTab::slotUpdateItems);
}

void QAbstractTab::addWidgetToMainLayout(QWidget *widget)
{
    mainLayout->addWidget(widget);
}


