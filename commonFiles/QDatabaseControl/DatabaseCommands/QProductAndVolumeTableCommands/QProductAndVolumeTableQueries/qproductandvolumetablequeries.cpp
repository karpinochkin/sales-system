#include "qproductandvolumetablequeries.h"

QProductAndVolumeTableQueries::QProductAndVolumeTableQueries()
{

}

QString QProductAndVolumeTableQueries::createTable_text()
{
    QString textQuery = "CREATE TABLE IF NOT EXISTS tbl_product_volumeProduct ("
                "tbl_product_id_product INTEGER NOT NULL,"
                "tbl_volumeProduct_id_volumeProduct INTEGER NOT NULL);";
    return textQuery;
}

QString QProductAndVolumeTableQueries::getIdVolumes_text(int idProduct)
{
    QString textQuery = "select tbl_volumeProduct_id_volumeProduct"
                        " from tbl_product_volumeProduct "
                        "where tbl_product_id_product = '"
            + QString::number(idProduct) + "';";
    return textQuery;
}

QString QProductAndVolumeTableQueries::getIdProducts_text(int idVolume)
{
    QString textQuery = "select tbl_product_id_product from tbl_product_volumeProduct "
                        "where "
                        "tbl_volumeProduct_id_volumeProduct = '" + QString::number(idVolume) + "';";
    return textQuery;
}

QString QProductAndVolumeTableQueries::linkProduct(int idVolume, int idProduct)
{
    QString textQuery = "insert into tbl_product_volumeProduct (tbl_product_id_product,"
                        "tbl_volumeProduct_id_volumeProduct) "
                        "values ('" + QString::number(idProduct) + "','"
            + QString::number(idVolume) + "');";
    return textQuery;
}

QString QProductAndVolumeTableQueries::unlinkProducts(int idVolume)
{
    QString textQuery = "delete from tbl_product_volumeProduct "
                        "where tbl_volumeProduct_id_volumeProduct = '"
            + QString::number(idVolume) + "';";
    return textQuery;
}
