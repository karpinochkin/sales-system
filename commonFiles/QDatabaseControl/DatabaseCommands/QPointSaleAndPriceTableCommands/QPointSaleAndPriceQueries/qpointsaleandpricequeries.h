#ifndef QPOINTSALEANDPRICEQUERIES_H
#define QPOINTSALEANDPRICEQUERIES_H

#include <QString>

class QPointSaleAndPriceQueries
{
public:
    static QString createTable_text();
    static QString getIdPrices_text(int idPointSale);
    static QString getIdPointSales_text(int idPrice);
    static QString unlinkPointSales_text(int idPice);
    static QString linkPointSale_text(int idPrice, int idPointSale);
private:
    QPointSaleAndPriceQueries();

};

#endif // QPOINTSALEANDPRICEQUERIES_H
