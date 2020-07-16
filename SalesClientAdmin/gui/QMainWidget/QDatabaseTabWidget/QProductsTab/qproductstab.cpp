#include "qproductstab.h"

using namespace Gui::DatabaseTabs;

QProductsTab::QProductsTab(QNetManager *networkManager, QWidget *parent)
: QAbstractTab(networkManager, parent)
{
    this->slotUpdateItems();
    connect(m_networkManager, &QNetManager::signalProductsLoaded,
            this, &QProductsTab::slotUpdateItems);
//    connect(m_networkManager, &QNetManager::signalRemoveProduct,
//            this, &QProductsTab::slotRemoveAnswer);
}

DatabaseCommands::QProductCommands *QProductsTab::getDatabaseProductCommands() const
{
    return m_networkManager->DatabaseCommands()->product;
}

DatabaseCommands::QProductPictureCommands *QProductsTab::getDatabasePictureCommands() const
{
    return m_networkManager->DatabaseCommands()->picture;
}

AbstractTab::QAbstractWidgetListItem *QProductsTab::createOwnItem(const QSalesObjects &object)
{
    int idPicture = static_cast<const QProduct&>(object).idPicture;

    QProductPicture picture;
    picture = this->getDatabasePictureCommands()->get(idPicture);

    return  new QProductsWidgetListItem(static_cast<const QProduct&>(object),
                                        picture.data,
                                    m_listWidget);
}

void QProductsTab::removeFromLocalDatabase(int id, const QString &name)
{
    Q_UNUSED(id)
    Q_UNUSED(name)
//    this->getDatabaseProductCommands()->remove(id, name);
}

QString QProductsTab::getCurrentItemName()
{
    QString output = dynamic_cast<QProductsWidgetListItem*>(currentItem)->getItemName();

    return output;
}
void QProductsTab::updateItemOnDisplay(const QProduct &product)
{
    for (int i = 0; i < m_listWidget->count(); i++) {
         currentItem = dynamic_cast<QProductsWidgetListItem*>
                (m_listWidget->itemWidget(m_listWidget->item(i)));

         QProduct currentProduct = reinterpret_cast<QProductsWidgetListItem*>(currentItem)->getProduct();

        if (currentProduct.id == product.id) {
            QProductPicture picture;
            picture = this->getDatabasePictureCommands()->get(product.idPicture);
            reinterpret_cast<QProductsWidgetListItem*>(currentItem)->setInformation(product,
                                                                                    picture.data);

            break;
        }
    }
}

void QProductsTab::addProcess(QProduct &product)
{
    bool result = m_networkManager->DatabaseCommands()->product->add(product);
    if (result) {
        m_networkManager->CommandsToServer()->product->send(product,
                                                            Database::Commands::ADD);
        // Обновляем все айтемы на экране
        this->slotUpdateItems();
    }
}

void QProductsTab::editProcess(QProduct &product)
{
    // Добавляем изменение в локальную бд
    bool result = m_networkManager->DatabaseCommands()->product->edit(product);
    if (result) {
        // Отправляем изменения на сервер
        m_networkManager->CommandsToServer()->product->send(product,
                                                            Database::Commands::EDIT);
        //Обновляем измененный элемент
        this->updateItemOnDisplay(product);
    }
}

void QProductsTab::shawPriceWidget(const QProduct &product)
{
    qDebug() << product.id << product.name;

    if (product.id > 0) {
        PricesTab::Product _product;

        _product.id = product.id;
        _product.name = product.name;


        QPricesTab *pricesTab = new QPricesTab(this->m_networkManager,
                                   _product,
                                   this);
        pricesTab->show();
    }
}

void QProductsTab::slotAddItem()
{
    bool ok = false;
    QProduct product = QProductsEditDialog::show(m_networkManager->DatabaseCommands(),
                                                       &ok,
                                                       this);
    if (ok) {
        this->addProcess(product);
    }
}

void QProductsTab::slotUpdateItems()
{
    m_listWidget->clear();

    QVector<QProduct> products = this->getDatabaseProductCommands()->getProducts();

    for (int i = 0; i < products.size(); i++) {
        QAbstractTab::templateCreateNewItemOnDisplay(static_cast<const QSalesObjects&>(products.at(i)));
    }
}

void QProductsTab::slotRemoveItem(int id)
{
    Q_UNUSED(id)
}

void QProductsTab::slotEditItem(QSalesObjects &object)
{
    QProduct product = static_cast<QProduct&>(object);

    bool ok = false;
    bool isShawPriceWindow = false;
    QProduct output = QProductsEditDialog::show(product,
                                                m_networkManager->DatabaseCommands(),
                                                &ok,
                                                &isShawPriceWindow,
                                                this);
    if (ok) {
        this->editProcess(output);
        if (isShawPriceWindow) {
            this->shawPriceWidget(output);
        }
    }
}
