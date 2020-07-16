#ifndef QLOADERWINDOW_H
#define QLOADERWINDOW_H

#include <QObject>
#include <QDebug>
#include <QSettings>
#include <gui/loader/QSalesSplashScreen/qsalessplashscreen.h>
#include <gui/loader/QHostsDialog/qhostsdialog.h>
#include <gui/loader/QAccountDialog/qaccountdialog.h>
#include <gui/loader/QDateRangeDialog/qdaterangedialog.h>
#include <QTimer>
#include <QApplication>
#include <QMessageBox>

namespace Gui::Loader {

class QLoaderScreen : public QObject
{
    Q_OBJECT
public:
    explicit QLoaderScreen(QSettings *settings, QObject *parent = nullptr);
    ~QLoaderScreen() = default;

    void show();

private:
    QSalesSplashScreen *splashScreen = nullptr;
    QSettings *settings = nullptr;
    QTimer *connectionTimer = nullptr;

    HostInfo host;
    UserAccount account;
    DateRange dateRange;

    void showSplashScreen();
    void setSplashMessage(QString);
    void hideSplashScreen();
    void connects();

    void saveSettings();
    void loadSettings();
    void loadingProccess();
    void close();
    void connectToServer();

    HostInfo getServer();
    UserAccount getAccount();
    DateRange getDateRange();

public slots:
    void slotAuthorized();
    void slotError(QString);

    void slotMessageSplashScreen(QString);
    void slotBeginSynchronization();
    void slotEndSynchronization();

private slots:
    void slotTimeout();

signals:
    void signalConnectToServer();
};

}

#endif // QLOADERWINDOW_H
