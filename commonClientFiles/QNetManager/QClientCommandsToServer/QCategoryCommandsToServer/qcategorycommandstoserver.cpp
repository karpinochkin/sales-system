#include "qcategorycommandstoserver.h"

QCategoryCommandsToServer::QCategoryCommandsToServer(QObject *parent)
    : CommandsToServer::QParentCommandsToServer(parent)
{

}

void QCategoryCommandsToServer::load(const QVector<int> &idCategories)
{
    QByteArray buf;
    QDataStream stream(&buf,QIODevice::WriteOnly);
    stream << static_cast<quint16>(idCategories.size());

    for (auto i : idCategories) {
        stream << i;
    }

    emit (signalSendCommand(buf, 0x02, false));
}

void QCategoryCommandsToServer::loadAll()
{
    QByteArray buf;
    QDataStream stream(&buf,QIODevice::WriteOnly);
    stream << 0x01;
    this->signalSendCommand(buf, 0x11, false);
}

void QCategoryCommandsToServer::send(QSalesCategory &category)
{
    QByteArray Output;
    QDataStream stream(&Output, QIODevice::WriteOnly);
    category >> stream;

    emit (signalSendCommand(Output, 0xC3, true));
}

void QCategoryCommandsToServer::remove(int id, const QString &name)
{
    QByteArray Output = getRemoveData(id, name);

    emit (signalSendCommand(Output, 0xC4, true));
}

