#ifndef QPOINTSALEANDCATEGORYTABLEQUERIES_H
#define QPOINTSALEANDCATEGORYTABLEQUERIES_H

#include <QString>

class QPointSaleAndCategoryTableQueries
{
public:
    static QString createTable_text();
    static QString getCategoriesId_QueryText(int idPointSale);
    static QString getPointSalesId_QueryText(int idCategory);
    static QString unlinkCategories(int idPointSale);
    static QString unlinkPointSales(int idCategory);
    static QString linkCategory(int idPointSale, int idCategory);
    static QString linkPointSale(int idCategory, int idPointSale);
private:
    QPointSaleAndCategoryTableQueries();
};

#endif // QPOINTSALEANDCATEGORYTABLEQUERIES_H
