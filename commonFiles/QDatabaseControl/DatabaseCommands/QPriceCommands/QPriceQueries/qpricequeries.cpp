#include "qpricequeries.h"

const QString QPriceQueries::TABLE = "tbl_price";
const QString QPriceQueries::ID = "id_price";
const QString QPriceQueries::VALUE = "value_price";
const QString QPriceQueries::START_TIME = "startTime_price";
const QString QPriceQueries::DESCRIPTION = "description_price";
const QString QPriceQueries::ID_PRODUCT = "price_id_product";
const QString QPriceQueries::ID_VOLUME = "price_id_volumeProduct";
const QString QPriceQueries::ID_CATEGORY = "price_id_productСategory";

QPriceQueries::QPriceQueries()
{

}

QString QPriceQueries::createTable_text()
{
    QString text = "CREATE TABLE IF NOT EXISTS "
            + TABLE + " ("
            + ID + " INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,"
            + VALUE + " DECIMAL(10,2) NOT NULL,"
            + START_TIME + " DATETIME NOT NULL,"
            + DESCRIPTION + " text NOT NULL,"
            + ID_PRODUCT + " INTEGER  NOT NULL,"
            + ID_VOLUME + " INTEGER  NOT NULL,"
            + ID_CATEGORY + " INTEGER  NOT NULL);";
    return text;
}

QString QPriceQueries::getTableName()
{
    return TABLE;
}

QString QPriceQueries::getColumnName_ID()
{
    return ID;
}

QString QPriceQueries::getPrices_text()
{
    QString text = "SELECT "
            + ID + ", "
            + VALUE + ", "
            + START_TIME + ", "
            + DESCRIPTION + ", "
            + ID_PRODUCT + ", "
            + ID_VOLUME + ", "
            + ID_CATEGORY + " "
            + " FROM "
            + TABLE + ";";
    return text;
}

QString QPriceQueries::get_text(int idPrice)
{
    QString text = "SELECT "
            + ID + ", "
            + VALUE + ", "
            + START_TIME + ", "
            + DESCRIPTION + ", "
            + ID_PRODUCT + ", "
            + ID_VOLUME + ", "
            + ID_CATEGORY + " "
            + " FROM "
            + TABLE
            + " WHERE "
            + ID + " = '"
            + QString::number(idPrice) + "';";
    return text;
}

QString QPriceQueries::get_text(int idCategory, int idProduct, int idVolume)
{
    QString text = "SELECT "
            + ID + ", "
            + VALUE + ", "
            + START_TIME + ", "
            + DESCRIPTION + ", "
            + ID_PRODUCT + ", "
            + ID_VOLUME + ", "
            + ID_CATEGORY + " "
            + " FROM "
            + TABLE
            + " WHERE "
            + ID_CATEGORY + " = '"
            + QString::number(idCategory) + "' "
            + " AND "
            + ID_PRODUCT + " = '"
            + QString::number(idProduct) + "' "
            + " AND "
            + ID_VOLUME + " = '"
            + QString::number(idVolume) + "' "
            + " AND "
            + START_TIME + " <= '" + QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss") + "' "
            + " ORDER BY "
            + START_TIME + " desc;";
    return text;

}

QString QPriceQueries::getId_text(const QPrice &price)
{
    QString text = "SELECT "
            + ID
            + " FROM "
            + TABLE
            + " WHERE "
            + VALUE + " = '"
            + QString::number(price.value) + "' "
            + " AND "
            + START_TIME + " = '"
            + price.startDate.toString("yyyy-MM-dd hh:mm:ss") + "' "
            + " AND "
            + DESCRIPTION + " = '"
            + price.description + "' "
            + " AND "
            + ID_PRODUCT + " = '"
            + QString::number(price.idProduct) + "' "
            + " AND "
            + ID_VOLUME + " = '"
            + QString::number(price.idVolume) + "' "
            + " AND "
            + ID_CATEGORY + " = '"
            + QString::number(price.idProductCategory) + "';";
    return text;
}

QString QPriceQueries::add_text(int id, const QPrice &price)
{
    QString text = "INSERT INTO "
            + TABLE + "("
            + ID + ", "
            + VALUE + ", "
            + START_TIME + ", "
            + DESCRIPTION + ", "
            + ID_PRODUCT + ", "
            + ID_VOLUME + ", "
            + ID_CATEGORY
            + ") VALUES ('"
            + QString::number(id) + "','"
            + QString::number(price.value) + "','"
            + price.startDate.toString("yyyy-MM-dd hh:mm:ss") + "','"
            + price.description + "','"
            + QString::number(price.idProduct) + "','"
            + QString::number(price.idVolume) + "','"
            + QString::number(price.idProductCategory) + "');";
    return text;
}

QString QPriceQueries::edit_text(const QPrice &price)
{
    QString text = "UPDATE "
            + TABLE
            + " SET "
            + VALUE + " = '"
            + QString::number(price.value) + "',"
            + START_TIME + " = '"
            + price.startDate.toString("yyyy-MM-dd hh:mm:ss") + "',"
            + DESCRIPTION + " = '"
            + price.description + "',"
            + ID_PRODUCT + " = '"
            + QString::number(price.idProduct) + "',"
            + ID_VOLUME + " = '"
            + QString::number(price.idVolume) + "',"
            + ID_CATEGORY + " = '"
            + QString::number(price.idProductCategory) + "' "
            + " WHERE "
            + ID + " = '"
            + QString::number(price.id) + "';";
    return text;
}
