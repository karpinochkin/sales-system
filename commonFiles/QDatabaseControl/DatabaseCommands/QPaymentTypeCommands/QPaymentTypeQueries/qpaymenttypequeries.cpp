#include "qpaymenttypequeries.h"

const QString QPaymentTypeQueries::TABLE = "tbl_typeProduct";
const QString QPaymentTypeQueries::ID = "id_type";
const QString QPaymentTypeQueries::NAME = "name_type";
const QString QPaymentTypeQueries::DESCRIPTION = "description_type";

QPaymentTypeQueries::QPaymentTypeQueries()
{

}

QString QPaymentTypeQueries::createTable_text()
{
    QString text = "CREATE TABLE IF NOT EXISTS "
            + TABLE + " ("
            + ID + " INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,"
            + NAME + " text NOT NULL,"
            + DESCRIPTION + " text NOT NULL);";
    return text;
}

QString QPaymentTypeQueries::getTableName()
{
    return TABLE;
}

QString QPaymentTypeQueries::getColumnName_ID()
{
    return ID;
}

QString QPaymentTypeQueries::getColumnName_Name()
{
    return NAME;
}

QString QPaymentTypeQueries::getTypes_text()
{
    QString text = "SELECT "
            + ID + ", "
            + NAME + ", "
            + DESCRIPTION + " "
            + " FROM "
            + TABLE + ";";
    return text;
}

QString QPaymentTypeQueries::get_text(int idTypeProduct)
{
    QString text = "SELECT "
            + ID + ", "
            + NAME + ", "
            + DESCRIPTION + " "
            + " FROM "
            + TABLE
            + " WHERE "
            + ID + " = '"
            + QString::number(idTypeProduct)
            + "';";
    return text;
}

QString QPaymentTypeQueries::add_text(int id, const QPaymentType &type)
{
    QString text = "INSERT INTO "
            + TABLE + " ("
            + ID + ", "
            + NAME + ", "
            + DESCRIPTION + ") "
            + " VALUES ('"
            + QString::number(id) + "','"
            + type.name + "','"
            + type.description + "');";
    return text;
}

QString QPaymentTypeQueries::edit_text(const QPaymentType &type)
{
    QString text = "UPDATE "
            + TABLE
            + " SET "
            + NAME + " = '"
            + type.name + "', "
            + DESCRIPTION + " = '"
            + type.description + "' "
            + " WHERE "
            + ID + " = '"
            + QString::number(type.id) + "';";
    return text;

}

QString QPaymentTypeQueries::getId_text(const QPaymentType &type)
{
    QString text = "SELECT "
            + ID
            + " FROM "
            + TABLE
            + " WHERE "
            + NAME + "= '"
            + type.name + "' "
            + " AND "
            + DESCRIPTION + " = '"
            + type.description + "';";
    return text;
}

QString QPaymentTypeQueries::remove_text(int id, const QString &name)
{
    QString text = "DELETE FROM "
            + TABLE
            + " WHERE "
            + ID + " = '" + QString::number(id) + "'"
            + " AND "
            + NAME + " = '" + name + "';";
    return text;
}
