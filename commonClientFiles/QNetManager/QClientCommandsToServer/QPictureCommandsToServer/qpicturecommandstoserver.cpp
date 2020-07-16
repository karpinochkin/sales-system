#include "qpicturecommandstoserver.h"

QPictureCommandsToServer::QPictureCommandsToServer(QObject *parent)
    : CommandsToServer::QParentCommandsToServer(parent)
{

}

void QPictureCommandsToServer::loadInformation(int idPicture)
{
    QByteArray Output;
    QDataStream stream(&Output,QIODevice::WriteOnly);

    stream << idPicture;
    emit (this->signalSendCommand(Output, 0x0E, false));
}

void QPictureCommandsToServer::loadAll()
{
    QByteArray Output;
    QDataStream stream(&Output,QIODevice::WriteOnly);

    emit (this->signalSendCommand(Output, 0xB1, false));
}

void QPictureCommandsToServer::send(QProductPicture &picture) {
    QByteArray Output;
    QDataStream stream(&Output, QIODevice::WriteOnly);
    picture >> stream;

    emit (signalSendCommand(Output, 0x0D, true));
}

void QPictureCommandsToServer::remove(int id, const QString &name)
{
    QByteArray Output = getRemoveData(id, name);

    emit (signalSendCommand(Output, 0xB2, true));
}
