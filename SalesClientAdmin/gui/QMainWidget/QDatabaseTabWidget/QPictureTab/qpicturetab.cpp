#include "qpicturetab.h"

using namespace Gui::DatabaseTabs;

QPictureTab::QPictureTab(QNetManager *netManager, QWidget *parent)
    : QAbstractTab(netManager, parent)
{
    this->slotUpdateItems();

    updateButton = new QPushButton(tr("Обновить с сервера"), this);
    updateButton->setMaximumSize(150, 350);

    connect(m_networkManager, &QNetManager::signalPictureSent,
            this, &QPictureTab::slotUpdateItems);
    connect(m_networkManager, &QNetManager::signalPicturesLoaded,
            this, &QPictureTab::slotUpdateItems);
    connect(m_networkManager, &QNetManager::signalPicturesLoaded,
            this, [=]() {updateButton->setEnabled(true);});
    connect(m_networkManager, &QNetManager::signalRemovePicture,
            this, &QPictureTab::slotRemoveAnswer);
    connect(updateButton, &QPushButton::clicked,
            this, &QPictureTab::slotUpdateFromServer);

    this->addWidgetToMainLayout(updateButton);
}

DatabaseCommands::QProductPictureCommands *QPictureTab::getDatabasePictureCommands() const
{
    return m_networkManager->DatabaseCommands()->picture;
}

AbstractTab::QAbstractWidgetListItem *QPictureTab::createOwnItem(const QSalesObjects &object)
{
    return new QPictureWidgetListItem(static_cast<const QProductPicture&>(object),
                                      m_listWidget);
}

void QPictureTab::removeFromLocalDatabase(int id, const QString &name)
{
    this->getDatabasePictureCommands()->remove(id, name);
}

QString QPictureTab::getCurrentItemName()
{
    QString output = dynamic_cast<QPictureWidgetListItem*>(currentItem)->getItemName();

     return output;
}

void QPictureTab::slotUpdateItems()
{
    m_listWidget->clear();

    QVector<QProductPicture> pictures = this->getDatabasePictureCommands()->getPictures();

    // Создание виджетов каждого товара
    for (int i = 0; i < pictures.size(); i++) {
        QAbstractTab::templateCreateNewItemOnDisplay(static_cast<const QSalesObjects&>(pictures.at(i)));
    }
}

void QPictureTab::slotUpdateFromServer()
{
    if (m_networkManager->isAuthorized()) {
        updateButton->setEnabled(false);
        m_networkManager->CommandsToServer()->picture->loadAll();
    }
    else {
        QMessageBox::critical(this,
                              tr("Ошибка"),
                              tr("Нет соединения с сервером. Попробуйте позже..."));
    }
}

void QPictureTab::slotRemoveItem(int id)
{
    qDebug() << "remove picture: " << id;
    if (m_networkManager->isAuthorized()) {
        QProductPicture picture = getDatabasePictureCommands()->get(id);
        qDebug() << id << picture.id << picture.name;
        m_networkManager->CommandsToServer()->picture->remove(picture.id, picture.name);
    }
    else {
        QMessageBox::critical(this,
                              tr("Ошибка"),
                              tr("Изображение не может быть удалено. Нет соединения с сервером. Попробуйте позже."));
    }
}

void QPictureTab::slotAddItem()
{
    bool ok = false;
    QProductPicture picture = QPictureEditDialog::show(m_networkManager->DatabaseCommands(),
                                                       &ok,
                                                       this);
    if (ok) {
        m_networkManager->CommandsToServer()->picture->send(picture);
    }
}

void QPictureTab::slotEditItem(QSalesObjects &object)
{
    QProductPicture picture = static_cast<QProductPicture&>(object);

    bool ok = false;
    QProductPicture output = QPictureEditDialog::show(picture,
                                                      m_networkManager->DatabaseCommands(),
                                                      &ok,
                                                      this);
    if (ok) {
        m_networkManager->CommandsToServer()->picture->send(output);
    }
}
