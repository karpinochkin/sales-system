#include "qreceipt.h"

void QReceipt::operator <<(QDataStream &stream)
{
    stream >> id;
    stream >> dateTime;
    stream >> sum;
    stream >> idPointSale;
    stream >> idShift;
}

void QReceipt::operator >>(QDataStream &stream)
{
    stream << id;
    stream << dateTime;
    stream << sum;
    stream << idPointSale;
    stream << idShift;

}

bool QReceipt::isEmpty()
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

void QReceipt::clear()
{
    id = -1;
    dateTime.setTime_t(0);
    sum = -1;
    idPointSale = -1;
    idShift = -1;
}

QByteArray QReceipt::toByteArray()
{
    QByteArray Output;

    QDataStream stream(&Output,QIODevice::WriteOnly);

    stream << id;
    stream << dateTime;
    stream << sum;
    stream << idPointSale;
    stream << idShift;

    return Output;
}

void QReceipt::fromByteArray(QByteArray &data)
{
    if (data.length()>3)
    {
        QDataStream stream(&data,QIODevice::ReadOnly);
        stream.device()->seek(0);

        stream>>id;
        stream>>dateTime;
        stream>>sum;
        stream>>idPointSale;
        stream>>idShift;
    }
}

QString QReceipt::toString()
{
    QString Output;

    Output = "id: " + QString::number(id) + " data:" + dateTime.toString("yyyy-MM-dd hh:mm:ss") +
             " sum:" + QString::number(sum) + " idPointSale:" + QString::number(idPointSale) + " "
             " idShift:" + QString::number(idShift);

    return Output;
}
