#include "qproduct.h"

void QProduct::operator<<(QDataStream &stream)
{
    idCategories.clear();
    quint16 count;

    stream >> id;
    stream >> name;
    stream >> description;
    stream >> count;
    setIdCategoriesFromStream(count, stream);
    color << stream;
    stream >> idPicture;
    stream >> pictureHash;
}

void QProduct::setIdCategoriesFromStream(int size, QDataStream &stream)
{
    int currentId;
    for (int i = 0; i < size; i++) {
        stream >> currentId;
        idCategories.push_back(currentId);
    }
}

void QProduct::operator>>(QDataStream &stream)
{
    stream << id;
    stream << name;
    stream << description;

    stream << static_cast<quint16>(idCategories.size());
    setIdCategoriesToStream(stream);
    color >> stream;
    stream << idPicture;
    stream <<pictureHash;
}

void QProduct::setIdCategoriesToStream(QDataStream &stream)
{
    int currentId;
    for (int i = 0 ;i < idCategories.size(); i++) {
        currentId = idCategories.at(i);
        stream << currentId;
    }
}

bool QProduct::isEmpty()
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

void QProduct::clear()
{
    id = -1;
    name.clear();
    description.clear();
    color.clear();
    idPicture = -1;
    pictureHash.clear();
    idCategories.clear();
}

QByteArray QProduct::toByteArray()
{
    QByteArray Output;
    QSalesByteArray salesByteArr;

    salesByteArr.intToByteArray(id, &Output);
    salesByteArr.string45ToByteArray(name, &Output);
    salesByteArr.string256ToByteArray(description, &Output);
    salesByteArr.vectorIntToByteArray(idCategories, &Output);

    return Output;
}

void QProduct::fromByteArray(QByteArray &data)
{
    if (data.length()>3)
    {
        QSalesByteArray salesByteArr;

        salesByteArr.intFromByteArray(id, &data);
        salesByteArr.stringFromByteArray(name, &data);
        salesByteArr.stringFromByteArray(description, &data);
        salesByteArr.vectorIntFromByteArray(idCategories, &data);
    }
}

QString QProduct::toString()
{
    QString Output;

    Output = "id:"
            + QString::number(id)
            + " name:"
            + name
            + " description:"
            + description;

    Output = Output + "Categoryes: {";

    for (int i = 0; i < idCategories.size(); i++) {
        Output = Output + QString::number(idCategories.at(i)) + " ";
    }

    Output = Output + "}";

    Output = Output + "color: {" +
            QString::number(color.red()) + "," +
            QString::number(color.green()) + "," +
            QString::number(color.blue()) +"} ";

    Output = Output + "Picture hash: " + pictureHash;

    return Output;
}
