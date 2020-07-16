#ifndef MIDDLEWAREQML_H
#define MIDDLEWAREQML_H

#include <QObject>
#include <QQmlPropertyMap>
#include <QMessageBox>
#include <QVector>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlRecord>
#include <QGuiApplication>
#include "../commonClientFiles/QNetManager/qnetmanager.h"
#include "productimageprovider.h"

//
class MiddlewareQML : public QObject
{
    Q_OBJECT
public:
    explicit MiddlewareQML(QObject *parent = nullptr);
    ~MiddlewareQML() override = default;

    ProductImageProvider *productImageProvider = nullptr;
    QQmlPropertyMap *qmlProperty;

private:
    QNetManager *netManager = nullptr;
    QSettings *settings = nullptr;
    QVector<HostInfo> vectorForSaveHosts;

public slots:
    void saveIdPointSaleInSettings();
    void getIdPointSaleFromSettings();
    void saveLoginInSettings();
    void getLoginFromSettings();
    void saveHostPortInMiddleware();
    void saveHostPortInSettings();
    void fillHostPortFromSetings();

    bool isAndroid();
    void getImage(int);
    void getWarnings(const QList<QQmlError> &);

    void fillCategoryTabs();
    void fillProducts(int);
    void fillVolumes(int);
    void fillPaymentTypes();
    void fillReceipts();
    void fillSoldPositions(int);
    void createReceipt(int);
    bool getPrice(int idCategory,
                  int idProduct,
                  int idVolume);

    void connectToHost();
    void disconnectFromHost();
    void exitApp();

    void authorized();
    void error (UnErr err);
    void endSynchronization();

signals:
    void signalCategoryTabsCreate();
    void signalProductsListCreate();
    void signalVolumesListCreate();
    void signalPaymentTypesListCreate();
    void signalReceiptsCreate();
    void signalSoldPositionsCreate();
    void signalHostPortCreate();

    void signalFillSomePropertyInReportView();
    void signalGetSomePropertyForSoldPosition(int index);

    void signalSendImage(QImage);
    void signalBadAuthorized();
    void signalGoodAuthorized();
    void signalMessageSplashScreen(QString message);
    void signalFillOpenDate();
    void signalFinishCreateTabs();

    void signalPortInvalid();
};

#endif // MIDDLEWAREQML_H
