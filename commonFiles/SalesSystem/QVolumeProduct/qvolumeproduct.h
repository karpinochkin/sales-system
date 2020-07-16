#ifndef QVOLUMEPRODUCT_H
#define QVOLUMEPRODUCT_H

#include <QVector>
#include <QDataStream>
#include "../QSalesObjects/qsalesobjects.h"

class QVolumeProduct : public QSalesObjects
{
public:
    QVolumeProduct() = default;
    ~QVolumeProduct() = default;

    int id;
    QString name;
    int volume;
    QString description;
    QString units;
    QVector<int> idProducts;

    void operator <<(QDataStream &stream);
    void operator >>(QDataStream &stream);

    bool isEmpty();
    void clear();
    QByteArray toByteArray();
    void fromByteArray(QByteArray &data);

    QString toString();
};

Q_DECLARE_METATYPE( QVolumeProduct )

#endif // QVOLUMEPRODUCT_H

