#ifndef QCLIENTLOADER_H
#define QCLIENTLOADER_H

#include <QObject>
#include <QSettings>
#include <QDebug>
#include "../commonClientFiles/QNetManager/qnetmanager.h"
#include "../../gui/loader/QLoaderScreen/qloaderscreen.h"
#include "../../gui/QMainWidget/qmainwidget.h"

using namespace Gui::Loader;
using namespace Gui;

class QClientLoader : public QObject
{
    Q_OBJECT
public:
    explicit QClientLoader(QObject *parent = nullptr);
    ~QClientLoader();

private:
    QSettings *currentSettings = nullptr;
    QNetManager *managerNetwork = nullptr;
    QLoaderScreen *loaderScreen = nullptr;
    QMainWidget *mainWidget = nullptr;

    void initObjects();
    void connectSlots();
    void showLoaderScreen();
    void showMainWidget();

private slots:
    void slotConnectToServer();
    void slotEndSynchronization();
};
#endif // QCLIENTLOADER_H
