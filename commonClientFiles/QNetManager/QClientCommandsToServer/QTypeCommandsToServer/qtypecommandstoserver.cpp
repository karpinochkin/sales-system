#include "qtypecommandstoserver.h"

QTypeCommandsToServer::QTypeCommandsToServer(QObject *parent)
    : CommandsToServer::QParentCommandsToServer(parent)
{

}

void QTypeCommandsToServer::loadAll()
{
    QByteArray Output;
    QDataStream stream(&Output, QIODevice::WriteOnly);

    stream<<0x01;

    emit (signalSendCommand(Output, 0x05, false));
}

void QTypeCommandsToServer::remove(int id, const QString &name)
{
    QByteArray Output = getRemoveData(id, name);

    emit (signalSendCommand(Output, 0xB3, true));
}

void QTypeCommandsToServer::send(QPaymentType &type) {
    QByteArray Output;
    QDataStream stream(&Output, QIODevice::WriteOnly);
    type >> stream;

    emit (signalSendCommand(Output, 0xB4, true));
}
