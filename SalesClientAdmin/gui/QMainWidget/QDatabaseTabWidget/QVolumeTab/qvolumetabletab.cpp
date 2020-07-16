#include "qvolumetabletab.h"

Gui::DatabaseTabs::QVolumeTableTab::QVolumeTableTab(QNetManager *networkManager,
                                                    QWidget *parent)
    : AbstractTableTab::QAbstractTableTab(AbstractTableTab::ColumnsSettings {
                                          4, {tr("Название"),
                                          tr("Значение"),
                                          tr("Описание"),
                                          tr("Величина")}
                                          },
                                          parent),
      m_netManager(networkManager)
{
//    connect(m_networkManager, &QNetManager::signalRemoveVolume,
//            this, &QVolumeTab::slotRemoveAnswer);
    connect(m_netManager, &QNetManager::signalVolumesLoaded,
            this, &QAbstractTableTab::updateItems);
    connect(this, &QAbstractTableTab::editItem,
            this, &QVolumeTableTab::slotEditItem);
    connect(this, &QAbstractTableTab::addItem,
            this, &QVolumeTableTab::slotAddItem);
    emit (updateItems());
}

void Gui::DatabaseTabs::QVolumeTableTab::editProcess(QVolumeProduct &value)
{
    // Добавляем изменение в локальную бд
    bool result = m_netManager->DatabaseCommands()->volume->edit(value);
    if (result) {
        // Отправляем изменения на сервер
        m_netManager->CommandsToServer()->volume->send(value);
        emit (updateItems());
    }
}

void Gui::DatabaseTabs::QVolumeTableTab::addProcess(QVolumeProduct &value)
{
    bool result = m_netManager->DatabaseCommands()->volume->add(value);
    if (result) {
        m_netManager->CommandsToServer()->volume->send(value);
        // Обновляем все айтемы на экране
        emit (updateItems());
    }
}

QVector<QVariant> Gui::DatabaseTabs::QVolumeTableTab::getSalesObjectVector()
{
    QVector<QVolumeProduct> volumes = m_netManager->DatabaseCommands()->volume->getVolumes();

    QVector<QVariant> output;
    for(auto volume : volumes) {
        output.push_back(QVariant::fromValue(volume));
    }
    return output;
}

void Gui::DatabaseTabs::QVolumeTableTab::processingAddItemsToTable(int row, const QVariant &value)
{
    QVolumeProduct volume = unpack<QVolumeProduct>(value);

    auto *itemName = createItem(volume.name, volume.id);
    setItemToTable(row, 0, itemName);

    auto *itemVolume = createItem(QString::number(volume.volume), volume.id);
    setItemToTable(row, 1, itemVolume);

    auto *itemDescription = createItem(volume.description, volume.id);
    setItemToTable(row, 2, itemDescription);

    auto *itemUnit = createItem(volume.units, volume.id);
    setItemToTable(row, 3, itemUnit);
}

void Gui::DatabaseTabs::QVolumeTableTab::slotEditItem(int ID)
{
    QVolumeProduct value = m_netManager->DatabaseCommands()->volume->get(ID);

    bool ok = false;
    QVolumeProduct output = QVolumeEditDialog::show(value,
                                                m_netManager->DatabaseCommands(),
                                                &ok,
                                                this);
    if (ok) {
        this->editProcess(output);
    }
}

void Gui::DatabaseTabs::QVolumeTableTab::slotAddItem()
{
    bool ok = false;
    QVolumeProduct value = QVolumeEditDialog::show(m_netManager->DatabaseCommands(),
                                                       &ok,
                                                       this);
    if (ok) {
        this->addProcess(value);
    }
}
