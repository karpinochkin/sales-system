#ifndef QPARENTCOMMANDSTOSERVER_H
#define QPARENTCOMMANDSTOSERVER_H

#include <QObject>
#include <QDebug>
#include <QDataStream>
#include <QByteArray>
#include "../commonFiles/SalesSystem/QSalesObjects/qsalesobjects.h"

namespace CommandsToServer {

class QParentCommandsToServer : public QObject
{
    Q_OBJECT

protected:
    explicit QParentCommandsToServer(QObject *parent = nullptr)
        : QObject(parent)
    {

    }

    QByteArray getRemoveData(int id, const QString& name) {
        QByteArray Output;
        QDataStream stream(&Output, QIODevice::WriteOnly);
        stream << id;
        stream << name;
        return Output;
    }

public:
    ~QParentCommandsToServer()  = default;

signals:
    void signalSendCommand(QByteArray &data, int command_code, bool save);
};
}


#endif // QPARENTCOMMANDSTOSERVER_H
