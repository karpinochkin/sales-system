#ifndef QPICTURECOMMANDSTOSERVER_H
#define QPICTURECOMMANDSTOSERVER_H

#include "../QParentCommandsToServer/qparentcommandstoserver.h"
#include "../commonFiles/SalesSystem/QProductPicture/qproductpicture.h"

class QPictureCommandsToServer : public CommandsToServer::QParentCommandsToServer
{
    Q_OBJECT
public:
    explicit QPictureCommandsToServer(QObject *parent = nullptr);
    ~QPictureCommandsToServer() override = default;

    void loadInformation(int idPicture);
    void loadAll();
    void send(QProductPicture &picture);
    void remove(int id, const QString &name);
};

#endif // QPICTURECOMMANDSTOSERVER_H
