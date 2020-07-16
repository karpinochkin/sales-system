#ifndef QPRICE_H
#define QPRICE_H

#include <QDateTime>
#include "../QSalesObjects/qsalesobjects.h"

class QPrice : public QSalesObjects
{
public:
    QPrice();
    ~QPrice() = default;

    int id;
    double value;
    QDateTime startDate;
    QString description;
    int idProduct;
    int idVolume;
    int idProductCategory;

    QVector<int> idPointSales;

    void operator <<(QDataStream &stream);
    void operator >>(QDataStream &stream);

    bool isEmpty();
    void clear();
    QByteArray toByteArray();
    void fromByteArray(QByteArray &data);

    QString toString();
private:
    void setIdPointSaleFromStream(int size, QDataStream &stream);
    void setIdPointSaleToStream(QDataStream &stream);
};

Q_DECLARE_METATYPE( QPrice )
#endif // QPRICE_H
