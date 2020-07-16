#ifndef QPRICECOMMANDSTOSERVER_H
#define QPRICECOMMANDSTOSERVER_H

#include "../QParentCommandsToServer/qparentcommandstoserver.h"
#include "../commonFiles/SalesSystem/QPrice/qprice.h"

class QPriceCommandsToServer : public CommandsToServer::QParentCommandsToServer
{
    Q_OBJECT
public:
    explicit QPriceCommandsToServer(QObject *parent = nullptr);
    ~QPriceCommandsToServer() = default;

    void load(int pointSaleID);
    void loadAll();
    void send(QPrice &price);
};

#endif // QPRICECOMMANDSTOSERVER_H
