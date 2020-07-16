#ifndef QPOINTSALEQUERIES_H
#define QPOINTSALEQUERIES_H

#include <QString>

class QPointSaleQueries
{
public:
    static QString getTableName();
    static QString getColumnName_ID();
    static QString getColumnName_Name();
    static QString createTable_text();
    static QString createPointSaleAndProductTable_text();
    static QString getPointSales_QueryText();
    static QString getProductsId_QueryText(int idPointSale);
    static QString get_QueryText(int idPointSale);
    static QString edit_QueryText(int idPointSale, const QString &namePointSale);
    static QString getId_QueryText(const QString &namePointSale);
    static QString add(int nextId, const QString &namePointSale);
    static QString unlinkProducts(int idPointSale);
    static QString linkProduct(int idPointSale, int idProduct);

private:
    QPointSaleQueries();

    static const QString TABLE_POINT_SALE;
    static const QString ID;
    static const QString NAME;
};

#endif // QPOINTSALEQUERIES_H
