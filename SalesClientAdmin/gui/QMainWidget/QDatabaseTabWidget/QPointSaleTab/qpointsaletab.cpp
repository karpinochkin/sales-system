#include "qpointsaletab.h"

using namespace Gui::DatabaseTabs;

QPointSaleTab::QPointSaleTab(QNetManager *networkManager, QWidget *parent)
    : AbstractTab::QAbstractTab(networkManager, parent)
{
    this->slotUpdateItems();

    connect(m_networkManager, &QNetManager::signalPointSaleInformationLoaded,
            this, &QPointSaleTab::slotUpdateItems);
    connect(m_networkManager, &QNetManager::signalRemovePointSale,
            this, &QPointSaleTab::slotRemoveAnswer);
}

DatabaseCommands::QPointSaleCommands *QPointSaleTab::getDatabasePointSaleCommands() const
{
    return m_networkManager->DatabaseCommands()->pointSale;
}

AbstractTab::QAbstractWidgetListItem *QPointSaleTab::createOwnItem(const QSalesObjects &object)
{
    return  new QPointSaleWidgetListItem(static_cast<const QPointSale&>(object),
                                         m_listWidget);
}

void QPointSaleTab::removeFromLocalDatabase(int id, const QString &name)
{
    this->getDatabasePointSaleCommands()->remove(id, name);
}

QString QPointSaleTab::getCurrentItemName()
{
//    return dynamic_cast<QPointSaleWidgetListItem*>(currentItem)->getPointSale().name;
    QString output = dynamic_cast<QPointSaleWidgetListItem*>(currentItem)->getItemName();

     return output;
}

void QPointSaleTab::updateItemOnDisplay(const QPointSale &pointSale)
{
    for (int i = 0; i < m_listWidget->count(); i++) {
        currentItem = dynamic_cast<QPointSaleWidgetListItem*>
                (m_listWidget->itemWidget(m_listWidget->item(i)));

        QPointSale currentPointSale = reinterpret_cast<QPointSaleWidgetListItem*>(currentItem)->getPointSale();

        if (currentPointSale.id == pointSale.id) {
            reinterpret_cast<QPointSaleWidgetListItem*>(currentItem)->setPointSale(pointSale);

            break;
        }
    }
}

void QPointSaleTab::addProcess(QPointSale &pointSale)
{
    bool result = m_networkManager->DatabaseCommands()->pointSale->add(pointSale);
    if (result) {
        m_networkManager->CommandsToServer()->pointSale->send(pointSale);
        // Обновляем все айтемы на экране
        this->slotUpdateItems();
    }
}

void QPointSaleTab::editProcess(QPointSale &pointSale)
{
    // Добавляем изменение в локальную бд
    bool result = m_networkManager->DatabaseCommands()->pointSale->edit(pointSale);
    if (result) {
        // Отправляем изменения на сервер
        m_networkManager->CommandsToServer()->pointSale->send(pointSale);
        //Обновляем измененный элемент
        this->updateItemOnDisplay(pointSale);
    }
}

void QPointSaleTab::slotAddItem()
{
    bool ok = false;
    QPointSale pointSale = QPointSaleEditDialog::show(m_networkManager->DatabaseCommands(),
                                                      &ok,
                                                      this);
    if (ok) {
        this->addProcess(pointSale);
    }
}

void QPointSaleTab::slotUpdateItems()
{
    m_listWidget->clear();

    QVector<QPointSale> pointSales = this->getDatabasePointSaleCommands()->getPointSales();

    for (int i = 0; i < pointSales.size(); i++) {
        QAbstractTab::templateCreateNewItemOnDisplay(static_cast<const QSalesObjects&>(pointSales.at(i)));
    }
}

void QPointSaleTab::slotRemoveItem(int id)
{
    if (m_networkManager->isAuthorized()) {
        QPointSale pointSale = getDatabasePointSaleCommands()->get(id);
        m_networkManager->CommandsToServer()->pointSale->remove(pointSale.id,
                                                                pointSale.name);
    }
    else {
        QMessageBox::critical(this,
                              tr("Ошибка"),
                              tr("Точка продаж не может быть удалена. Нет соединения с сервером. Попробуйте позже."));
    }
}

void QPointSaleTab::slotEditItem(QSalesObjects &object)
{
    QPointSale pointSale = static_cast<QPointSale&>(object);

    bool ok = false;
    QPointSale output = QPointSaleEditDialog::show(pointSale,
                                                   m_networkManager->DatabaseCommands(),
                                                   &ok,
                                                   this);
    if (ok) {
        this->editProcess(output);
    }
}
