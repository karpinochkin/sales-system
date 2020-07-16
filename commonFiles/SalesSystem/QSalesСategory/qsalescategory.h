#ifndef QSALESCATEGORY_H
#define QSALESCATEGORY_H

#include "../QColorConsole/qcolorconsole.h"
#include "../QSalesByteArray/qsalesbytearray.h"
#include "../QSalesObjects/qsalesobjects.h"

class QSalesCategory : public QSalesObjects
{
public:
    QSalesCategory() = default;
    ~QSalesCategory() = default;

    int id;
    QString name;
    QString description;
    QColorConsole color;

    QVector<int> idPointSale;

    void operator <<(QDataStream &stream);
    void operator >>(QDataStream &stream);

    bool isEmpty();
    void clear();
    QString toString();
    QByteArray toByteArray();
    void fromByteArray(QByteArray &data);

private:
    void setIdPointSalesFromStream(int size, QDataStream &stream);
    void setIdPointSalesToStream(QDataStream &stream);
};
Q_DECLARE_METATYPE( QSalesCategory )

#endif // QSALESCATEGORY_H
