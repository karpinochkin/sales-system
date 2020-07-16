#include "qshiftqueries.h"

const QString QShiftQueries::TABLE = "tbl_shift";
const QString QShiftQueries::ID = "id_shift";
const QString QShiftQueries::OPEN_TIME = "openTime_shift";
const QString QShiftQueries::CLOSE_TIME = "closeTime_shift";
const QString QShiftQueries::IS_OPEN = "open_shift";
const QString QShiftQueries::IS_CLOSE = "close_shift";
const QString QShiftQueries::ID_USER = "shift_id_user";
const QString QShiftQueries::ID_POINT_SALE = "shift_id_pointSale";

QShiftQueries::QShiftQueries()
{

}

QString QShiftQueries::createTable_text()
{
    QString text = "CREATE TABLE IF not EXISTS "
            + TABLE + " ("
            + ID + " INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,"
            + OPEN_TIME + " DATETIME NOT NULL,"
            + CLOSE_TIME + " DATETIME NOT NULL,"
            + IS_OPEN + " INTEGER NOT NULL,"
            + IS_CLOSE + " INTEGER NOT NULL,"
            + ID_USER + " INTEGER NOT NULL,"
            + ID_POINT_SALE + " INTEGER NOT NULL);";
    return text;
}

QString QShiftQueries::getTableName()
{
    return TABLE;
}

QString QShiftQueries::getColumnName_ID()
{
    return ID;
}

QString QShiftQueries::getShifts_text()
{
    QString text = "SELECT "
            + ID + ", "
            + OPEN_TIME + ", "
            + CLOSE_TIME + ", "
            + IS_OPEN + ", "
            + IS_CLOSE + ", "
            + ID_USER + ", "
            + ID_POINT_SALE + " "
            + " FROM "
            + TABLE + ";";
    return text;
}

QString QShiftQueries::get_text(int idShift)
{
    QString text = "SELECT "
            + ID + ", "
            + OPEN_TIME + ", "
            + CLOSE_TIME + ", "
            + IS_OPEN + ", "
            + IS_CLOSE + ", "
            + ID_USER + ", "
            + ID_POINT_SALE + " "
            + " FROM "
            + TABLE
            + " WHERE "
            + ID + " = '" + QString::number(idShift) + "';";
    return text;
}

QString QShiftQueries::get_text(int idUser, int idPointSale)
{
    QString text = "SELECT "
            + ID + ", "
            + OPEN_TIME + ", "
            + CLOSE_TIME + ", "
            + IS_OPEN + ", "
            + IS_CLOSE + ", "
            + ID_USER + ", "
            + ID_POINT_SALE + " "
            + " FROM "
            + TABLE
            + " WHERE "
            + ID_USER + " = '" + QString::number(idUser) + "' "
            + " AND "
            + ID_POINT_SALE + " = '" + QString::number(idPointSale) + "';";
    return text;
}

QString QShiftQueries::getOpenedShift_text(int idUser, int idPointSale)
{
    QString text = "SELECT "
            + ID + ", "
            + OPEN_TIME + ", "
            + CLOSE_TIME + ", "
            + IS_OPEN + ", "
            + IS_CLOSE + ", "
            + ID_USER + ", "
            + ID_POINT_SALE + " "
            + " FROM "
            + TABLE
            + " WHERE "
            + ID_USER + " = '" + QString::number(idUser) + "' "
            + " AND "
            + ID_POINT_SALE + " = '" + QString::number(idPointSale) + "' "
            + " AND "
            + IS_OPEN + " = '" + QString::number(true) + "' "
            + " AND "
            + IS_CLOSE + " = '" + QString::number(false) + "';";
    return text;
}

QString QShiftQueries::getId_text(const QShift &shift)
{
    QString text = "SELECT "
            + ID
            + " FROM "
            + TABLE
            + " WHERE "
            + OPEN_TIME + " = '" + shift.openTime.toString("yyyy-MM-dd hh:mm:ss") + "' "
            + " AND "
            + CLOSE_TIME + " = '" +  shift.closeTime.toString("yyyy-MM-dd hh:mm:ss") + "' "
            + " AND "
            + IS_OPEN + " = '" + QString::number(shift.open) + "' "
            + " AND "
            + IS_CLOSE + " = '" + QString::number(shift.close) + "' "
            + " AND "
            + ID_USER + " = '" + QString::number(shift.idUser) + "' "
            + " AND "
            + ID_POINT_SALE + " = '" + QString::number(shift.idPointSale) + "';";
    return text;
}

QString QShiftQueries::add_text(int id, const QShift &shift)
{
    QString text = "INSERT INTO "
            + TABLE + " ("
            + ID + ", "
            + OPEN_TIME + ", "
            + CLOSE_TIME + ", "
            + IS_OPEN + ", "
            + IS_CLOSE + ", "
            + ID_USER + ", "
            + ID_POINT_SALE
            + ") VALUES ('"
            + QString::number(id) + "','"
            + shift.openTime.toString("yyyy-MM-dd hh:mm:ss") + "','"
            + shift.closeTime.toString("yyyy-MM-dd hh:mm:ss") + "','"
            + QString::number(shift.open) + "','"
            + QString::number(shift.close) + "','"
            + QString::number(shift.idUser) + "','"
            + QString::number(shift.idPointSale) + "');";
    return text;
}

QString QShiftQueries::edit_text(const QShift &shift)
{
    QString text = "UPDATE "
            + TABLE
            + " SET "
            + OPEN_TIME + " = '" + shift.openTime.toString("yyyy-MM-dd hh:mm:ss") + "',"
            + CLOSE_TIME + " = '" + shift.closeTime.toString("yyyy-MM-dd hh:mm:ss") + "',"
            + IS_OPEN + " = '" + QString::number(shift.open) + "',"
            + IS_CLOSE + " = '" + QString::number(shift.close) + "',"
            + ID_USER + " = '" + QString::number(shift.idUser) + "',"
            + ID_POINT_SALE + " = '" + QString::number(shift.idPointSale) + "' "
            + " WHERE "
            + ID + " = '" + QString::number(shift.id) + "';";
    return text;
}
