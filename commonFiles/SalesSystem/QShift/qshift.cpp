#include "qshift.h"

QShift::QShift()
{
    this->clear();
}

void QShift::operator <<(QDataStream &stream)
{
    stream >> id;
    stream >> openTime;
    stream >> closeTime;
    stream >> open;
    stream >> close;
    stream >> idUser;
    stream >> idPointSale;
}

void QShift::operator >>(QDataStream &stream)
{
    stream << id;
    stream << openTime;
    stream << closeTime;
    stream << open;
    stream << close;
    stream << idUser;
    stream << idPointSale;
}

bool QShift::isEmpty()
{
    bool Output = true;

    if (id == -1) {
        Output = true;
    }
    else {
        Output = false;
    }

    return Output;
}

void QShift::clear()
{
    id = -1;
    openTime.setTime_t(0);
    closeTime.setTime_t(0);
    open = false;
    close = false;
    idUser = -1;
    idPointSale = -1;
}

QByteArray QShift::toByteArray()
{
    QByteArray Output;

    QDataStream stream(&Output,QIODevice::WriteOnly);

    stream << id;
    stream << openTime;
    stream << closeTime;
    stream << open;
    stream << close;
    stream << idUser;
    stream << idPointSale;


    return Output;
}

void QShift::fromByteArray(QByteArray &data)
{
    if (data.length()>3)
    {
        QDataStream stream(&data,QIODevice::ReadOnly);
        stream.device()->seek(0);

        stream >> id;
        stream >> openTime;
        stream >> closeTime;
        stream >> open;
        stream >> close;
        stream << idUser;
        stream << idPointSale;
    }
}

QString QShift::toString()
{
    QString Output;

    Output = "id:" + QString::number(id) +
             " openTime:" + openTime.toString("yyyy-MM-dd hh:mm:ss") +
             " closeTime:" + closeTime.toString("yyyy-MM-dd hh:mm:ss") +
             " open:" +QString::number(open) +
             " close:" +QString::number(close) +
             " idUser:" +QString::number(idUser) +
             " idPointSale:" +QString::number(idPointSale);


    return Output;
}

