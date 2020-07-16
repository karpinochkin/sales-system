#ifndef QUSER_H
#define QUSER_H

//#include <QDataStream>
#include "../QSalesByteArray/qsalesbytearray.h"
#include "../QSalesObjects/qsalesobjects.h"

class QUser : public QSalesObjects
{
public:
    QUser() = default;
    ~QUser() = default;

    int id;
    QString login;
    QString password;
    QString name;
    QString patronymic;
    QString surname;

    void operator <<(QDataStream &stream);
    void operator >>(QDataStream &stream);

    bool isEmpty();
    void clear();
    QByteArray toByteArray();
    void fromByteArray(QByteArray &data);

    QString toString();
};

Q_DECLARE_METATYPE( QUser )

#endif // QUSER_H
