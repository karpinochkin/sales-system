#include "qreceiptcommandstoserver.h"

QReceiptCommandsToServer::QReceiptCommandsToServer(QObject *parent)
    : CommandsToServer::QParentCommandsToServer(parent)
{

}

void QReceiptCommandsToServer::loadAll()
{
    QByteArray Output;
    QDataStream stream(&Output,QIODevice::WriteOnly);

    stream<<0x01;
    emit (this->signalSendCommand(Output, 0x15, false));
}

void QReceiptCommandsToServer::load(QShift &shift)
{
    QByteArray Output;
    QDataStream stream(&Output,QIODevice::WriteOnly);

    shift >> stream;

    emit (signalSendCommand(Output, 0x0A, false));
}

void QReceiptCommandsToServer::load(QDate startDate, QDate endDate)
{
    QByteArray Output;
    QDataStream stream(&Output,QIODevice::WriteOnly);

    stream << startDate;
    stream << endDate;

    emit (this->signalSendCommand(Output, 0xC6, false));
}

void QReceiptCommandsToServer::sendSale(QReceipt &receipt, const QVector<QSoldPosition> &soldPositions)
{
    QByteArray Output;
    QDataStream stream(&Output,QIODevice::WriteOnly);
    receipt >> stream;

//    stream << static_cast<quint16>(soldPositions.size());

    for (auto soldPos : soldPositions) {
        soldPos >> stream;
    }

    emit (signalSendCommand(Output, 0x0C, true));

}

