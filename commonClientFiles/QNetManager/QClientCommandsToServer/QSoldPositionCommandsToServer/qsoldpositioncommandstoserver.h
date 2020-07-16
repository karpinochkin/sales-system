#ifndef QSOLDPOSITIONCOMMANDSTOSERVER_H
#define QSOLDPOSITIONCOMMANDSTOSERVER_H

#include "../QParentCommandsToServer/qparentcommandstoserver.h"
#include "../commonFiles/SalesSystem/QReceipt/qreceipt.h"
#include <QDate>

class QSoldPositionCommandsToServer : public CommandsToServer::QParentCommandsToServer
{
    Q_OBJECT
public:
    explicit QSoldPositionCommandsToServer(QObject *parent = nullptr);
    ~QSoldPositionCommandsToServer() = default;

    void loadAll();
    void load(QVector<QReceipt> receipts);
    void load(QDate startDate, QDate endDate);
};

#endif // QSOLDPOSITIONCOMMANDSTOSERVER_H
