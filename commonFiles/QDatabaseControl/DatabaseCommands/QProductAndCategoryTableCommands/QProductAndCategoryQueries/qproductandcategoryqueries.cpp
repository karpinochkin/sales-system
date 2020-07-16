#include "qproductandcategoryqueries.h"

QProductAndCategoryQueries::QProductAndCategoryQueries()
{

}

QString QProductAndCategoryQueries::createTable_text()
{
    QString textQuery = "CREATE TABLE IF NOT EXISTS tbl_product_category ("
                "tbl_product_id_product INTEGER NOT NULL,"
                "tbl_categoty_id_category INTEGER NOT NULL);";
    return textQuery;
}

QString QProductAndCategoryQueries::getIdCategories_text(int idProduct)
{

    QString textQuery = "select tbl_categoty_id_category"
                        " from tbl_product_category "
                        "where tbl_product_id_product = '"
            + QString::number(idProduct) + "';";
    return textQuery;
}

QString QProductAndCategoryQueries::getIdProducts_text(int idCategory)
{
    QString textQuery = "select tbl_product_id_product from "
                        "tbl_product_category where "
                        "tbl_categoty_id_category = '"
            + QString::number(idCategory) + "';";
    return textQuery;
}

QString QProductAndCategoryQueries::linkCategory(int idProduct, int idCategory)
{
    QString textQuery = "insert into tbl_product_category "
                        "(tbl_product_id_product,tbl_categoty_id_category) "
                        "values('" + QString::number(idProduct)
            + "','" + QString::number(idCategory) + "');";
    return textQuery;
}

QString QProductAndCategoryQueries::unlinkCategories(int idProduct)
{
    QString textQuery = "delete from tbl_product_category "
                        "where tbl_product_id_product = '"
            + QString::number(idProduct) + "';";
    return textQuery;
}
