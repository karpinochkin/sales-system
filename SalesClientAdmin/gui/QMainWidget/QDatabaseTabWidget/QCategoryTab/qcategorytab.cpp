#include "qcategorytab.h"

using namespace Gui::DatabaseTabs;

QCategoryTab::QCategoryTab(QNetManager *networkManager, QWidget *parent)
: QAbstractTab(networkManager, parent)
{
    this->slotUpdateItems();
    connect(m_networkManager, &QNetManager::signalCategoriesLoaded,
            this, &QCategoryTab::slotUpdateItems);
    connect(m_networkManager, &QNetManager::signalRemoveCategory,
            this, &QCategoryTab::slotRemoveAnswer);
}

DatabaseCommands::QSalesCategoryCommands *QCategoryTab::getDatabaseCategoryCommands() const
{
    return m_networkManager->DatabaseCommands()->category;
}

AbstractTab::QAbstractWidgetListItem *QCategoryTab::createOwnItem(const QSalesObjects &object)
{
    return  new QCategoryWidgetListItem(static_cast<const QSalesCategory&>(object),
                                    m_listWidget);
}

void QCategoryTab::removeFromLocalDatabase(int id, const QString &name)
{
    this->getDatabaseCategoryCommands()->remove(id, name);
}

QString QCategoryTab::getCurrentItemName()
{
    QString output = dynamic_cast<QCategoryWidgetListItem*>(currentItem)->getItemName();

    return output;
}

void QCategoryTab::updateItemOnDisplay(const QSalesCategory &category)
{
    for (int i = 0; i < m_listWidget->count(); i++) {
         currentItem = dynamic_cast<QCategoryWidgetListItem*>
                (m_listWidget->itemWidget(m_listWidget->item(i)));

         QSalesCategory currentCategory = reinterpret_cast<QCategoryWidgetListItem*>(currentItem)->getCategory();

        if (currentCategory.id == category.id) {
            reinterpret_cast<QCategoryWidgetListItem*>(currentItem)->setCategory(category);

            break;
        }
    }
}

void QCategoryTab::addProcess(QSalesCategory &category)
{
    bool result = m_networkManager->DatabaseCommands()->category->add(category);
    if (result) {
        m_networkManager->CommandsToServer()->category->send(category);
        qDebug() << category.toString();
        // Обновляем все айтемы на экране
        this->slotUpdateItems();
    }
}

void QCategoryTab::editProcess(QSalesCategory &category)
{
    // Добавляем изменение в локальную бд
    bool result = m_networkManager->DatabaseCommands()->category->edit(category);
    if (result) {
        // Отправляем изменения на сервер
        m_networkManager->CommandsToServer()->category->send(category);
        qDebug() << category.toString();
        //Обновляем измененный элемент
        this->updateItemOnDisplay(category);
    }
}

void QCategoryTab::slotAddItem()
{
    bool ok = false;
    QSalesCategory category = QCategoryEditDialog::show(m_networkManager->DatabaseCommands(),
                                                       &ok,
                                                       this);
    if (ok) {
        this->addProcess(category);
    }
}

void QCategoryTab::slotUpdateItems()
{
    m_listWidget->clear();

    QVector<QSalesCategory> categories = this->getDatabaseCategoryCommands()->getCategories();

    for (int i = 0; i < categories.size(); i++) {
        QAbstractTab::templateCreateNewItemOnDisplay(static_cast<const QSalesObjects&>(categories.at(i)));
    }
}

void QCategoryTab::slotRemoveItem(int id)
{
    if (m_networkManager->isAuthorized()) {
        QSalesCategory category = getDatabaseCategoryCommands()->get(id);
        m_networkManager->CommandsToServer()->category->remove(category.id, category.name);
    }
    else {
        QMessageBox::critical(this,
                              tr("Ошибка"),
                              tr("Тип не может быть удален. Нет соединения с сервером. Попробуйте позже."));
    }
}

void QCategoryTab::slotEditItem(QSalesObjects &object)
{
    QSalesCategory category = static_cast<QSalesCategory&>(object);

    bool ok = false;
    QSalesCategory output = QCategoryEditDialog::show(category,
                                                m_networkManager->DatabaseCommands(),
                                                &ok,
                                                this);
    if (ok) {
        this->editProcess(output);
    }
}
