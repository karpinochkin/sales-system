#include "qpointsale.h"

QPointSale::QPointSale()
{
    this->clear();
}

bool QPointSale::isEmpty()
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

void QPointSale::clear()
{
    id = -1;
    name.clear();
    idProducts.clear();
    idCategories.clear();
}

QByteArray QPointSale::toByteArray()
{
    QByteArray Output;
    QSalesByteArray salesByteArray;

    salesByteArray.intToByteArray(id, &Output);
    salesByteArray.string45ToByteArray(name, &Output);
    salesByteArray.vectorIntToByteArray(idCategories, &Output);
    salesByteArray.vectorIntToByteArray(idProducts, &Output);

    return Output;
}

void QPointSale::fromByteArray(QByteArray &data)
{
    if (data.length() > 3) {
        QSalesByteArray salesByteArray;
        salesByteArray.intFromByteArray(id, &data);
        salesByteArray.stringFromByteArray(name, &data);
        salesByteArray.vectorIntFromByteArray(idCategories, &data);
        salesByteArray.vectorIntFromByteArray(idProducts, &data);
    }
}

QString QPointSale::toString()
{
    QString Output;

    Output = "id:" + QString::number(id) + " name:" + name;

    Output = Output + "Categories: {";
    for (int i=0;i<idCategories.length();i++)
        Output = Output + QString::number(idCategories.at(i)) + " ";

    Output = Output + "}";

    Output = Output + "Drinks: {";
    for (int i=0;i<idProducts.length();i++)
        Output = Output + QString::number(idProducts.at(i)) + " ";

    Output = Output + "}";

    return Output;
}
