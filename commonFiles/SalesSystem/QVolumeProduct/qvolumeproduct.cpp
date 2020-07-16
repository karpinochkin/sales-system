#include "qvolumeproduct.h"

bool QVolumeProduct::isEmpty()
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

void QVolumeProduct::clear()
{
    id = -1;
    name.clear();
    volume = -1;
    description.clear();
    units.clear();
    idProducts.clear();
}

void QVolumeProduct::operator <<(QDataStream &stream)
{
    stream >> id;
    stream >> name;
    stream >> volume;
    stream >> description;
    stream >> units;

    idProducts.clear();
    quint16 count;
    stream >> count;
    int currentId;
    for (int i=0;i<count;i++){
        stream>>currentId;
        idProducts.push_back(currentId);
    }
}

void QVolumeProduct::operator >>(QDataStream &stream)
{
    stream << id;
    stream << name;
    stream << volume;
    stream << description;
    stream << units;

    stream << static_cast<quint16>(idProducts.length());
    int currentId;
    for (int i=0;i<idProducts.length();i++) {
        currentId = idProducts.at(i);
        stream << currentId;
    }
}

QByteArray QVolumeProduct::toByteArray()
{
    QByteArray Output;

    QDataStream stream(&Output,QIODevice::WriteOnly);

    stream << id;
    stream << name;
    stream << volume;
    stream << description;
    stream << idProducts;


    return Output;
}

void QVolumeProduct::fromByteArray(QByteArray &data)
{
    if (data.length()>3)
    {
        QDataStream stream(&data, QIODevice::ReadOnly);
        stream.device()->seek(0);

        stream >> id;
        stream >> name;
        stream >> volume;
        stream >> description;
        stream >> idProducts;
    }
}

QString QVolumeProduct::toString()
{
    QString Output;

    Output = "id: " + QString::number(id) + " name:" + name +
             " volume:" + QString::number(volume) + " description:" + description;

    Output = Output + " idDrink{";

    for (int i=0;i<idProducts.length();i++)
        Output = Output + QString::number(idProducts.at(i)) + " ";

    Output = Output + "}";

    return Output;
}
