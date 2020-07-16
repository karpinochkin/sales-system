#ifndef QTYPEPRODUCTQUERIES_H
#define QTYPEPRODUCTQUERIES_H

#include <QString>
#include "../commonFiles/SalesSystem/QPaymentType/qpaymenttype.h"

class QPaymentTypeQueries
{
public:
    static QString createTable_text();
    static QString getTableName();
    static QString getColumnName_ID();
    static QString getColumnName_Name();
    static QString getTypes_text();
    static QString get_text(int idTypeProduct);
    static QString add_text(int id, const QPaymentType &type);
    static QString edit_text(const QPaymentType &type);
    static QString getId_text(const QPaymentType &type);
    static QString remove_text(int id, const QString &name);

private:
    QPaymentTypeQueries();

    static const QString TABLE;
    static const QString ID;
    static const QString NAME;
    static const QString DESCRIPTION;
};

#endif // QTYPEPRODUCTQUERIES_H
