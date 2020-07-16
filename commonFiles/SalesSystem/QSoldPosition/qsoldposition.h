#ifndef QSOLDPOSITION_H
#define QSOLDPOSITION_H

#include <QDataStream>
#include <QDateTime>
#include <QVector>

class QSoldPosition
{
public:
    QSoldPosition() = default;
    ~QSoldPosition() = default;

    int id;
    int idUser;
    int count;
    int idProduct;
    int idTypeProduct;
    int idPrice;
    int idVolumeProduct;
    int idReceipt;
    int idPointSale;
    int numberInReceipt;
    QDateTime date;

    void operator <<(QDataStream &stream);
    void operator >>(QDataStream &stream);

    bool isEmpty();
    void clear();
    QByteArray toByteArray();
    void fromByteArray(QByteArray &data);

    QString toString();
};

Q_DECLARE_METATYPE( QSoldPosition )

#endif // QSOLDPOSITION_H
