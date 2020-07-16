#include "qshiftcommandstoserver.h"

QShiftCommandsToServer::QShiftCommandsToServer(QObject *parent)
    : CommandsToServer::QParentCommandsToServer(parent)
{

}

void QShiftCommandsToServer::loadAll()
{
    QByteArray Output;
    QDataStream stream(&Output,QIODevice::WriteOnly);

    stream<<0x01;
    emit (this->signalSendCommand(Output, 0x14, false));
}

void QShiftCommandsToServer::close(QShift &shift)
{
    QByteArray Output;
    QDataStream stream(&Output,QIODevice::WriteOnly);

    shift >> stream;

    emit (signalSendCommand(Output, 0x09, false));
}

void QShiftCommandsToServer::open(int pointSaleID)
{
    QByteArray Output;
    QDataStream stream(&Output,QIODevice::WriteOnly);

    stream << pointSaleID;

    emit (signalSendCommand(Output, 0x08, false));
}
