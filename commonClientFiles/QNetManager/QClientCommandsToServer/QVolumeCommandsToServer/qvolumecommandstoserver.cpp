#include "qvolumecommandstoserver.h"

QVolumeCommandsToServer::QVolumeCommandsToServer(QObject *parent)
    : CommandsToServer::QParentCommandsToServer(parent)
{

}

void QVolumeCommandsToServer::loadVolumes(QVector<int> idProducts)
{
    QByteArray Output;
    QDataStream stream(&Output,QIODevice::WriteOnly);
    stream << static_cast<quint16>(idProducts.length());
    for (int i = 0; i < idProducts.length(); i++) {
        stream << idProducts.at(i);
    }
    emit (this->signalSendCommand(Output, 0x04, false));
}

void QVolumeCommandsToServer::remove(int id, const QString &name)
{
    QByteArray Output = getRemoveData(id, name);

    emit (signalSendCommand(Output, 0xB5, true));
}

void QVolumeCommandsToServer::send(QVolumeProduct &value)
{
    QByteArray Output;
    QDataStream stream(&Output, QIODevice::WriteOnly);
    value >> stream;

    emit (signalSendCommand(Output, 0xB6, true));
}
