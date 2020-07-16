#ifndef QTYPECOMMANDSTOSERVER_H
#define QTYPECOMMANDSTOSERVER_H

#include "../commonFiles/SalesSystem/QPaymentType/qpaymenttype.h"
#include "../QParentCommandsToServer/qparentcommandstoserver.h"

class QTypeCommandsToServer : public CommandsToServer::QParentCommandsToServer
{
    Q_OBJECT
public:
    explicit QTypeCommandsToServer(QObject *parent = nullptr);
    ~QTypeCommandsToServer() override = default;

    void loadAll();
    void remove(int id, const QString &name);
    void send(QPaymentType &type);
};

#endif // QTYPECOMMANDSTOSERVER_H

