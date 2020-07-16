#include "qpointsaletabletab.h"

Gui::DatabaseTabs::QPointSaleTableTab::QPointSaleTableTab(QNetManager *networkManager,
                                                          QWidget *parent)
    : AbstractTableTab::QAbstractTableTab(AbstractTableTab::ColumnsSettings {
                                          1, {tr("Название")}
                                          },
                                          parent),
      m_netManager(networkManager)
{
    //    connect(m_networkManager, &QNetManager::signalRemovePointSale,
    //            this, &QPointSaleTab::slotRemoveAnswer);
    connect(m_netManager, &QNetManager::signalPointSaleInformationLoaded,
            this, &QAbstractTableTab::updateItems);
    connect(this, &QAbstractTableTab::editItem,
            this, &QPointSaleTableTab::slotEditItem);
    connect(this, &QAbstractTableTab::addItem,
            this, &QPointSaleTableTab::slotAddItem);
    emit (updateItems());
}

void Gui::DatabaseTabs::QPointSaleTableTab::editProcess(QPointSale &value)
{
    // Добавляем изменение в локальную бд
    bool result = m_netManager->DatabaseCommands()->pointSale->edit(value);
    if (result) {
        // Отправляем изменения на сервер
        m_netManager->CommandsToServer()->pointSale->send(value);

        emit (updateItems());
    }
}

void Gui::DatabaseTabs::QPointSaleTableTab::addProcess(QPointSale &value)
{
    bool result = m_netManager->DatabaseCommands()->pointSale->add(value);
    if (result) {
        m_netManager->CommandsToServer()->pointSale->send(value);

        emit (updateItems());
    }
}

QVector<QVariant> Gui::DatabaseTabs::QPointSaleTableTab::getSalesObjectVector()
{
    QVector<QPointSale> pointSales = m_netManager->DatabaseCommands()->pointSale->getPointSales();

    QVector<QVariant> output;
    for(auto pointSale : pointSales) {
        output.push_back(QVariant::fromValue(pointSale));
    }
    return output;
}

void Gui::DatabaseTabs::QPointSaleTableTab::processingAddItemsToTable(int row, const QVariant &val)
{
    QPointSale pointSale = unpack<QPointSale>(val);
    auto *itemName = createItem(pointSale.name, pointSale.id);
    setItemToTable(row, 0, itemName);
}

void Gui::DatabaseTabs::QPointSaleTableTab::slotEditItem(int ID)
{
    QPointSale pointSale = m_netManager->DatabaseCommands()->pointSale->get(ID);

    bool ok = false;
    QPointSale output = QPointSaleEditDialog::show(pointSale,
                                                   m_netManager->DatabaseCommands(),
                                                   &ok,
                                                   this);
    if (ok) {
        this->editProcess(output);
    }
}

void Gui::DatabaseTabs::QPointSaleTableTab::slotAddItem()
{
    bool ok = false;
    QPointSale pointSale = QPointSaleEditDialog::show(m_netManager->DatabaseCommands(),
                                                      &ok,
                                                      this);
    if (ok) {
        this->addProcess(pointSale);
    }
}
