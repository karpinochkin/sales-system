#ifndef QTYPEPRODUCT_H
#define QTYPEPRODUCT_H

#include <QDataStream>
#include "../QSalesByteArray/qsalesbytearray.h"
#include "../QSalesObjects/qsalesobjects.h"

enum PaymentType {
    Cash = 1,
    NonCash = 2,
    Free = 3
};

class QPaymentType : public QSalesObjects
{
public:
    QPaymentType() = default;
    ~QPaymentType() = default;

    int id;
    QString name;
    QString description;

    void operator <<(QDataStream &stream);
    void operator >>(QDataStream &stream);

    bool isEmpty();
    void clear();
    QByteArray toByteArray();
    void fromByteArray(QByteArray &data);

    QString toString();
};

Q_DECLARE_METATYPE( QPaymentType )
#endif // QTYPEPRODUCT_H


