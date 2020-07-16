#include "qusertabletab.h"

Gui::DatabaseTabs::QUserTableTab::QUserTableTab(QNetManager *networkManager,
                                                QWidget *parent)
    : AbstractTableTab::QAbstractTableTab(AbstractTableTab::ColumnsSettings {
                                          4, {tr("Логин"),
                                          tr("Имя"),
                                          tr("Фамилия"),
                                          tr("Отчество")}
                                          },
                                          parent),
      m_netManager(networkManager)
{
//    connect(m_networkManager, &QNetManager::signalRemoveUser,
//            this, &QUserTab::slotRemoveAnswer);
    connect(m_netManager, &QNetManager::signalUsersLoaded,
            this, &QAbstractTableTab::updateItems);
    connect(this, &QAbstractTableTab::editItem,
            this, &QUserTableTab::slotEditItem);
    connect(this, &QAbstractTableTab::addItem,
            this, &QUserTableTab::slotAddItem);
    emit (updateItems());
}

void Gui::DatabaseTabs::QUserTableTab::editProcess(QUser &value)
{
    // Добавляем изменение в локальную бд
    bool result = m_netManager->DatabaseCommands()->user->edit(value);
    if (result) {
        // Отправляем изменения на сервер
        m_netManager->CommandsToServer()->user->send(value);
        emit (updateItems());
    }
}

void Gui::DatabaseTabs::QUserTableTab::addProcess(QUser &value)
{
    bool result = m_netManager->DatabaseCommands()->user->add(value);
    if (result) {
        m_netManager->CommandsToServer()->user->send(value);
        // Обновляем все айтемы на экране
        emit (updateItems());
    }
}

QVector<QVariant> Gui::DatabaseTabs::QUserTableTab::getSalesObjectVector()
{
    QVector<QUser> users = m_netManager->DatabaseCommands()->user->getUsers();

    QVector<QVariant> output;
    for(auto user : users) {
        output.push_back(QVariant::fromValue(user));
    }
    return output;
}

void Gui::DatabaseTabs::QUserTableTab::processingAddItemsToTable(int row, const QVariant &value)
{
    QUser user = unpack<QUser>(value);

    auto *itemLogin = createItem(user.login, user.id);
    setItemToTable(row, 0, itemLogin);

    auto *itemName = createItem(user.name, user.id);
    setItemToTable(row, 1, itemName);

    auto *itemSurname = createItem(user.surname, user.id);
    setItemToTable(row, 2, itemSurname);

    auto *itemPatronymic = createItem(user.patronymic, user.id);
    setItemToTable(row, 3, itemPatronymic);
}

void Gui::DatabaseTabs::QUserTableTab::slotEditItem(int ID)
{
    QUser user = m_netManager->DatabaseCommands()->user->get(ID);

    bool ok = false;
    QUser output = QUserEditDialog::show(user,
                                         m_netManager->DatabaseCommands(),
                                         &ok,
                                         this);
    if (ok) {
        this->editProcess(output);
    }
}

void Gui::DatabaseTabs::QUserTableTab::slotAddItem()
{
    bool ok = false;
    QUser user = QUserEditDialog::show(m_netManager->DatabaseCommands(),
                                       &ok,
                                       this);
    if (ok) {
        this->addProcess(user);
    }
}
