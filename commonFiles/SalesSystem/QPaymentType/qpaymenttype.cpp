#include "qpaymenttype.h"

void QPaymentType::operator <<(QDataStream &stream)
{
    stream >> id;
    stream >> name;
    stream >> description;
}

void QPaymentType::operator >>(QDataStream &stream)
{
    stream << id;
    stream << name;
    stream << description;
}

bool QPaymentType::isEmpty()
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

void QPaymentType::clear()
{
    id = -1;
    name.clear();
    description.clear();
}

QByteArray QPaymentType::toByteArray()
{
    QByteArray Output;

    QSalesByteArray salesByteArray;
    salesByteArray.intToByteArray(id, &Output);
    salesByteArray.string45ToByteArray(name, &Output);
    salesByteArray.string256ToByteArray(description, &Output);

    return Output;
}

void QPaymentType::fromByteArray(QByteArray &data)
{
    if (data.length()>3)
    {
        QSalesByteArray salesByteArray;
        salesByteArray.intFromByteArray(id, &data);
        salesByteArray.stringFromByteArray(name, &data);
        salesByteArray.stringFromByteArray(description, &data);
    }
}

QString QPaymentType::toString()
{
    QString Output;

    Output = "id:" + QString::number(id) + " name:" + name + " description:" +description;

    return Output;
}
