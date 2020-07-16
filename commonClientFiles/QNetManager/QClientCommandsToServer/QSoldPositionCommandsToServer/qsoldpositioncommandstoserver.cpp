#include "qsoldpositioncommandstoserver.h"

QSoldPositionCommandsToServer::QSoldPositionCommandsToServer(QObject *parent)
    : CommandsToServer::QParentCommandsToServer(parent)
{

}

void QSoldPositionCommandsToServer::loadAll()
{
    QByteArray Output;
    QDataStream stream(&Output,QIODevice::WriteOnly);

    stream<<0x01;
    emit (this->signalSendCommand(Output, 0x16, false));
}

void QSoldPositionCommandsToServer::load(QVector<QReceipt> receipts)
{
    QByteArray Output;
    QDataStream stream(&Output,QIODevice::WriteOnly);

    stream << static_cast<quint16>(receipts.size());

    for (auto i : receipts) {
        stream << i.id;
    }

    emit (signalSendCommand(Output, 0x0B, false));
}

void QSoldPositionCommandsToServer::load(QDate startDate, QDate endDate)
{
    QByteArray Output;
    QDataStream stream(&Output,QIODevice::WriteOnly);

    stream << startDate;
    stream << endDate;

    emit (this->signalSendCommand(Output, 0xC7, false));
}
