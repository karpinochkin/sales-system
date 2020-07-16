#include "qpointsalequeries.h"

const QString QPointSaleQueries::TABLE_POINT_SALE = "tbl_pointSale";
const QString QPointSaleQueries::ID = "id_pointSale";
const QString QPointSaleQueries::NAME = "name_pointSale";

QPointSaleQueries::QPointSaleQueries()
{

}

QString QPointSaleQueries::getTableName()
{
    return TABLE_POINT_SALE;
}

QString QPointSaleQueries::getColumnName_ID()
{
    return ID;
}

QString QPointSaleQueries::getColumnName_Name()
{
    return NAME;
}

QString QPointSaleQueries::createTable_text()
{
    QString text = "CREATE TABLE IF NOT EXISTS "
            + TABLE_POINT_SALE + " ("
            + ID + " INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,"
            + NAME + " text NOT NULL);";
    return text;
}

QString QPointSaleQueries::createPointSaleAndProductTable_text()
{
    QString textQuery = "CREATE TABLE IF NOT EXISTS tbl_product_pointSale ("
                        "tbl_product_id_product INTEGER NOT NULL,"
                        "tbl_pointSale_id_pointSale INTEGER NOT NULL);";
    return textQuery;
}

QString QPointSaleQueries::getPointSales_QueryText()
{
    QString queryText = "select " + ID + ", "
            + NAME + " from " + TABLE_POINT_SALE + ";";

    return  queryText;
}

QString QPointSaleQueries::getProductsId_QueryText(int idPointSale)
{
    QString textQuery = "select tbl_product_id_product from tbl_product_pointSale "
                        "where tbl_pointSale_id_pointSale = '" + QString::number(idPointSale) + "';";

    return textQuery;
}

QString QPointSaleQueries::get_QueryText(int idPointSale)
{
    QString queryText = "select " + ID + ", " + NAME + " from " + TABLE_POINT_SALE
            + " where " + ID + " = '" + QString::number(idPointSale) + "';";
    return  queryText;
}

QString QPointSaleQueries::edit_QueryText(int idPointSale, const QString &namePointSale)
{
    QString textQuery = "update " + TABLE_POINT_SALE + " set " + NAME + " = '"
            + namePointSale + "' where " + ID + " = '" + QString::number(idPointSale)
            + "';";
    return textQuery;
}

QString QPointSaleQueries::unlinkProducts(int idPointSale)
{
    QString textQuery = "delete from tbl_product_pointSale "
                        "where tbl_pointSale_id_pointSale = '" + QString::number(idPointSale) + "';";
    return textQuery;
}

QString QPointSaleQueries::linkProduct(int idPointSale, int idProduct)
{
    QString textQuery = "insert into tbl_product_pointSale (tbl_product_id_product,"
                        "tbl_pointSale_id_pointSale) "
                        "values ('" + QString::number(idProduct)+ "','" + QString::number(idPointSale) + "');";
    return textQuery;
}

QString QPointSaleQueries::add(int nextId, const QString &namePointSale)
{
    QString textQuery = "insert into " + TABLE_POINT_SALE + " (" + ID + ", " + NAME
            + ") values ('" + QString::number(nextId) + "','" + namePointSale + "');";
    return textQuery;
}

QString QPointSaleQueries::getId_QueryText(const QString &namePointSale)
{
    QString textQuery = "select " + ID + " from " + TABLE_POINT_SALE
            + " where " + NAME + " = '" + namePointSale + "';";
    return textQuery;
}

