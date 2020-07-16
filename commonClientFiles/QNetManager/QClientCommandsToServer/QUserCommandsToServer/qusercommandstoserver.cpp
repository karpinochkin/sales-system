#include "qusercommandstoserver.h"

QUserCommandsToServer::QUserCommandsToServer(QObject *parent)
    : CommandsToServer::QParentCommandsToServer(parent)
{

}

void QUserCommandsToServer::loadInformation()
{
    QByteArray Output;
    QDataStream stream(&Output,QIODevice::WriteOnly);

    stream<<0x01;
    emit (this->signalSendCommand(Output, 0x07, false));
}

void QUserCommandsToServer::remove(int id, const QString &name)
{
    QByteArray Output = getRemoveData(id, name);

    emit (signalSendCommand(Output, 0xB7, true));
}

void QUserCommandsToServer::send(QUser &value)
{
    QByteArray Output;
    QDataStream stream(&Output, QIODevice::WriteOnly);
    value >> stream;

    emit (signalSendCommand(Output, 0xB8, true));
}

void QUserCommandsToServer::loadAll()
{
    QByteArray Output;
    QDataStream stream(&Output, QIODevice::WriteOnly);

    stream<<0x01;

    emit (signalSendCommand(Output, 0xB9, false));
}
