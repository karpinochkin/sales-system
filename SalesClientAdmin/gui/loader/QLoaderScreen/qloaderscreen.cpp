#include "qloaderscreen.h"

using namespace Gui::Loader;

QLoaderScreen::QLoaderScreen(QSettings *settings, QObject *parent)
    : QObject(parent),
      settings(settings)
{

}

void QLoaderScreen::show()
{
    this->showSplashScreen();
    this->setSplashMessage(tr("Запуск программы"));

    connectionTimer = new QTimer(this);

    this->loadSettings();
    this->loadingProccess();
    this->connects();
}

void QLoaderScreen::connects()
{
    connect(connectionTimer, &QTimer::timeout,
            this, &QLoaderScreen::slotTimeout);
}

void QLoaderScreen::slotAuthorized()
{
    delete connectionTimer;
}

void QLoaderScreen::slotError(QString err)
{
    connectionTimer->stop();

    switch (err.toInt()) {

    case UnErr::errAuthBlock: {
        QMessageBox::critical(splashScreen,tr("Error"),tr("Аккаунт заблокирован"));
    }
        break;
    case UnErr::errAuthLogin: {
        QMessageBox::critical(splashScreen,tr("Error"),tr("Неправильный логин"));
    }
        break;
    case UnErr::errAuthPassword: {
        QMessageBox::critical(splashScreen,tr("Error"),tr("Неправильный пароль"));
    }
        break;
    case UnErr::errAuthServWork:
    {
        QMessageBox::critical(splashScreen,tr("Error"),tr("Технические работы на сервере"));
    }
        break;
    }

    this->close();
}

void QLoaderScreen::slotTimeout()
{
    connectionTimer->stop();
    QMessageBox::critical(splashScreen, tr("Error"), tr("Время подключения вышло"));
    this->close();
}

void QLoaderScreen::showSplashScreen()
{
    splashScreen = new QSalesSplashScreen(QPixmap(":/images/SplashScreen.jpg"));
    splashScreen->showSplashScreen();
}

void QLoaderScreen::loadSettings()
{
    account.save = settings->value("/SalesAdminClient/save").toBool();
    if (account.save) {
        account.login = settings->value("/SalesAdminClient/login").toString();
        account.password = settings->value("/SalesAdminClient/password").toString();
        host.address = settings->value("/SalesAdminClient/address").toString();
        host.port = settings->value("/SalesAdminClient/port").toInt();
    }
}

void QLoaderScreen::saveSettings()
{
    settings->setValue("/SalesAdminClient/save", account.save);
    settings->setValue("/SalesAdminClient/login", account.login);
    settings->setValue("/SalesAdminClient/password", account.password);
    settings->setValue("/SalesAdminClient/port", host.port);
    settings->setValue("/SalesAdminClient/address", host.address);
    settings->setValue("/SalesAdminClient/dateRange/startDate", dateRange.startDate);
    settings->setValue("/SalesAdminClient/dateRange/endDate", dateRange.endDate);
    settings->setValue("/SalesAdminClient/dateRange/allDates", dateRange.allDates);
}

void QLoaderScreen::loadingProccess()
{
    try {
        this->setSplashMessage(tr("Установка настроек сервера..."));
        host = this->getServer();

        this->setSplashMessage(tr("Введите логин и пароль..."));
        account = this->getAccount();

        dateRange.endDate = QDate::currentDate();
        dateRange.startDate.setDate(dateRange.endDate.year(),
                                    dateRange.endDate.month(),
                                    dateRange.endDate.day() - 1);
        dateRange.allDates = false;
    }
    catch (QString &e) {
        QMessageBox::critical(splashScreen, tr("Ошибка"), e);
        this->close();

        return;
    }

    this->setSplashMessage(tr("Подключаемся к серверу..."));
    this->saveSettings();
    this->connectToServer();
    connectionTimer->start(90000);
}

HostInfo QLoaderScreen::getServer()
{
    bool result = false;
    HostInfo output = QHostsDialog::getHost(host, &result);

    if (!result) {
        throw tr("Неправильные данные сервера");
    }

    return output;
}

UserAccount QLoaderScreen::getAccount()
{
    bool result = false;
    UserAccount output = QAccountDialog::getAccount(account, &result, splashScreen);

    if (!result) {
        throw tr("Неправильные данные аккаунта");
    }

    return output;
}

DateRange QLoaderScreen::getDateRange()
{
    bool result = false;
    DateRange output = QDateRangeDialog::getDateRange(&result,
                                            tr("Установка нужных дат"),
                                            splashScreen);

    if (!result) {
        throw tr("Вы не установили диапазон дат");
    }

    return output;
}

void QLoaderScreen::connectToServer()
{
    signalConnectToServer();
}

void QLoaderScreen::setSplashMessage(QString message)
{
    qDebug() << "splash" << message;
    splashScreen->setSplashMessage(message);
}

void QLoaderScreen::hideSplashScreen()
{
    delete splashScreen;
    splashScreen = nullptr;
}

void QLoaderScreen::close()
{
    qApp->exit();
    QTimer::singleShot(1, qApp, SLOT(quit()));
}

void QLoaderScreen::slotMessageSplashScreen(QString message)
{
    this->setSplashMessage(message);
}

void QLoaderScreen::slotBeginSynchronization()
{
    qDebug()<<"начало синхронизации";
}

void QLoaderScreen::slotEndSynchronization()
{
    qDebug()<<"окончание синхронизации";
    this->hideSplashScreen();
}
