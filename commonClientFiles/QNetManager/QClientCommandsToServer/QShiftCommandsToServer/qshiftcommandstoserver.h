#ifndef QSHIFTCOMMANDSTOSERVER_H
#define QSHIFTCOMMANDSTOSERVER_H

#include "../QParentCommandsToServer/qparentcommandstoserver.h"
#include "../commonFiles/SalesSystem/QShift/qshift.h"

class QShiftCommandsToServer : public CommandsToServer::QParentCommandsToServer
{
    Q_OBJECT
public:
    explicit QShiftCommandsToServer(QObject *parent = nullptr);
    ~QShiftCommandsToServer() = default;

    void loadAll();
    void close(QShift &);
    void open(int pointSaleID);
};

#endif // QSHIFTCOMMANDSTOSERVER_H
