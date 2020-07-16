#include "qusertab.h"

using namespace Gui::DatabaseTabs;

QUserTab::QUserTab(QNetManager *networkManager, QWidget *parent)
    : QAbstractTab(networkManager, parent)
{
    this->slotUpdateItems();
    connect(m_networkManager, &QNetManager::signalUsersLoaded,
            this, &QUserTab::slotUpdateItems);
    connect(m_networkManager, &QNetManager::signalRemoveUser,
            this, &QUserTab::slotRemoveAnswer);
}

DatabaseCommands::QUserCommands *QUserTab::getDatabaseUserCommands() const
{
    return m_networkManager->DatabaseCommands()->user;
}

AbstractTab::QAbstractWidgetListItem *QUserTab::createOwnItem(const QSalesObjects &object)
{
    return  new QUserWidgetListItem(static_cast<const QUser&>(object),
                                    m_listWidget);
}

void QUserTab::removeFromLocalDatabase(int id, const QString &name)
{
    this->getDatabaseUserCommands()->remove(id, name);
}

QString QUserTab::getCurrentItemName()
{
    QString output = dynamic_cast<QUserWidgetListItem*>(currentItem)->getItemName();

     return output;
}

void QUserTab::updateItemOnDisplay(const QUser &user)
{
    for (int i = 0; i < m_listWidget->count(); i++) {
        currentItem = dynamic_cast<QUserWidgetListItem*>
                (m_listWidget->itemWidget(m_listWidget->item(i)));

        QUser currentUser = reinterpret_cast<QUserWidgetListItem*>(currentItem)->getUser();

        if (currentUser.id == user.id) {
            reinterpret_cast<QUserWidgetListItem*>(currentItem)->setUser(user);

            break;
        }
    }
}

void QUserTab::addProcess(QUser &user)
{
    bool result = m_networkManager->DatabaseCommands()->user->add(user);
    if (result) {
        m_networkManager->CommandsToServer()->user->send(user);
        // Обновляем все айтемы на экране
        this->slotUpdateItems();
    }
}

void QUserTab::editProcess(QUser &user)
{
    // Добавляем изменение в локальную бд
    bool result = m_networkManager->DatabaseCommands()->user->edit(user);
    if (result) {
        // Отправляем изменения на сервер
        m_networkManager->CommandsToServer()->user->send(user);
        //Обновляем измененный элемент
        this->updateItemOnDisplay(user);
    }
}

void QUserTab::slotAddItem()
{
    bool ok = false;
    QUser user = QUserEditDialog::show(m_networkManager->DatabaseCommands(),
                                       &ok,
                                       this);
    if (ok) {
        this->addProcess(user);
    }
}

void QUserTab::slotUpdateItems()
{
    m_listWidget->clear();

    QVector<QUser> users = this->getDatabaseUserCommands()->getUsers();

    for (int i = 0; i < users.size(); i++) {
        QAbstractTab::templateCreateNewItemOnDisplay
                (static_cast<const QSalesObjects&>(users.at(i)));
    }
}

void QUserTab::slotRemoveItem(int id)
{
    if (m_networkManager->isAuthorized()) {
        QUser user = getDatabaseUserCommands()->get(id);

        if(!isCurrentUser(user)) {
            m_networkManager->CommandsToServer()->user->remove(user.id, user.login);
        }
        else {
            QMessageBox::critical(this,
                                  tr("Ошибка"),
                                  tr("Вы не можете удалить сами себя."));
        }
    }
    else {
        QMessageBox::critical(this,
                              tr("Ошибка"),
                              tr("Пользователь не может быть удален. Нет соединения с сервером. Попробуйте позже."));
    }
}

bool QUserTab::isCurrentUser(const QUser &user)
{
    bool result = false;
    if (user.id == m_networkManager->getCurrentUser().id) {
        result = true;
    }
    return result;
}

void QUserTab::slotEditItem(QSalesObjects &object)
{
    QUser user = static_cast<QUser&>(object);

    bool ok = false;
    QUser output = QUserEditDialog::show(user,
                                         m_networkManager->DatabaseCommands(),
                                         &ok,
                                         this);
    if (ok) {
        this->editProcess(output);
    }
}
