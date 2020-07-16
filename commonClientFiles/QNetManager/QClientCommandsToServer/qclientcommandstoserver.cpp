#include "qclientcommandstoserver.h"

QClientCommandsToServer::QClientCommandsToServer(QObject *parent)
    : QObject(parent)
{
    createObjects();
    connects();
}

void QClientCommandsToServer::createObjects()
{
    pointSale = new QPointSaleCommandsToServer(this);
    category = new QCategoryCommandsToServer(this);
    product = new QProductCommandsToServer(this);
    price = new QPriceCommandsToServer(this);
    volume = new QVolumeCommandsToServer(this);
    type = new QTypeCommandsToServer(this);
    user = new QUserCommandsToServer(this);
    shift = new QShiftCommandsToServer(this);
    receipt = new QReceiptCommandsToServer(this);
    soldPosition = new QSoldPositionCommandsToServer(this);
    statistics = new QStatisticsCommandsToServer(this);
    picture = new QPictureCommandsToServer(this);
}

void QClientCommandsToServer::connects()
{
    connect(pointSale, &QPointSaleCommandsToServer::signalSendCommand,
            this, &QClientCommandsToServer::signalSendCommand);
    connect(category, &QCategoryCommandsToServer::signalSendCommand,
            this, &QClientCommandsToServer::signalSendCommand);
    connect(product, &QProductCommandsToServer::signalSendCommand,
            this, &QClientCommandsToServer::signalSendCommand);
    connect(price, &QPriceCommandsToServer::signalSendCommand,
            this, &QClientCommandsToServer::signalSendCommand);
    connect(volume, &QVolumeCommandsToServer::signalSendCommand,
            this, &QClientCommandsToServer::signalSendCommand);
    connect(type, &QTypeCommandsToServer::signalSendCommand,
            this, &QClientCommandsToServer::signalSendCommand);
    connect(user, &QUserCommandsToServer::signalSendCommand,
            this, &QClientCommandsToServer::signalSendCommand);
    connect(shift, &QShiftCommandsToServer::signalSendCommand,
            this, &QClientCommandsToServer::signalSendCommand);
    connect(receipt, &QReceiptCommandsToServer::signalSendCommand,
            this, &QClientCommandsToServer::signalSendCommand);
    connect(soldPosition, &QSoldPositionCommandsToServer::signalSendCommand,
            this, &QClientCommandsToServer::signalSendCommand);
    connect(statistics, &QStatisticsCommandsToServer::signalSendCommand,
            this, &QClientCommandsToServer::signalSendCommand);
    connect(picture, &QPictureCommandsToServer::signalSendCommand,
            this, &QClientCommandsToServer::signalSendCommand);
}

void QClientCommandsToServer::getHandshake()
{
    QString str = "Hello world!";
    QByteArray data = str.toLatin1();
    signalSendCommand(data, 0xA1, false);
}

void QClientCommandsToServer::endSynchronization()
{
    QString str = "End synch!";
    QByteArray data = str.toLatin1();
    signalSendCommand(data, 0xA2, false);
}
