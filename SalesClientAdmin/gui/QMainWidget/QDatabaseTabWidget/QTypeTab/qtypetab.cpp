#include "qtypetab.h"

using namespace Gui::DatabaseTabs;

QTypeTab::QTypeTab(QNetManager *networkManager, QWidget *parent)
    : QAbstractTab(networkManager, parent)
{
    this->slotUpdateItems();
    connect(m_networkManager, &QNetManager::signalTypesLoaded,
            this, &QTypeTab::slotUpdateItems);
    connect(m_networkManager, &QNetManager::signalRemoveType,
            this, &QTypeTab::slotRemoveAnswer);
}

DatabaseCommands::QPaymentTypeCommands *QTypeTab::getDatabaseTypeCommands() const
{
    return m_networkManager->DatabaseCommands()->type;
}

AbstractTab::QAbstractWidgetListItem *QTypeTab::createOwnItem(const QSalesObjects &object)
{
    return  new QTypeWidgetListItem(static_cast<const QPaymentType&>(object),
                                    m_listWidget);
}

void QTypeTab::removeFromLocalDatabase(int id, const QString &name)
{
    this->getDatabaseTypeCommands()->remove(id, name);
}

QString QTypeTab::getCurrentItemName()
{
    QString output = dynamic_cast<QTypeWidgetListItem*>(currentItem)->getItemName();

     return output;
}

void QTypeTab::slotUpdateItems()
{
    m_listWidget->clear();

    QVector<QPaymentType> types = this->getDatabaseTypeCommands()->getTypes();

    for (int i = 0; i < types.size(); i++) {
        QAbstractTab::templateCreateNewItemOnDisplay(static_cast<const QSalesObjects&>(types.at(i)));
    }
}

void QTypeTab::slotRemoveItem(int id)
{
    if (m_networkManager->isAuthorized()) {
        QPaymentType type = getDatabaseTypeCommands()->get(id);
        m_networkManager->CommandsToServer()->type->remove(type.id, type.name);
    }
    else {
        QMessageBox::critical(this,
                              tr("Ошибка"),
                              tr("Тип не может быть удален. Нет соединения с сервером. Попробуйте позже."));
    }
}

void QTypeTab::slotEditItem(QSalesObjects &object)
{
    QPaymentType type = static_cast<QPaymentType&>(object);

    bool ok = false;
    QPaymentType output = QTypeEditDialog::show(type,
                                                m_networkManager->DatabaseCommands(),
                                                &ok,
                                                this);
    if (ok) {
        this->editProcess(output);
    }
}

void QTypeTab::editProcess(QPaymentType &type)
{
    // Добавляем изменение в локальную бд
    bool result = m_networkManager->DatabaseCommands()->type->edit(type);
    if (result) {
        // Отправляем изменения на сервер
        m_networkManager->CommandsToServer()->type->send(type);
        //Обновляем измененный элемент
        this->updateItemOnDisplay(type);
    }
}

void QTypeTab::slotAddItem()
{
    bool ok = false;
    QPaymentType type = QTypeEditDialog::show(m_networkManager->DatabaseCommands(),
                                                       &ok,
                                                       this);
    if (ok) {
        this->addProcess(type);
    }
}

void QTypeTab::addProcess(QPaymentType &type)
{

    bool result = m_networkManager->DatabaseCommands()->type->add(type);
    if (result) {
        m_networkManager->CommandsToServer()->type->send(type);
        // Обновляем все айтемы на экране
        this->slotUpdateItems();
    }
}

void QTypeTab::updateItemOnDisplay(const QPaymentType &type)
{
    for (int i = 0; i < m_listWidget->count(); i++) {
         currentItem = dynamic_cast<QTypeWidgetListItem*>
                (m_listWidget->itemWidget(m_listWidget->item(i)));

         QPaymentType currentType = reinterpret_cast<QTypeWidgetListItem*>(currentItem)->getType();

        if (currentType.id == type.id) {
            reinterpret_cast<QTypeWidgetListItem*>(currentItem)->setType(type);

            break;
        }
    }
}

