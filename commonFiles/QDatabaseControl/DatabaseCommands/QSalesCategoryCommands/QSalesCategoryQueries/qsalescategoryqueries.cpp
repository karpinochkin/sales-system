#include "qsalescategoryqueries.h"

const QString QSalesCategoryQueries::TABLE = "tbl_productСategory";
const QString QSalesCategoryQueries::ID = "id_category";
const QString QSalesCategoryQueries::NAME = "name_category";
const QString QSalesCategoryQueries::DESCRIPTION = "description_category";
const QString QSalesCategoryQueries::RED = "red_category";
const QString QSalesCategoryQueries::GREEN = "green_category";
const QString QSalesCategoryQueries::BLUE = "blue_category";

QSalesCategoryQueries::QSalesCategoryQueries()
{

}

QString QSalesCategoryQueries::getTableName()
{
    return TABLE;
}

QString QSalesCategoryQueries::getColumnName_ID()
{
    return ID;
}

QString QSalesCategoryQueries::getColumnName_Name()
{
    return NAME;
}

QString QSalesCategoryQueries::createTable_text()
{
    QString text = "CREATE TABLE IF NOT EXISTS "
            + TABLE + " ("
            + ID + " INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,"
            + NAME + " text NOT NULL,"
            + DESCRIPTION + " text NOT NULL,"
            + RED + "  INTEGER NOT NULL,"
            + GREEN + " INTEGER NOT NULL,"
            + BLUE + " INTEGER NOT NULL);";
    return text;
}

QString QSalesCategoryQueries::get_QueryText(int idCategory)
{
    QString text = "SELECT "
            + ID + ", "
            + NAME + ", "
            + DESCRIPTION + ", "
            + RED + ", "
            + GREEN + ", "
            + BLUE + " "
            + " FROM "
            + TABLE
            + " WHERE "
            + ID + " = '"
            + QString::number(idCategory) + "';";
    return text;
}

QString QSalesCategoryQueries::getCategories_QueryText()
{
    QString text = "SELECT "
            + ID + ", "
            + NAME + ", "
            + DESCRIPTION + ", "
            + RED + ", "
            + GREEN + ", "
            + BLUE + " "
            + " FROM "
            + TABLE + ";";
    return text;
}

QString QSalesCategoryQueries::edit_QueryText(QSalesCategory &category)
{
    QString text = "UPDATE "
            + TABLE
            + " SET "
            + NAME + " = '"
            + category.name + "', "
            + DESCRIPTION + " = '"
            + category.description + "', "
            + RED + " = '"
            + QString::number(category.color.red()) + "', "
            + GREEN + " = '"
            + QString::number(category.color.green()) + "', "
            + BLUE + " = '"
            + QString::number(category.color.blue()) + "' "
            + " WHERE "
            + ID + " = '"
            + QString::number(category.id) + "';";
    return text;
}

QString QSalesCategoryQueries::add_QueryText(int id, QSalesCategory &category)
{
    QString text = "INSERT INTO "
            + TABLE + " ("
            + ID + ", "
            + NAME + ", "
            + DESCRIPTION + ", "
            + RED + ", "
            + GREEN + ", "
            + BLUE
            + ") VALUES ('"
            + QString::number(id) + "','"
            + category.name + "','"
            + category.description + "', '"
            + QString::number(category.color.red()) + "','"
            + QString::number(category.color.green()) + "','"
            + QString::number(category.color.blue()) + "');";
    return text;
}

QString QSalesCategoryQueries::getId_QueryText(QSalesCategory &category)
{
    QString text = "SELECT "
            + ID
            + " FROM "
            + TABLE
            + " WHERE "
            + NAME + " = '" + category.name + "' "
            + " AND "
            + DESCRIPTION + " = '" + category.description + "' "
            + " AND "
            + RED + " = '" + QString::number(category.color.red()) + "' "
            + " AND "
            + GREEN + " = '" + QString::number(category.color.green()) + "' "
            + " AND "
            + BLUE + " = '" + QString::number(category.color.blue()) + "';";
    return text;
}
