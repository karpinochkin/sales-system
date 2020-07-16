#ifndef QPRICEQUERIES_H
#define QPRICEQUERIES_H

#include <QString>
#include "../commonFiles/SalesSystem/QPrice/qprice.h"

class QPriceQueries
{
public:
    static QString createTable_text();
    static QString getTableName();
    static QString getColumnName_ID();
    static QString getPrices_text();
    static QString get_text(int idPrice);
    static QString get_text(int idCategory, int idProduct, int idVolume);
    static QString add_text(int id, const QPrice &price);
    static QString edit_text(const QPrice &price);
    static QString getId_text(const QPrice &price);

private:
    explicit QPriceQueries();

    static const QString TABLE;
    static const QString ID;
    static const QString VALUE;
    static const QString START_TIME;
    static const QString DESCRIPTION;
    static const QString ID_PRODUCT;
    static const QString ID_VOLUME;
    static const QString ID_CATEGORY;
};

#endif // QPRICEQUERIES_H
