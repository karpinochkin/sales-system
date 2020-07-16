#ifndef QRECEIPTCOMMANDSTOSERVER_H
#define QRECEIPTCOMMANDSTOSERVER_H

#include "../QParentCommandsToServer/qparentcommandstoserver.h"
#include "../commonFiles/SalesSystem/QReceipt/qreceipt.h"
#include "../commonFiles/SalesSystem/QSoldPosition/qsoldposition.h"
#include "../commonFiles/SalesSystem/QPointSale/qpointsale.h"
#include "../commonFiles/SalesSystem/QShift/qshift.h"
#include "../commonFiles/SalesSystem/QUser/quser.h"
#include <QDate>
class QReceiptCommandsToServer : public CommandsToServer::QParentCommandsToServer
{
    Q_OBJECT
public:
    explicit QReceiptCommandsToServer(QObject *parent = nullptr);
    ~QReceiptCommandsToServer() = default;

    void loadAll();
    void load(QShift &shift);
    void load(QDate startDate,
              QDate endDate);
    void sendSale(QReceipt &receipt,
                  const QVector<QSoldPosition> &soldPositions);
};

#endif // QRECEIPTCOMMANDSTOSERVER_H
