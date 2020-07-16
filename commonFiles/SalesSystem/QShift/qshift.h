#ifndef QSHIFT_H
#define QSHIFT_H

#include <QDataStream>
#include <QDateTime>

class QShift
{
public:
    QShift();
    ~QShift() = default;

    int id;
    QDateTime openTime;
    QDateTime closeTime;
    bool open;
    bool close;
    int idUser;
    int idPointSale;

    void operator <<(QDataStream &stream);
    void operator >>(QDataStream &stream);

    bool isEmpty();
    void clear();
    QByteArray toByteArray();
    void fromByteArray(QByteArray &data);

    QString toString();
};

Q_DECLARE_METATYPE( QShift )

#endif // QSHIFT_H
