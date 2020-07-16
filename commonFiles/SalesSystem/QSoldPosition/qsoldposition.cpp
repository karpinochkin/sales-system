#include "qsoldposition.h"

void QSoldPosition::operator <<(QDataStream &stream)
{
    stream >> id;
    stream >> idUser;
    stream >> count;
    stream >> idProduct;
    stream >> idTypeProduct;
    stream >> idPrice;
    stream >> idVolumeProduct;
    stream >> idReceipt;
    stream >> idPointSale;
    stream >> numberInReceipt;
    stream >> date;
}

void QSoldPosition::operator >>(QDataStream &stream)
{
    stream << id;
    stream << idUser;
    stream << count;
    stream << idProduct;
    stream << idTypeProduct;
    stream << idPrice;
    stream << idVolumeProduct;
    stream << idReceipt;
    stream << idPointSale;
    stream << numberInReceipt;
    stream << date;

}

bool QSoldPosition::isEmpty()
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

void QSoldPosition::clear()
{
    id = -1;
    idUser = -1;
    count = -1;
    idProduct = -1;
    idTypeProduct = -1;
    idPrice = -1;
    idVolumeProduct = -1;
    idReceipt = -1;
    idPointSale = -1;
    numberInReceipt = -1;
    date.setTime_t(0);
}

QByteArray QSoldPosition::toByteArray()
{
    QByteArray Output;

    QDataStream stream(&Output,QIODevice::WriteOnly);

    stream << id;
    stream << idUser;
    stream << count;
    stream << idProduct;
    stream << idTypeProduct;
    stream << idPrice;
    stream << idVolumeProduct;
    stream << idReceipt;
    stream << idPointSale;
    stream << numberInReceipt;
    stream << date;

    return Output;
}

void QSoldPosition::fromByteArray(QByteArray &data)
{
    if (data.length()>3)
    {
        QDataStream stream(&data,QIODevice::ReadOnly);
        stream.device()->seek(0);

        stream >> id;
        stream >> idUser;
        stream >> count;
        stream >> idProduct;
        stream >> idTypeProduct;
        stream >> idPrice;
        stream >> idVolumeProduct;
        stream >> idReceipt;
        stream >> idPointSale;
        stream >> numberInReceipt;
        stream >> date;
    }
}

QString QSoldPosition::toString()
{
    QString Output;

    Output = Output + "id:" + QString::number(id);
    Output = Output + "idUser:" + QString::number(idUser);
    Output = Output + " count:" + QString::number(count);
    Output = Output + " idDrink:" + QString::number(idProduct);
    Output = Output + " idTypeDrink:" + QString::number(idTypeProduct);
    Output = Output + " idPrice:" + QString::number(idPrice);
    Output = Output + " idVolumeDrink:" + QString::number(idVolumeProduct);
    Output = Output + " idReceipt:" + QString::number(idReceipt);
    Output = Output + " idPointSale:" + QString::number(idPointSale);
    Output = Output + " numberInReceipt:" + QString::number(numberInReceipt);
    Output = Output + " date:" + date.toString("yyyy-MM-dd hh:mm:ss");

    return Output;
}
