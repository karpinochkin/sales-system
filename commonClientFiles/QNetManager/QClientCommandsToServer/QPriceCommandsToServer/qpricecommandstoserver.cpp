#include "qpricecommandstoserver.h"

QPriceCommandsToServer::QPriceCommandsToServer(QObject *parent)
    : CommandsToServer::QParentCommandsToServer(parent)
{

}

void QPriceCommandsToServer::load(int pointSaleID)
{
    QByteArray Output;
    QDataStream stream(&Output,QIODevice::WriteOnly);

    stream << pointSaleID;

    emit (signalSendCommand(Output, 0x06, false));
}

void QPriceCommandsToServer::loadAll()
{
    QByteArray Output;
    QDataStream stream(&Output,QIODevice::WriteOnly);

    stream<<0x01;
    emit (this->signalSendCommand(Output, 0x13, false));
}

void QPriceCommandsToServer::send(QPrice &price)
{
    QByteArray Output;
    QDataStream stream(&Output, QIODevice::WriteOnly);
    price >> stream;

    emit (signalSendCommand(Output, 0xC5, true));
}
