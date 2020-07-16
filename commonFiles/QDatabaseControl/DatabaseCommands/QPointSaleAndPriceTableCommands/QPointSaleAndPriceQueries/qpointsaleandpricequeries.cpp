#include "qpointsaleandpricequeries.h"

QPointSaleAndPriceQueries::QPointSaleAndPriceQueries()
{

}

QString QPointSaleAndPriceQueries::createTable_text()
{
    QString text = "CREATE TABLE IF NOT EXISTS tbl_pointSale_price ("
                   "tbl_pointSale_id_pointSale INTEGER NOT NULL,"
                   "tbl_price_id_price INTEGER NOT NULL);";
    return text;
}

QString QPointSaleAndPriceQueries::getIdPrices_text(int idPointSale)
{
    QString textQuery = "select tbl_price_id_price from tbl_pointSale_price "
                        "where tbl_pointSale_id_pointSale = '"
            + QString::number(idPointSale) + "';";
    return  textQuery;
}

QString QPointSaleAndPriceQueries::getIdPointSales_text(int idPrice)
{
    QString textQuery = "select tbl_pointSale_id_pointSale from tbl_pointSale_price "
                        "where tbl_price_id_price = '"
            + QString::number(idPrice) +"';";
    return textQuery;
}

QString QPointSaleAndPriceQueries::unlinkPointSales_text(int idPice)
{
    QString textQuery = "delete from tbl_pointSale_price "
                        "where tbl_price_id_price = '"
            + QString::number(idPice) + "';";
    return textQuery;
}

QString QPointSaleAndPriceQueries::linkPointSale_text(int idPrice, int idPointSale)
{
    QString textQuery = "insert into tbl_pointSale_price "
                        "(tbl_pointSale_id_pointSale,tbl_price_id_price) "
                        "values ('" + QString::number(idPointSale) + "','"
            + QString::number(idPrice) + "');";
    return textQuery;
}
