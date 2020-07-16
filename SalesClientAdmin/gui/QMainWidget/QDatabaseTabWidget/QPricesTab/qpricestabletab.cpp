#include "qpricestabletab.h"

Gui::DatabaseTabs::QPricesTableTab::QPricesTableTab(QNetManager *networkManager,
                                                    const Gui::DatabaseTabs::PricesTab::
                                                    Product &product,
                                                    QWidget *parent)
    : AbstractTableTab::QAbstractTableTab(AbstractTableTab::ColumnsSettings {
                                          6, {tr("Цена"),
                                          tr("Дата"),
                                          tr("Описание"),
                                          tr("Товар"),
                                          tr("Величина"),
                                          tr("Категория")}
                                          },
                                          parent),
      m_netManager(networkManager),
      product(product)
{
    this->setWindowModality(Qt::WindowModality::WindowModal);
    this->setWindowFlags(Qt::Dialog |  Qt::WindowTitleHint);
    this->setMinimumSize(parentWidget()->size() / 2);
    this->setMaximumSize(parentWidget()->size() / 1.3);
    this->resize(this->maximumSize());
    connects();
}

Gui::DatabaseTabs::QPricesTableTab::QPricesTableTab(QNetManager *networkManager,
                                                    QWidget *parent)
    : AbstractTableTab::QAbstractTableTab(AbstractTableTab::ColumnsSettings {
                                          6, {tr("Цена"),
                                          tr("Дата"),
                                          tr("Описание"),
                                          tr("Товар"),
                                          tr("Величина"),
                                          tr("Категория")}
                                          },
                                          parent),
      m_netManager(networkManager)
{
    connects();
}

void Gui::DatabaseTabs::QPricesTableTab::connects()
{
    connect(m_netManager, &QNetManager::signalPricesLoaded,
            this, &QAbstractTableTab::updateItems);
    connect(m_netManager, &QNetManager::signalPriceSent,
            this, &QAbstractTableTab::updateItems);
    connect(this, &QAbstractTableTab::editItem,
            this, &QPricesTableTab::slotEditItem);
    connect(this, &QAbstractTableTab::addItem,
            this, &QPricesTableTab::slotAddItem);
    emit (updateItems());
}

void Gui::DatabaseTabs::QPricesTableTab::editProcess(QPrice &value)
{
    // Добавляем изменение в локальную бд
    bool result = m_netManager->DatabaseCommands()->price->edit(value);
    if (result) {
        // Отправляем изменения на сервер
        m_netManager->CommandsToServer()->price->send(value);
        emit (updateItems());
    }
}

void Gui::DatabaseTabs::QPricesTableTab::addProcess(QPrice &value)
{
    bool result = m_netManager->DatabaseCommands()->price->add(value);
    if (result) {
        m_netManager->CommandsToServer()->price->send(value);
        // Обновляем все айтемы на экране
        emit (updateItems());
    }
}

void Gui::DatabaseTabs::QPricesTableTab::selectedPricesUpdate()
{
    emit (updateItems());
}

void Gui::DatabaseTabs::QPricesTableTab::allPricesUpdate()
{
    emit (updateItems());
}

QVector<QVariant> Gui::DatabaseTabs::QPricesTableTab::getSalesObjectVector()
{
    QVector<QPrice> prices = m_netManager->DatabaseCommands()->price->getPrices();

    QVector<QVariant> output;
    for(auto price : prices) {
        output.push_back(QVariant::fromValue(price));
    }
    return output;
}

void Gui::DatabaseTabs::QPricesTableTab::processingAddItemsToTable(int row, const QVariant &value)
{
    QPrice price = unpack<QPrice>(value);
    auto *itemValue = createItem(QString::number(price.value), price.id);
    setItemToTable(row, 0, itemValue);

    auto *itemDate = createItem(price.startDate.toString("yyyy-mm-dd hh:mm:ss"), price.id);
    setItemToTable(row, 1, itemDate);

    auto *itemDescription = createItem(price.description, price.id);
    setItemToTable(row, 2, itemDescription);

    QProduct product = m_netManager->DatabaseCommands()->product->get(price.idProduct);
    auto *itemProduct = createItem(product.name, price.id);
    setItemToTable(row, 3, itemProduct);

    QVolumeProduct volume = m_netManager->DatabaseCommands()->volume->get(price.idVolume);
    auto *itemVolume = createItem(volume.description, price.id);
    setItemToTable(row, 4, itemVolume);

    QSalesCategory category = m_netManager->DatabaseCommands()->category->get(price.idProductCategory);
    auto *itemCategory = createItem(category.name, price.id);
    setItemToTable(row, 5, itemCategory);
}

void Gui::DatabaseTabs::QPricesTableTab::closeEvent(QCloseEvent *)
{
    emit (this->signalClose());
    this->deleteLater();
}

void Gui::DatabaseTabs::QPricesTableTab::slotEditItem(int ID)
{
    QPrice price = m_netManager->DatabaseCommands()->price->get(ID);

    bool ok = false;
    QPrice output;

    if (product.id < 0) {
        output = QPricesEditDialog::show(price,
                                         m_netManager->DatabaseCommands(),
                                         &ok,
                                         this);
    }
    else {
        output = QPricesEditForProductDialog::show(price,
                                                   m_netManager->DatabaseCommands(),
                                                   product,
                                                   &ok,
                                                   this);
    }

    if (ok) {
        this->editProcess(output);
    }
}

void Gui::DatabaseTabs::QPricesTableTab::slotAddItem()
{
    bool ok = false;
    QPrice price;

    if (product.id < 0) {
        price = QPricesEditDialog::show(m_netManager->DatabaseCommands(),
                                        &ok,
                                        this);
    }
    else {
        price = QPricesEditForProductDialog::show(m_netManager->DatabaseCommands(),
                                                  product,
                                                  &ok,
                                                  this);
    }

    if (ok) {
        this->addProcess(price);
    }
}
