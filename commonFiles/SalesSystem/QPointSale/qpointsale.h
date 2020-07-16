#ifndef QSALESPOINTSALE_H
#define QSALESPOINTSALE_H

#include "../QSalesObjects/qsalesobjects.h"
#include "../QSalesByteArray/qsalesbytearray.h"

class QPointSale : public QSalesObjects
{
public:
    QPointSale();
    ~QPointSale() = default;

    int id;
    QString name;

    QVector<int> idProducts;
    QVector<int> idCategories;

    bool isEmpty();
    void clear();
    QByteArray toByteArray();
    void fromByteArray(QByteArray &data);
    QString toString();

};

Q_DECLARE_METATYPE( QPointSale )
#endif // QSALESPOINTSALE_H
