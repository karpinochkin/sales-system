#ifndef QVOLUMECOMMANDSTOSERVER_H
#define QVOLUMECOMMANDSTOSERVER_H

#include "../commonFiles/SalesSystem/QVolumeProduct/qvolumeproduct.h"
#include "../QParentCommandsToServer/qparentcommandstoserver.h"

class QVolumeCommandsToServer : public CommandsToServer::QParentCommandsToServer
{
    Q_OBJECT
public:
    explicit QVolumeCommandsToServer(QObject *parent = nullptr);
    ~QVolumeCommandsToServer() = default;

    void loadVolumes(QVector<int> idProducts);
    void remove(int id, const QString &name);
    void send(QVolumeProduct &value);
};

#endif // QVOLUMECOMMANDSTOSERVER_H
