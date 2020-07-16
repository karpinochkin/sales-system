#include "qpointsaleandcategorytablequeries.h"

QPointSaleAndCategoryTableQueries::QPointSaleAndCategoryTableQueries()
{

}

QString QPointSaleAndCategoryTableQueries::createTable_text()
{
    QString text = "CREATE TABLE IF NOT EXISTS tbl_pointSale_productСategory ("
                   "tbl_pointSale_id_pointSale INTEGER NOT NULL,"
                   "tbl_productСategory_id_productСategory INTEGER NOT NULL);";
    return text;
}

QString QPointSaleAndCategoryTableQueries::getCategoriesId_QueryText(int idPointSale)
{
    QString textQuery = "select tbl_productСategory_id_productСategory from tbl_pointSale_productСategory "
                        "where tbl_pointSale_id_pointSale = '" + QString::number(idPointSale) + "';";

    return  textQuery;
}

QString QPointSaleAndCategoryTableQueries::getPointSalesId_QueryText(int idCategory)
{
    QString text = "select tbl_pointSale_id_pointSale from tbl_pointSale_productСategory "
                   "where tbl_productСategory_id_productСategory = '" + QString::number(idCategory) + "';";
    return text;
}

QString QPointSaleAndCategoryTableQueries::unlinkCategories(int idPointSale)
{
    QString textQuery = "delete from tbl_pointSale_productСategory "
                        "where tbl_pointSale_id_pointSale = '" + QString::number(idPointSale) + "';";
    return textQuery;
}

QString QPointSaleAndCategoryTableQueries::unlinkPointSales(int idCategory)
{

    QString textQuery = "delete from tbl_pointSale_productСategory "
                        "where tbl_productСategory_id_productСategory = '" + QString::number(idCategory) + "';";
    return textQuery;
}

QString QPointSaleAndCategoryTableQueries::linkCategory(int idPointSale,
                                                        int idCategory)
{
    QString textQuery = "insert into tbl_pointSale_productСategory (tbl_pointSale_id_pointSale,"
                        "tbl_productСategory_id_productСategory) "
                        "values ('" + QString::number(idPointSale)+ "','" + QString::number(idCategory) + "');";
    return textQuery;
}

QString QPointSaleAndCategoryTableQueries::linkPointSale(int idCategory,
                                                         int idPointSale)
{
    QString text = "insert into tbl_pointSale_productСategory (tbl_pointSale_id_pointSale,"
                   "tbl_productСategory_id_productСategory) "
                   "values ('" + QString::number(idPointSale) + "','" + QString::number(idCategory) + "');";
    return text;
}

