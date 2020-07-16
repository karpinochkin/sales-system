#ifndef QPRODUCTCOMMANDSTOSERVER_H
#define QPRODUCTCOMMANDSTOSERVER_H

#include <../commonFiles/DatabaseEnumCommands/DatabaseEnumCommands.h>
#include <../commonFiles/SalesSystem/QProduct/qproduct.h>
#include "../QParentCommandsToServer/qparentcommandstoserver.h"

class QProductCommandsToServer : public CommandsToServer::QParentCommandsToServer
{
    Q_OBJECT
public:
    explicit QProductCommandsToServer(QObject *parent = nullptr);
    ~QProductCommandsToServer() = default;

    void send(QProduct &product, quint32 operation);
    void loadAll();
    void load(const QVector<int> &idProducts);
};

#endif // QPRODUCTCOMMANDSTOSERVER_H
