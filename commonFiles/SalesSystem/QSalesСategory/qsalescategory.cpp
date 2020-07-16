#include "qsalescategory.h"

void QSalesCategory::operator<<(QDataStream &stream)
{
    idPointSale.clear();
    quint16 count;

    stream >> id;
    stream >> name;
    stream >> description;
    color << stream;
    stream >> count;
    setIdPointSalesFromStream(count, stream);
}

void QSalesCategory::setIdPointSalesFromStream(int size, QDataStream &stream)
{
    int id = 0;

    for (int i = 0; i < size; i++) {
        stream >> id;
        idPointSale.push_back(id);
    }
}

void QSalesCategory::operator>>(QDataStream &stream)
{
    stream << id;
    stream << name;
    stream << description;
    color >> stream;
    stream << static_cast<quint16>(idPointSale.size());
    setIdPointSalesToStream(stream);
}

void QSalesCategory::setIdPointSalesToStream(QDataStream &stream)
{
    int id = 0;

    for (int i = 0; i < idPointSale.size(); i++) {
        id = idPointSale.at(i);
        stream << id;
    }
}

bool QSalesCategory::isEmpty()
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

void QSalesCategory::clear()
{
    id = -1;
    name.clear();
    description.clear();
    color.clear();
    idPointSale.clear();
}

QByteArray QSalesCategory::toByteArray()
{
    QByteArray Output;
    QSalesByteArray salesByteArr;

    salesByteArr.intToByteArray(id, &Output);
    salesByteArr.string45ToByteArray(name, &Output);
    salesByteArr.string256ToByteArray(description, &Output);
    salesByteArr.vectorIntToByteArray(idPointSale, &Output);

    return Output;
}

void QSalesCategory::fromByteArray(QByteArray &data)
{
    if (data.size() > 3) {
        QSalesByteArray salesByteArray;

        salesByteArray.intFromByteArray(id, &data);
        salesByteArray.stringFromByteArray(name, &data);
        salesByteArray.stringFromByteArray(description, &data);
        salesByteArray.vectorIntFromByteArray(idPointSale, &data);
    }
}

QString QSalesCategory::toString()
{
    QString Output;

    Output = "id:"
            + QString::number(id)
            + " name:"
            + name
            + " description:"
            + description;

    Output = Output + "Sale Point: {";

    for (int i = 0; i < idPointSale.size(); i++)
        Output = Output
                + QString::number(idPointSale.at(i))
                + " ";

    Output = Output + "}";

    return Output;
}
