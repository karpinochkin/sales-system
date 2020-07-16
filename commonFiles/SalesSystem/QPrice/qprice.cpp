#include "qprice.h"

QPrice::QPrice()
{
    this->clear();
}

void QPrice::operator<<(QDataStream &stream)
{
    idPointSales.clear();
    stream >> id;
    stream >> value;
    stream >> startDate;
    stream >> description;
    stream >> idProduct;
    stream >> idVolume;
    stream >> idProductCategory;
    quint16 count;
    stream >> count;
    setIdPointSaleFromStream(count, stream);
}

void QPrice::setIdPointSaleFromStream(int size, QDataStream &stream)
{
    int currentId;
    for (int i = 0; i < size; i++) {
        stream >> currentId;
        idPointSales.push_back(currentId);
    }
}

void QPrice::operator>>(QDataStream &stream)
{
    stream << id;
    stream << value;
    stream << startDate;
    stream << description;
    stream << idProduct;
    stream << idVolume;
    stream << idProductCategory;

    stream << static_cast<quint16>(idPointSales.size());
    setIdPointSaleToStream(stream);
}

void QPrice::setIdPointSaleToStream(QDataStream &stream)
{
    int currentId;
    for (int i = 0; i < idPointSales.size(); i++) {
        currentId = idPointSales.at(i);
        stream << currentId;
    }
}

bool QPrice::isEmpty()
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

void QPrice::clear()
{
    id = -1;
    value = -1;
    startDate.setTime_t(0);
    description.clear();
    idProduct = -1;
    idVolume = -1;
    idProductCategory = -1;
    idPointSales.clear();
}

QByteArray QPrice::toByteArray()
{
    QByteArray Output;

    QDataStream stream(&Output,QIODevice::WriteOnly);

    stream<<id;
    stream<<value;
    stream<<startDate;
    stream<<description;
    stream<<idProduct;
    stream<<idVolume;
    stream<<idProductCategory;

    stream<<idPointSales;

    return Output;
}

void QPrice::fromByteArray(QByteArray &data)
{
    if (data.length()>3)
    {

        QDataStream stream(&data,QIODevice::ReadOnly);
        stream.device()->seek(0);

        stream>>id;
        stream>>value;
        stream>>startDate;
        stream>>description;
        stream>>idProduct;
        stream>>idVolume;
        stream>>idProductCategory;

        stream>>idPointSales;
    }
}

QString QPrice::toString()
{
    QString Output;


    Output =    "id: " + QString::number(id) +
                " value:" + QString::number(value) +
                " startDate:" + startDate.toString("yyyy-MM-dd hh:mm:ss") +
                " description:" + description +
                " idDrink:" + QString::number(idProduct) +
                " idVolume:" + QString::number(idVolume) +
                " idDrinkCategory:" + QString::number(idProductCategory);

    Output = Output + " idPointSale{";

    for (int i=0;i<idPointSales.length();i++)
        Output = Output + QString::number(idPointSales.at(i)) + " ";

    Output = Output + "}";

    return Output;
}
