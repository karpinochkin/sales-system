#include "qreceiptqueries.h"

const QString QReceiptQueries::TABLE = "tbl_receipt";
const QString QReceiptQueries::ID = "id_receipt";
const QString QReceiptQueries::DATE = "date_receipt";
const QString QReceiptQueries::SUM = "sum_receipt";
const QString QReceiptQueries::ID_POINT_SALE = "receipt_id_pointSale";
const QString QReceiptQueries::ID_SHIFT = "receipt_id_shift";

QReceiptQueries::QReceiptQueries()
{

}

QString QReceiptQueries::createTable_text()
{
    QString text = "CREATE TABLE IF NOT EXISTS "
            + TABLE + " ("
            + ID + " INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,"
            + DATE + " DATETIME NOT NULL,"
            + SUM +  " DECIMAL(10,2) NOT NULL,"
            + ID_POINT_SALE + " INTEGER  NOT NULL,"
            + ID_SHIFT + " INTEGER  NOT NULL);";
    return text;
}

QString QReceiptQueries::getTableName()
{
    return TABLE;
}

QString QReceiptQueries::getColumnName_ID()
{
    return ID;
}

QString QReceiptQueries::getReceipts_text()
{
    QString text = "SELECT "
            + ID + ", "
            + DATE + ", "
            + SUM + ", "
            + ID_POINT_SALE + ", "
            + ID_SHIFT + " "
            + " FROM "
            + TABLE + ";";
    return text;
}

QString QReceiptQueries::getReceipts_text(QDateTime startDate, QDateTime endDate)
{
    QString text = "SELECT "
            + ID + ", "
            + DATE + ", "
            + SUM + ", "
            + ID_POINT_SALE + ", "
            + ID_SHIFT + " "
            + " FROM "
            + TABLE
            + " WHERE "
            + DATE + " < '" + endDate.toString("yyyy-MM-dd hh:mm:ss") + "'"
            + " AND "
            + DATE + " > '" + startDate.toString("yyyy-MM-dd hh:mm:ss") + "';";
    return text;
}

QString QReceiptQueries::getReceipts_text(int idShift)
{
    QString text = "SELECT "
            + ID + ", "
            + DATE + ", "
            + SUM + ", "
            + ID_POINT_SALE + ", "
            + ID_SHIFT + " "
            + " FROM "
            + TABLE
            + " WHERE "
            + ID_SHIFT + " = '"
            + QString::number(idShift) + "';";
    return text;
}

QString QReceiptQueries::getReceiptsForPointSale_text(int idPointSale)
{
    QString text = "SELECT "
            + ID + ", "
            + DATE + ", "
            + SUM + ", "
            + ID_POINT_SALE + ", "
            + ID_SHIFT + " "
            + " FROM "
            + TABLE
            + " WHERE "
            + ID_POINT_SALE + " = '"
            + QString::number(idPointSale) + "';";
    return text;
}

QString QReceiptQueries::getReceiptsForPointSaleByDateRange_text(int idPointSale, QDateTime startDate, QDateTime endDate)
{
    QString text = "SELECT "
            + ID + ", "
            + DATE + ", "
            + SUM + ", "
            + ID_POINT_SALE + ", "
            + ID_SHIFT + " "
            + " FROM "
            + TABLE
            + " WHERE "
            + ID_POINT_SALE + " = '"
            + QString::number(idPointSale) + "'"
            + " AND "
            + DATE + " < '" + endDate.toString("yyyy-MM-dd hh:mm:ss") + "'"
            + " AND "
            + DATE + " > '" + startDate.toString("yyyy-MM-dd hh:mm:ss") + "';";
    return text;
}

QString QReceiptQueries::get_text(int idReceipt)
{
    QString text = "SELECT "
            + ID + ", "
            + DATE + ", "
            + SUM + ", "
            + ID_POINT_SALE + ", "
            + ID_SHIFT + " "
            + " FROM "
            + TABLE
            + " WHERE "
            + ID + " = '"
            + QString::number(idReceipt) + "';";
    return text;
}

QString QReceiptQueries::add_text(int id, const QReceipt &receipt)
{
    QString text = "INSERT INTO "
            + TABLE + " ("
            + ID + ", "
            + DATE + ", "
            + SUM + ", "
            + ID_POINT_SALE + ", "
            + ID_SHIFT
            + ") VALUES ('"
            + QString::number(id) + "','"
            + receipt.dateTime.toString("yyyy-MM-dd hh:mm:ss") + "','"
            + QString::number(receipt.sum) + "','"
            + QString::number(receipt.idPointSale) + "','"
            + QString::number(receipt.idShift) + "');";
    return text;
}

QString QReceiptQueries::edit_text(const QReceipt &receipt)
{
    QString text = "UPDATE "
            + TABLE
            + " SET "
            + DATE + " = '"
            + receipt.dateTime.toString("yyyy-MM-dd hh:mm:ss") + "', "
            + SUM + " = '"
            + QString::number(receipt.sum) + "', "
            + ID_POINT_SALE + " = '"
            + QString::number(receipt.idPointSale) + "',"
            + ID_SHIFT + " = '"
            + QString::number(receipt.idShift) + "' "
            + " WHERE "
            + ID + " = '"
            + QString::number(receipt.id) + "';";
    return text;
}

QString QReceiptQueries::edit_text(int id, const QReceipt &receipt)
{
    QString text = "UPDATE "
            + TABLE
            + " SET "
            + ID + " = '" + QString::number(receipt.id) + "', "
            + DATE + " = '"
            + receipt.dateTime.toString("yyyy-MM-dd hh:mm:ss") + "', "
            + SUM + " = '"
            + QString::number(receipt.sum) + "', "
            + ID_POINT_SALE + " = '"
            + QString::number(receipt.idPointSale) + "',"
            + ID_SHIFT + " = '"
            + QString::number(receipt.idShift) + "' "
            + " WHERE "
            + ID + " = '" + QString::number(id) + "';";

    return text;
}

QString QReceiptQueries::getId_text(const QReceipt &receipt)
{
    QString text = "SELECT "
            + ID
            + " FROM "
            + TABLE
            + " WHERE "
            + DATE + " = '"
            + receipt.dateTime.toString("yyyy-MM-dd hh:mm:ss") + "' "
            + " AND "
            + SUM + " = '" + QString::number(receipt.sum) + "' "
            + " AND "
            + ID_POINT_SALE + " = '" + QString::number(receipt.idPointSale) + "' "
            + " AND "
            + ID_SHIFT + " = '" + QString::number(receipt.idShift) + "';";
    return text;
}


