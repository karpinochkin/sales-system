#include "qclientloader.h"

QClientLoader::QClientLoader(QObject *parent)
    : QObject (parent)
{
    qDebug()<<"Create QClientLoader";
    setObjectName("loader");

    initObjects();
}

QClientLoader::~QClientLoader()
{
    if(mainWidget != nullptr) {
        delete mainWidget;
    }
}


void QClientLoader::initObjects()
{
    currentSettings = new QSettings("Sales", "SalesAdminClient");
    this->showLoaderScreen();

}

void QClientLoader::showLoaderScreen()
{
    loaderScreen = new QLoaderScreen(currentSettings, this);

    connect(loaderScreen, &QLoaderScreen::signalConnectToServer,
            this, &QClientLoader::slotConnectToServer);

    loaderScreen->show();
}

void QClientLoader::connectSlots()
{
    connect(managerNetwork, &QNetManager::signalAuthorized,
            loaderScreen, &QLoaderScreen::slotAuthorized);
    connect(managerNetwork, &QNetManager::signalError,
            loaderScreen, &QLoaderScreen::slotError);
    connect(managerNetwork, &QNetManager::signalMessageSplashScreen,
            loaderScreen, &QLoaderScreen::slotMessageSplashScreen);
    connect(managerNetwork, &QNetManager::signalEndSynchronization,
            loaderScreen, &QLoaderScreen::slotEndSynchronization);
    connect(managerNetwork, &QNetManager::signalEndSynchronization,
            this, &QClientLoader::slotEndSynchronization);
}

void QClientLoader::slotConnectToServer()
{
    managerNetwork = new QNetManager(currentSettings, this);
    managerNetwork->setObjectName("managerNetwork");
    connectSlots();

}

void QClientLoader::slotEndSynchronization()
{
    this->showMainWidget();
}

void QClientLoader::showMainWidget()
{
    delete loaderScreen;
    mainWidget = new QMainWidget(currentSettings, managerNetwork);
    mainWidget->show();
}
