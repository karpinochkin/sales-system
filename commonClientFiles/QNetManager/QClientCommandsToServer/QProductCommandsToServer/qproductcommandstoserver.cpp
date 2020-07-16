#include "qproductcommandstoserver.h"

QProductCommandsToServer::QProductCommandsToServer(QObject *parent)
    : CommandsToServer::QParentCommandsToServer(parent)
{

}

void QProductCommandsToServer::loadAll()
{
    QByteArray Output;
    QDataStream stream(&Output,QIODevice::WriteOnly);

    stream << 0x01;

    emit(signalSendCommand(Output, 0x12, false));
}

void QProductCommandsToServer::load(const QVector<int> &idProducts)
{
    QByteArray Output;
    QDataStream stream(&Output,QIODevice::WriteOnly);

    stream << static_cast<quint16>(idProducts.size());

    for (auto i : idProducts) {
        stream << i;
    }

    emit (signalSendCommand(Output, 0x03, false));
}

void QProductCommandsToServer::send(QProduct &product,
                                    quint32 operation)
{
    QByteArray Output;
    QDataStream stream(&Output, QIODevice::WriteOnly);
    stream << operation;
    product >> stream;

    emit(signalSendCommand(Output, 0xA0, true));
}
