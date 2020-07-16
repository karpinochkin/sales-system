#include "qproductqueries.h"

const QString QProductQueries::TABLE = "tbl_product";
const QString QProductQueries::ID = "id_product";
const QString QProductQueries::NAME = "name_product";
const QString QProductQueries::DESCRIPTION = "description_product";
const QString QProductQueries::RED = "red_product";
const QString QProductQueries::GREEN = "green_product";
const QString QProductQueries::BLUE = "blue_product";
const QString QProductQueries::PICTURE_ID = "product_id_pictureProduct";
const QString QProductQueries::HASH = "hash_product";

QProductQueries::QProductQueries()
{

}

QString QProductQueries::getTableName()
{
    return TABLE;
}

QString QProductQueries::getColumnName_ID()
{
    return ID;
}

QString QProductQueries::clear_text()
{
    QString text = "DELETE FROM "
            + TABLE + ";";
    return text;
}

QString QProductQueries::createTable_text()
{
    QString text = "CREATE TABLE IF NOT EXISTS "
            + TABLE + "("
            + ID + " INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,"
            + NAME + " text NOT NULL,"
            + DESCRIPTION + " text NOT NULL,"
            + RED + " INTEGER NOT NULL,"
            + GREEN + " INTEGER NOT NULL,"
            + BLUE + " INTEGER NOT NULL,"
            + PICTURE_ID + " INTEGER,"
            + HASH + " text);";
    return text;
}

QString QProductQueries::getProducts_text()
{
    QString text = "SELECT "
            + ID + ", "
            + NAME + ", "
            + DESCRIPTION + ", "
            + RED + ", "
            + GREEN + ", "
            + BLUE + ", "
            + PICTURE_ID + ", "
            + HASH + " "
            + " FROM "
            + TABLE + ";";
    return text;
}

QString QProductQueries::get_text(int idProduct)
{
    QString text = "SELECT "
            + ID + ", "
            + NAME + ", "
            + DESCRIPTION + ", "
            + RED + ", "
            + GREEN + ", "
            + BLUE + ", "
            + PICTURE_ID + ", "
            + HASH + " "
            + " FROM "
            + TABLE
            + " WHERE "
            + ID + " = '"
            + QString::number(idProduct) + "';";
    return text;
}

QString QProductQueries::getId_text(QProduct &product)
{
    QString text = "SELECT "
            + ID
            + " FROM "
            + TABLE
            + " WHERE "
            + NAME + " = '"
            + product.name + "' "

            + " AND "
            + DESCRIPTION + " = '"
            + product.description + "' "

            + " AND "
            + RED + " = '"
            + QString::number(product.color.red()) + "' "

            + " AND "
            + GREEN + " = '"
            + QString::number(product.color.green()) + "' "

            + " AND "
            + BLUE + " = '"
            + QString::number(product.color.blue()) + "' "

            + " AND "
            + PICTURE_ID + " = '"
            + QString::number(product.idPicture) + "' "

            + " AND "
            + HASH + " = '"
            + product.pictureHash + "';";
    return text;
}

QString QProductQueries::getAllID_text()
{
    QString text = "SELECT "
            + ID
            + " FROM "
            + TABLE + ";";
    return text;
}

QString QProductQueries::add_text(int id, QProduct &product)
{
    QString text = "INSERT INTO "
            + TABLE + " ("
            + ID + ", "
            + NAME + ", "
            + DESCRIPTION + ", "
            + RED + ", "
            + GREEN + ", "
            + BLUE + ", "
            + PICTURE_ID + ", "
            + HASH
            + " ) VALUES ('"
            + QString::number(id) + "','"
            + product.name + "','"
            + product.description + "','"
            + QString::number(product.color.red()) + "','"
            + QString::number(product.color.green()) + "','"
            + QString::number(product.color.blue()) + "','"
            + QString::number(product.idPicture) + "','"
            + product.pictureHash + "');";
    return  text;

}

QString QProductQueries::add_textEmptyPicture(int id, QProduct &product)
{
    QString text = "INSERT INTO "
            + TABLE + " ("
            + ID + ", "
            + NAME + ", "
            + DESCRIPTION + ", "
            + RED + ", "
            + GREEN + ", "
            + BLUE + ", "
            + HASH
            + " ) VALUES ('"
            + QString::number(id) + "','"
            + product.name + "','"
            + product.description + "','"
            + QString::number(product.color.red()) + "','"
            + QString::number(product.color.green()) + "','"
            + QString::number(product.color.blue()) + "','"
            + product.pictureHash + "');";
    return  text;
}

QString QProductQueries::edit_text(QProduct &product)
{
    QString text = "UPDATE "
            + TABLE
            + " SET "
            + NAME + " = '"
            + product.name + "', "
            + DESCRIPTION + " = '"
            + product.description + "', "
            + RED + " = '"
            + QString::number(product.color.red()) + "', "
            + GREEN + " = '"
            + QString::number(product.color.green()) + "', "
            + BLUE + " = '"
            + QString::number(product.color.blue()) + "', "
            + PICTURE_ID + " = '"
            + QString::number(product.idPicture) + "', "
            + HASH + " = '"
            + product.pictureHash + "' "
            + " WHERE "
            + ID + " = '"
            + QString::number(product.id) + "';";
    return text;

}

QString QProductQueries::edit_textEmptyPicture(QProduct &product)
{
    QString text = "UPDATE "
            + TABLE
            + " SET "
            + NAME + " = '"
            + product.name + "', "
            + DESCRIPTION + " = '"
            + product.description + "', "
            + RED + " = '"
            + QString::number(product.color.red()) + "', "
            + GREEN + " = '"
            + QString::number(product.color.green()) + "', "
            + BLUE + " = '"
            + QString::number(product.color.blue()) + "', "
            + HASH + " = '"
            + product.pictureHash + "' "
            + " WHERE "
            + ID + " = '"
            + QString::number(product.id) + "';";
    return text;
}
