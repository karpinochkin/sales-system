#include "qpointsalecommandstoserver.h"

QPointSaleCommandsToServer::QPointSaleCommandsToServer(QObject *parent)
    : CommandsToServer::QParentCommandsToServer(parent)
{

}

void QPointSaleCommandsToServer::loadInformation(int idPointSale)
{
    QByteArray buf;

    QDataStream stream(&buf,QIODevice::WriteOnly);
    stream<<idPointSale;

    emit(signalSendCommand(buf, 0x01, false));
}

void QPointSaleCommandsToServer::loadAll_0x0F()
{
    QByteArray buf;

    QDataStream stream(&buf,QIODevice::WriteOnly);
    stream << 0x01;

    emit(signalSendCommand(buf, 0x0F, false));
}

void QPointSaleCommandsToServer::loadAll_0xB0()
{
    QByteArray buf;

    QDataStream stream(&buf,QIODevice::WriteOnly);

    emit(signalSendCommand(buf, 0xB0, false));
}

void QPointSaleCommandsToServer::loadInformation_0x10(int idPointSale)
{
    QByteArray buf;

    QDataStream stream(&buf,QIODevice::WriteOnly);
    stream << idPointSale;

    emit(signalSendCommand(buf, 0x10, false));
}

void QPointSaleCommandsToServer::send(QPointSale &pointSale)
{
    QByteArray Output;
    QDataStream stream(&Output, QIODevice::WriteOnly);
    stream << pointSale.toByteArray();

    emit (signalSendCommand(Output, 0xC1, true));
}

void QPointSaleCommandsToServer::remove(int id, const QString &name)
{
    QByteArray Output = getRemoveData(id, name);

    emit (signalSendCommand(Output, 0xC2, true));
}
