#include "qstatisticscommandstoserver.h"

QStatisticsCommandsToServer::QStatisticsCommandsToServer(QObject *parent)
    : CommandsToServer::QParentCommandsToServer(parent)
{

}

void QStatisticsCommandsToServer::load(StatisticsInput &val)
{
    QByteArray Output;
    QDataStream stream(&Output, QIODevice::WriteOnly);

    val >> stream;

    emit (signalSendCommand(Output, 0xC8, false));
}
