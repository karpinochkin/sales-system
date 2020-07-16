#include "quser.h"

void QUser::operator <<(QDataStream &stream)
{
    stream >> id;
    stream >> login;
    stream >> password;
    stream >> name;
    stream >> patronymic;
    stream >> surname;
}

void QUser::operator >>(QDataStream &stream)
{
    stream << id;
    stream << login;
    stream << password;
    stream << name;
    stream << patronymic;
    stream << surname;
}

bool QUser::isEmpty()
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

void QUser::clear()
{
    id = -1;
    login.clear();
    password.clear();
    name.clear();
    patronymic.clear();
    surname.clear();
}

QByteArray QUser::toByteArray()
{
    QByteArray Output;
    QSalesByteArray salesByteArray;

    salesByteArray.intToByteArray(id, &Output);
    salesByteArray.string45ToByteArray(login, &Output);
    salesByteArray.string45ToByteArray(password, &Output);
    salesByteArray.string45ToByteArray(name, &Output);
    salesByteArray.string45ToByteArray(patronymic, &Output);
    salesByteArray.string45ToByteArray(surname, &Output);

    return Output;
}

void QUser::fromByteArray(QByteArray &data)
{
    if (data.length()>3)
    {
        QSalesByteArray salesByteArray;
        salesByteArray.intFromByteArray(id, &data);
        salesByteArray.stringFromByteArray(login, &data);
        salesByteArray.stringFromByteArray(password, &data);
        salesByteArray.stringFromByteArray(name, &data);
        salesByteArray.stringFromByteArray(patronymic, &data);
        salesByteArray.stringFromByteArray(surname, &data);
    }
}

QString QUser::toString()
{
    QString Output;

    Output = "id:" + QString::number(id) + " login:" + login +
             " password:" +password + " name:" + name +
             " patronymic:" + patronymic + " surname:" + surname;

    return Output;
}
