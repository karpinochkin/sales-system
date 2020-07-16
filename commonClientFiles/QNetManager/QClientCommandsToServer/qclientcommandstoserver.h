#ifndef QCLIENTCOMMANDSTOSERVER_H
#define QCLIENTCOMMANDSTOSERVER_H

#include "QPointSaleCommandsToServer/qpointsalecommandstoserver.h"
#include "QCategoryCommandsToServer/qcategorycommandstoserver.h"
#include "QProductCommandsToServer/qproductcommandstoserver.h"
#include "QPriceCommandsToServer/qpricecommandstoserver.h"
#include "QVolumeCommandsToServer/qvolumecommandstoserver.h"
#include "QTypeCommandsToServer/qtypecommandstoserver.h"
#include "QUserCommandsToServer/qusercommandstoserver.h"
#include "QShiftCommandsToServer/qshiftcommandstoserver.h"
#include "QReceiptCommandsToServer/qreceiptcommandstoserver.h"
#include "QSoldPositionCommandsToServer/qsoldpositioncommandstoserver.h"
#include "QPictureCommandsToServer/qpicturecommandstoserver.h"
#include "QStatisticsCommandsToServer/qstatisticscommandstoserver.h"

class QClientCommandsToServer : public QObject
{
    Q_OBJECT
public:
    explicit QClientCommandsToServer(QObject *parent = nullptr);
    ~QClientCommandsToServer() = default;
    void getHandshake();
    void endSynchronization();

    QPointSaleCommandsToServer *pointSale = nullptr;
    QCategoryCommandsToServer *category = nullptr;
    QProductCommandsToServer *product = nullptr;
    QPriceCommandsToServer *price = nullptr;
    QVolumeCommandsToServer *volume = nullptr;
    QTypeCommandsToServer *type = nullptr;
    QUserCommandsToServer *user = nullptr;
    QShiftCommandsToServer *shift = nullptr;
    QReceiptCommandsToServer *receipt = nullptr;
    QSoldPositionCommandsToServer *soldPosition = nullptr;
    QStatisticsCommandsToServer *statistics = nullptr;
    QPictureCommandsToServer *picture = nullptr;

private:
    void createObjects();
    void connects();

signals:
    void signalSendCommand(QByteArray &data, int command_code, bool save);
};

#endif // QCLIENTCOMMANDSTOSERVER_H
