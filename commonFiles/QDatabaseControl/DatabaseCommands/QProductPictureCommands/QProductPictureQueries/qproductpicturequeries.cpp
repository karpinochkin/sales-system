#include "qproductpicturequeries.h"

const QString QProductPictureQueries::TABLE = "tbl_pictureProduct";
const QString QProductPictureQueries::ID = "id_picture";
const QString QProductPictureQueries::NAME = "name_picture";
const QString QProductPictureQueries::DATA = "data_picture";

QProductPictureQueries::QProductPictureQueries()
{

}

QString QProductPictureQueries::getTableName()
{
    return TABLE;
}

QString QProductPictureQueries::getColumnName_ID()
{
    return ID;
}

QString QProductPictureQueries::getColumnName_Name()
{
    return NAME;
}

QString QProductPictureQueries::createTable_text()
{
    QString text = "CREATE TABLE IF NOT EXISTS "
            + TABLE + " ("
            + ID + " INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,"
            + NAME + " text NOT NULL,"
            + DATA + " blob NOT NULL);";
    return text;
}

QString QProductPictureQueries::getPictures_text()
{
    QString text = "SELECT "
            + ID + ","
            + NAME + ","
            + DATA
            + " FROM "
            + TABLE + ";";
    return text;
}

QString QProductPictureQueries::get_text(int idPicture)
{
    QString text = "SELECT "
            + ID + ", "
            + NAME + ", "
            + DATA
            + " FROM "
            + TABLE
            + " WHERE "
            + ID + " = '"
            + QString::number(idPicture) + "';";
    return text;

}

QString QProductPictureQueries::add_text(int nextId, QString &name)
{
    QString text = "INSERT INTO "
            + TABLE + " ("
            + ID + ","
            + NAME + ","
            + DATA
            +") VALUES ('"
            + QString::number(nextId) + "','"
            + name + "',"
            + ":imageData);";
    return text;
}


QString QProductPictureQueries::getId_text(QString &name)
{
    QString text = "SELECT "
            + ID
            + " FROM "
            + TABLE
            + " WHERE "
            + " AND "
            + NAME + " = '" + name + "' "
            + " AND "
            + DATA + " = :imageData;";
    return text;
}

QString QProductPictureQueries::edit_text(int id, QString &name)
{
    QString text = "UPDATE "
            + TABLE
            + " SET "
            + NAME + " = '" + name + "',"
            + DATA + " = :imageData"
            + " WHERE "
            + ID + " = '" + QString::number(id)
            + "';";

    return text;
}

QString QProductPictureQueries::remove_text(int id, const QString &name)
{
    QString text = "DELETE FROM "
            + TABLE
            + " WHERE "
            + ID + " = '" + QString::number(id) + "'"
            + " AND "
            + NAME + " = '" + name + "';";
    return text;
}
