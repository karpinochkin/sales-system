#ifndef QPOINTSALECOMMANDSTOSERVER_H
#define QPOINTSALECOMMANDSTOSERVER_H

#include "../QParentCommandsToServer/qparentcommandstoserver.h"
#include "../commonFiles/SalesSystem/QPointSale/qpointsale.h"
class QPointSaleCommandsToServer : public CommandsToServer::QParentCommandsToServer
{
    Q_OBJECT
public:
    QPointSaleCommandsToServer(QObject *parent = nullptr);
    ~QPointSaleCommandsToServer() = default;

    void loadInformation(int idPointSale);
    void loadAll_0x0F();
    void loadAll_0xB0(); // Замена варианту loadAll_0x0F
    void loadInformation_0x10(int idPointSale);
    void send(QPointSale &pointSale);
    void remove(int id, const QString &name);
};

#endif // QPOINTSALECOMMANDSTOSERVER_H
