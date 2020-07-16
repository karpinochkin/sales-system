#ifndef QUSERCOMMANDSTOSERVER_H
#define QUSERCOMMANDSTOSERVER_H

#include "../QParentCommandsToServer/qparentcommandstoserver.h"
#include "../commonFiles/SalesSystem/QUser/quser.h"

class QUserCommandsToServer : public CommandsToServer::QParentCommandsToServer
{
    Q_OBJECT
public:
    explicit QUserCommandsToServer(QObject *parent = nullptr);
    ~QUserCommandsToServer() = default;

    void loadInformation();
    void remove(int id, const QString &name);
    void send(QUser &value);
    void loadAll();
};

#endif // QUSERCOMMANDSTOSERVER_H
