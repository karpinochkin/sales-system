#ifndef QRECEIPT_H
#define QRECEIPT_H

#include <QObject>
#include <QDateTime>
#include <QDataStream>
#include "../QSalesObjects/qsalesobjects.h"

class QReceipt : public QSalesObjects
{
public:
    QReceipt() = default;
    ~QReceipt() = default;

    int id = 0;
    QDateTime dateTime;
    double sum = 0;
    int idPointSale = 0;
    int idShift = 0;

    void operator <<(QDataStream &stream);
    void operator >>(QDataStream &stream);

    bool isEmpty();
    void clear();
    QByteArray toByteArray();
    void fromByteArray(QByteArray &data);
    QString toString();
};

Q_DECLARE_METATYPE( QReceipt )
#endif // QRECEIPT_H
