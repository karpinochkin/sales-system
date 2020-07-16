#include "qvolumetab.h"

using namespace Gui::DatabaseTabs;

QVolumeTab::QVolumeTab(QNetManager *networkManager, QWidget *parent)
    : QAbstractTab(networkManager, parent)
{
    this->slotUpdateItems();
    connect(m_networkManager, &QNetManager::signalVolumesLoaded,
            this, &QVolumeTab::slotUpdateItems);
    connect(m_networkManager, &QNetManager::signalRemoveVolume,
            this, &QVolumeTab::slotRemoveAnswer);
}

DatabaseCommands::QVolumeProductCommands *QVolumeTab::getDatabaseVolumeCommands() const
{
    return m_networkManager->DatabaseCommands()->volume;
}

AbstractTab::QAbstractWidgetListItem *QVolumeTab::createOwnItem(const QSalesObjects &object)
{
    return new QVolumeWidgetListItem(static_cast<const QVolumeProduct&>(object),
                                     m_listWidget);
}

void QVolumeTab::removeFromLocalDatabase(int id, const QString &name)
{
    this->getDatabaseVolumeCommands()->remove(id, name);
}

QString QVolumeTab::getCurrentItemName()
{
    QString output = dynamic_cast<QVolumeWidgetListItem*>(currentItem)->getItemName();

     return output;
}

void QVolumeTab::updateItemOnDisplay(const QVolumeProduct &value)
{
    for (int i = 0; i < m_listWidget->count(); i++) {
         currentItem = dynamic_cast<QVolumeWidgetListItem*>
                (m_listWidget->itemWidget(m_listWidget->item(i)));

         QVolumeProduct currentType = reinterpret_cast<QVolumeWidgetListItem*>(currentItem)->getVolume();

        if (currentType.id == value.id) {
            reinterpret_cast<QVolumeWidgetListItem*>(currentItem)->setVolume(value);

            break;
        }
    }
}

void QVolumeTab::addProcess(QVolumeProduct &value)
{
    bool result = m_networkManager->DatabaseCommands()->volume->add(value);
    if (result) {
        m_networkManager->CommandsToServer()->volume->send(value);
        // Обновляем все айтемы на экране
        this->slotUpdateItems();
    }
}

void QVolumeTab::editProcess(QVolumeProduct &value)
{
    // Добавляем изменение в локальную бд
    bool result = m_networkManager->DatabaseCommands()->volume->edit(value);
    if (result) {
        // Отправляем изменения на сервер
        m_networkManager->CommandsToServer()->volume->send(value);
        //Обновляем измененный элемент
        this->updateItemOnDisplay(value);
    }
}

void QVolumeTab::slotAddItem()
{
    bool ok = false;
    QVolumeProduct value = QVolumeEditDialog::show(m_networkManager->DatabaseCommands(),
                                                       &ok,
                                                       this);
    if (ok) {
        this->addProcess(value);
    }
}

void QVolumeTab::slotEditItem(QSalesObjects &object)
{
    QVolumeProduct value = static_cast<QVolumeProduct&>(object);

    bool ok = false;
    QVolumeProduct output = QVolumeEditDialog::show(value,
                                                m_networkManager->DatabaseCommands(),
                                                &ok,
                                                this);
    if (ok) {
        this->editProcess(output);
    }
}

void QVolumeTab::slotRemoveItem(int id)
{
    if (m_networkManager->isAuthorized()) {
        QVolumeProduct value = getDatabaseVolumeCommands()->get(id);
        m_networkManager->CommandsToServer()->volume->remove(value.id, value.name);
    }
    else {
        QMessageBox::critical(this,
                              tr("Ошибка"),
                              tr("Нельзя удалить. Нет соединения с сервером. Попробуйте позже."));
    }
}

void QVolumeTab::slotUpdateItems()
{
    m_listWidget->clear();

    QVector<QVolumeProduct> volumes = this->getDatabaseVolumeCommands()->getVolumes();

    for (int i = 0; i < volumes.size(); i++) {
        QAbstractTab::templateCreateNewItemOnDisplay(static_cast<const QSalesObjects&>(volumes.at(i)));
    }
}
