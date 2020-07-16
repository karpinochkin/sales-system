#include "qpricestab.h"

using namespace Gui::DatabaseTabs;

QPricesTab::QPricesTab(QNetManager *networkManager,
                       const PricesTab::Product &product,
                       QWidget *parent)
    : QAbstractTab(networkManager, parent),
      product(product)
{
    qDebug() << "QPricesTab";
    this->setWindowModality(Qt::WindowModality::WindowModal);
    this->setWindowFlags(Qt::Dialog |  Qt::WindowTitleHint);
    this->setMinimumSize(parentWidget()->size() / 2);
    this->setMaximumSize(parentWidget()->size() / 1.3);
    this->resize(this->maximumSize());

    this->setGui();
}

QPricesTab::QPricesTab(QNetManager *networkManager, QWidget *parent)
    : QAbstractTab(networkManager, parent)
{
    this->setGui();
}

DatabaseCommands::QPriceCommands *QPricesTab::getDatabasePriceCommands() const
{
    return m_networkManager->DatabaseCommands()->price;
}

AbstractTab::QAbstractWidgetListItem *QPricesTab::createOwnItem(const QSalesObjects &object)
{

    QVolumeProduct volume = m_networkManager->DatabaseCommands()->volume->get(static_cast<const QPrice&>(object).idVolume);

    return  new QPricesWidgetListItem(static_cast<const QPrice&>(object),
                                      volume,
                                      m_listWidget);
}

void QPricesTab::removeFromLocalDatabase(int id, const QString &name)
{
    Q_UNUSED(id)
    Q_UNUSED(name)
}

QString QPricesTab::getCurrentItemName()
{
    QString output = dynamic_cast<QPricesWidgetListItem*>(currentItem)->getItemName();

    return output;
}

void QPricesTab::setGui()
{
    this->slotUpdateItems();
    connect(m_networkManager, &QNetManager::signalPricesLoaded,
            this, &QPricesTab::slotUpdateItems);
    connect(m_networkManager, &QNetManager::signalPriceSent,
            this, &QPricesTab::slotUpdateItems);
}

void QPricesTab::selectedPricesUpdate()
{
    m_listWidget->clear();

    QVector<QPrice> prices = this->getDatabasePriceCommands()->getPrices();
    QVector<QPrice> selectedPrices;

    for (int i = 0; i < prices.size(); i++) {
        if (product.id == prices.at(i).idProduct) {
            selectedPrices.push_back(prices.at(i));
        }
    }

    for (int i = 0; i < selectedPrices.size(); i++) {
        QAbstractTab::templateCreateNewItemOnDisplay(static_cast<const QSalesObjects&>(selectedPrices.at(i)));
    }
}

void QPricesTab::allPricesUpdate()
{
    m_listWidget->clear();

    QVector<QPrice> prices = this->getDatabasePriceCommands()->getPrices();

    for (int i = 0; i < prices.size(); i++) {
        QAbstractTab::templateCreateNewItemOnDisplay(static_cast<const QSalesObjects&>(prices.at(i)));
    }
}

void QPricesTab::updateItemOnDisplay(const QPrice &price)
{
    for (int i = 0; i < m_listWidget->count(); i++) {
        currentItem = dynamic_cast<QPricesWidgetListItem*>
                (m_listWidget->itemWidget(m_listWidget->item(i)));

        QPrice currentPrice = reinterpret_cast<QPricesWidgetListItem*>(currentItem)->getPrice();

        if (currentPrice.id == price.id) {
            reinterpret_cast<QPricesWidgetListItem*>(currentItem)->setPrice(price);

            break;
        }
    }
}

void QPricesTab::addProcess(QPrice &price)
{
    bool result = m_networkManager->DatabaseCommands()->price->add(price);
    if (result) {
        m_networkManager->CommandsToServer()->price->send(price);
        // Обновляем все айтемы на экране
        this->slotUpdateItems();
    }
}

void QPricesTab::editProcess(QPrice &price)
{
    // Добавляем изменение в локальную бд
    bool result = m_networkManager->DatabaseCommands()->price->edit(price);
    if (result) {
        // Отправляем изменения на сервер
        m_networkManager->CommandsToServer()->price->send(price);
        //Обновляем измененный элемент
        this->updateItemOnDisplay(price);
    }
}

void QPricesTab::closeEvent(QCloseEvent *)
{

    emit (this->signalClose());
    this->deleteLater();

}

void QPricesTab::slotAddItem()
{
    bool ok = false;
    QPrice price;

    if (product.id < 0) {
        price = QPricesEditDialog::show(m_networkManager->DatabaseCommands(),
                                        &ok,
                                        this);
    }
    else {
        price = QPricesEditForProductDialog::show(m_networkManager->DatabaseCommands(),
                                                  product,
                                                  &ok,
                                                  this);
    }

    if (ok) {
        this->addProcess(price);
    }
}

void QPricesTab::slotUpdateItems()
{
    if (product.id < 0) {
        this->allPricesUpdate();
    }
    else {
        this->selectedPricesUpdate();
    }
}

void QPricesTab::slotRemoveItem(int id)
{
    Q_UNUSED(id)
}

void QPricesTab::slotEditItem(QSalesObjects &object)
{
    QPrice price = static_cast<QPrice&>(object);

    bool ok = false;
    QPrice output;

    if (product.id < 0) {
        output = QPricesEditDialog::show(price,
                                         m_networkManager->DatabaseCommands(),
                                         &ok,
                                         this);
    }
    else {
        output = QPricesEditForProductDialog::show(price,
                                                   m_networkManager->DatabaseCommands(),
                                                   product,
                                                   &ok,
                                                   this);
    }

    if (ok) {
        this->editProcess(output);
    }
}
