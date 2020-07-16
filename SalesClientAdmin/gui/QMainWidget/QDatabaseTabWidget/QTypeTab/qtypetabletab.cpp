#include "qtypetabletab.h"

using namespace Gui::DatabaseTabs;

QTypeTableTab::QTypeTableTab(QNetManager *networkManager, QWidget *parent)
    : AbstractTableTab::QAbstractTableTab(AbstractTableTab::ColumnsSettings {
                                          2, {tr("Имя"), tr("Описание")}
                                          },
                                          parent),
      m_netManager(networkManager)
{
    //    connect(m_networkManager, &QNetManager::signalRemoveType,
    //            this, &QTypeTab::slotRemoveAnswer);

    connect(m_netManager, &QNetManager::signalTypesLoaded,
            this, &QAbstractTableTab::updateItems);
    connect(this, &QTypeTableTab::editItem,
            this, &QTypeTableTab::slotEditItem);
    connect(this, &QAbstractTableTab::addItem,
            this, &QTypeTableTab::slotAddItem);
    emit (updateItems());
}

void QTypeTableTab::slotEditItem(int typeID)
{
    qDebug() << typeID;
    QPaymentType type = m_netManager->DatabaseCommands()->type->get(typeID);

    bool ok = false;
    QPaymentType output = QTypeEditDialog::show(type,
                                                m_netManager->DatabaseCommands(),
                                                &ok,
                                                this);
    if (ok) {
        this->editProcess(output);
    }
}

void QTypeTableTab::editProcess(QPaymentType &type)
{
    // Добавляем изменение в локальную бд
    bool result = m_netManager->DatabaseCommands()->type->edit(type);
    if (result) {
        // Отправляем изменения на сервер
        m_netManager->CommandsToServer()->type->send(type);
        emit (updateItems());
    }
}

void QTypeTableTab::slotAddItem()
{
    bool ok = false;
    QPaymentType type = QTypeEditDialog::show(m_netManager->DatabaseCommands(),
                                              &ok,
                                              this);
    if (ok) {
        this->addProcess(type);
    }
}

void QTypeTableTab::addProcess(QPaymentType &type)
{
    bool result = m_netManager->DatabaseCommands()->type->add(type);
    if (result) {
        m_netManager->CommandsToServer()->type->send(type);
        // Обновляем все айтемы на экране
        emit (updateItems());
    }
}

QVector<QVariant> QTypeTableTab::getSalesObjectVector()
{
    QVector<QPaymentType> types = m_netManager->DatabaseCommands()->type->getTypes();

    QVector<QVariant> output;
    for(auto type : types) {
        output.push_back(QVariant::fromValue(type));
    }
    return output;
}

void QTypeTableTab::processingAddItemsToTable(int row, const QVariant &val)
{
    QPaymentType type = unpack<QPaymentType>(val);
    auto *itemName = createItem(type.name, type.id);
    setItemToTable(row, 0, itemName);

    auto *itemDescription = createItem(type.description, type.id);
    setItemToTable(row, 1, itemDescription);
}

