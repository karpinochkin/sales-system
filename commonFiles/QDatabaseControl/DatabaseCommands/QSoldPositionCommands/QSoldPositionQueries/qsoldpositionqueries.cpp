#include "qsoldpositionqueries.h"

const QString QSoldPositionQueries::TABLE = "tbl_soldPosition";
const QString QSoldPositionQueries::ID = "id_soldPosition";
const QString QSoldPositionQueries::ID_USER = "soldPosition_id_user";
const QString QSoldPositionQueries::COUNT = "count_soldPosition";
const QString QSoldPositionQueries::ID_PRODUCT = "soldPosition_id_product";
const QString QSoldPositionQueries::ID_TYPE = "soldPosition_id_typeProduct";
const QString QSoldPositionQueries::ID_PRICE = "soldPosition_id_price";
const QString QSoldPositionQueries::ID_VOLUME = "soldPosition_id_volumeProduct";
const QString QSoldPositionQueries::ID_RECEIPT = "soldPosition_id_receipt";
const QString QSoldPositionQueries::ID_POINT_SALE = "soldPosition_id_pointSale";
const QString QSoldPositionQueries::NUMBER_IN_RECEIPT = "soldPosition_numberInReceipt";
const QString QSoldPositionQueries::DATE = "date_soldPosition";

QSoldPositionQueries::QSoldPositionQueries()
{

}

QString QSoldPositionQueries::createTable_text()
{
    QString text = "CREATE TABLE IF NOT EXISTS "
            + TABLE + " ("
            + ID + " INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,"
            + ID_USER + " INTEGER NOT NULL,"
            + COUNT + "  INTEGER NOT NULL,"
            + ID_PRODUCT + "  INTEGER NOT NULL,"
            + ID_TYPE + "  INTEGER NOT NULL,"
            + ID_PRICE + "  INTEGER NOT NULL,"
            + ID_VOLUME + "  INTEGER NOT NULL,"
            + ID_RECEIPT + "  INTEGER NOT NULL,"
            + ID_POINT_SALE + "  INTEGER NOT NULL,"
            + NUMBER_IN_RECEIPT + "  INTEGER NOT NULL,"
            + DATE + " DATETIME NOT NULL);";
    return text;
}

QString QSoldPositionQueries::getTableName()
{
    return TABLE;
}

QString QSoldPositionQueries::getColumnName_ID()
{
    return ID;
}

QString QSoldPositionQueries::remove_text(int idSoldPosition)
{
    QString text = "DELETE FROM "
            + TABLE
            + " WHERE "
            + ID + " = '"
            + QString::number(idSoldPosition) + "';";
    return text;
}

QString QSoldPositionQueries::getSoldPositions_text()
{
    QString text = "SELECT "
            + ID + ", "
            + ID_USER + ", "
            + COUNT + ", "
            + ID_PRODUCT + ", "
            + ID_TYPE + ", "
            + ID_PRICE + ", "
            + ID_VOLUME + ", "
            + ID_RECEIPT + ", "
            + ID_POINT_SALE + ", "
            + NUMBER_IN_RECEIPT + ", "
            + DATE + " "
            + " FROM "
            + TABLE + ";";
    return text;
}

QString QSoldPositionQueries::getSoldPositions_text(QDateTime startDate, QDateTime endDate)
{
    QString text = "SELECT "
            + ID + ", "
            + ID_USER + ", "
            + COUNT + ", "
            + ID_PRODUCT + ", "
            + ID_TYPE + ", "
            + ID_PRICE + ", "
            + ID_VOLUME + ", "
            + ID_RECEIPT + ", "
            + ID_POINT_SALE + ", "
            + NUMBER_IN_RECEIPT + ", "
            + DATE + " "
            + " FROM "
            + TABLE
            + " WHERE "
            + DATE + " < '" + endDate.toString("yyyy-MM-dd hh:mm:ss") + "'"
            + " AND "
            + DATE + " > '" + startDate.toString("yyyy-MM-dd hh:mm:ss") + "';";
    return text;
}

QString QSoldPositionQueries::getSoldPositions_text(int idReceipt)
{
    QString text = "SELECT "
            + ID + ", "
            + ID_USER + ", "
            + COUNT + ", "
            + ID_PRODUCT + ", "
            + ID_TYPE + ", "
            + ID_PRICE + ", "
            + ID_VOLUME + ", "
            + ID_RECEIPT + ", "
            + ID_POINT_SALE + ", "
            + NUMBER_IN_RECEIPT + ", "
            + DATE + " "
            + " FROM "
            + TABLE
            + " WHERE "
            + ID_RECEIPT + " = '"
            + QString::number(idReceipt) + "';";
    return text;
}

QString QSoldPositionQueries::getSoldPositionsForProduct_text(int idProduct)
{
    QString text = "SELECT "
            + ID + ", "
            + ID_USER + ", "
            + COUNT + ", "
            + ID_PRODUCT + ", "
            + ID_TYPE + ", "
            + ID_PRICE + ", "
            + ID_VOLUME + ", "
            + ID_RECEIPT + ", "
            + ID_POINT_SALE + ", "
            + NUMBER_IN_RECEIPT + ", "
            + DATE + " "
            + " FROM "
            + TABLE
            + " WHERE "
            + ID_PRODUCT + " = '"
            + QString::number(idProduct) + "';";
    return text;
}

QString QSoldPositionQueries::getSoldPositionsForProduct_text(int idProduct,
                                                              QDateTime startDate,
                                                              QDateTime endDate)
{
    QString text = "SELECT "
            + ID + ", "
            + ID_USER + ", "
            + COUNT + ", "
            + ID_PRODUCT + ", "
            + ID_TYPE + ", "
            + ID_PRICE + ", "
            + ID_VOLUME + ", "
            + ID_RECEIPT + ", "
            + ID_POINT_SALE + ", "
            + NUMBER_IN_RECEIPT + ", "
            + DATE + " "
            + " FROM "
            + TABLE
            + " WHERE "
            + ID_PRODUCT + " = '"
            + QString::number(idProduct) + "'"
            + " AND "
            + DATE + " < '" + endDate.toString("yyyy-MM-dd hh:mm:ss") + "'"
            + " AND "
            + DATE + " > '" + startDate.toString("yyyy-MM-dd hh:mm:ss") + "';";
    return text;
}

QString QSoldPositionQueries::getSoldPositionsForPointSale_text(int idPointSale)
{
    QString text = "SELECT "
            + ID + ", "
            + ID_USER + ", "
            + COUNT + ", "
            + ID_PRODUCT + ", "
            + ID_TYPE + ", "
            + ID_PRICE + ", "
            + ID_VOLUME + ", "
            + ID_RECEIPT + ", "
            + ID_POINT_SALE + ", "
            + NUMBER_IN_RECEIPT + ", "
            + DATE + " "
            + " FROM "
            + TABLE
            + " WHERE "
            + ID_POINT_SALE + " = '"
            + QString::number(idPointSale) + "';";
    return text;
}

QString QSoldPositionQueries::getSoldPositionsForPointSale_text(int idPointSale,
                                                                QDateTime startDate,
                                                                QDateTime endDate)
{
    QString text = "SELECT "
            + ID + ", "
            + ID_USER + ", "
            + COUNT + ", "
            + ID_PRODUCT + ", "
            + ID_TYPE + ", "
            + ID_PRICE + ", "
            + ID_VOLUME + ", "
            + ID_RECEIPT + ", "
            + ID_POINT_SALE + ", "
            + NUMBER_IN_RECEIPT + ", "
            + DATE + " "
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

QString QSoldPositionQueries::getSoldPositionsForUser_text(int idUser)
{
    QString text = "SELECT "
            + ID + ", "
            + ID_USER + ", "
            + COUNT + ", "
            + ID_PRODUCT + ", "
            + ID_TYPE + ", "
            + ID_PRICE + ", "
            + ID_VOLUME + ", "
            + ID_RECEIPT + ", "
            + ID_POINT_SALE + ", "
            + NUMBER_IN_RECEIPT + ", "
            + DATE + " "
            + " FROM "
            + TABLE
            + " WHERE "
            + ID_USER + " = '"
            + QString::number(idUser) + "';";
    return text;
}

QString QSoldPositionQueries::getSoldPositionsForUser_text(int idUser, QDateTime startDate, QDateTime endDate)
{
    QString text = "SELECT "
            + ID + ", "
            + ID_USER + ", "
            + COUNT + ", "
            + ID_PRODUCT + ", "
            + ID_TYPE + ", "
            + ID_PRICE + ", "
            + ID_VOLUME + ", "
            + ID_RECEIPT + ", "
            + ID_POINT_SALE + ", "
            + NUMBER_IN_RECEIPT + ", "
            + DATE + " "
            + " FROM "
            + TABLE
            + " WHERE "
            + ID_USER + " = '"
            + QString::number(idUser) + "'"
            + " AND "
            + DATE + " < '" + endDate.toString("yyyy-MM-dd hh:mm:ss") + "'"
            + " AND "
            + DATE + " > '" + startDate.toString("yyyy-MM-dd hh:mm:ss") + "';";
    return text;
}

QString QSoldPositionQueries::add_text(int id, const QSoldPosition &soldPosition)
{
    QString text = "INSERT INTO "
            + TABLE + " ("
            + ID + ", "
            + ID_USER + ", "
            + COUNT + ", "
            + ID_PRODUCT + ", "
            + ID_TYPE + ", "
            + ID_PRICE + ", "
            + ID_VOLUME + ", "
            + ID_RECEIPT + ", "
            + ID_POINT_SALE + ", "
            + NUMBER_IN_RECEIPT + ", "
            + DATE
            + ") VALUES ('"
            + QString::number(id) + "','"
            + QString::number(soldPosition.idUser) + "','"
            + QString::number(soldPosition.count) + "','"
            + QString::number(soldPosition.idProduct) + "','"
            + QString::number(soldPosition.idTypeProduct) + "','"
            + QString::number(soldPosition.idPrice) + "','"
            + QString::number(soldPosition.idVolumeProduct) + "','"
            + QString::number(soldPosition.idReceipt) + "','"
            + QString::number(soldPosition.idPointSale) + "','"
            + QString::number(soldPosition.numberInReceipt) + "','"
            + soldPosition.date.toString("yyyy-MM-dd hh:mm:ss") + "');";
    return text;
}

QString QSoldPositionQueries::edit_text(const QSoldPosition &soldPosition)
{
    QString text = "UPDATE "
            + TABLE
            + " SET "
            + ID_USER + " = '" + QString::number(soldPosition.idUser) + "',"
            + COUNT + " = '" + QString::number(soldPosition.count) + "',"
            + ID_PRODUCT + " = '" + QString::number(soldPosition.idProduct) + "',"
            + ID_TYPE + " = '" + QString::number(soldPosition.idTypeProduct) + "',"
            + ID_PRICE + " = '" + QString::number(soldPosition.idPrice) + "',"
            + ID_VOLUME + " = '" + QString::number(soldPosition.idVolumeProduct) + "',"
            + ID_RECEIPT + " = '" + QString::number(soldPosition.idReceipt) + "',"
            + ID_POINT_SALE + " = '" + QString::number(soldPosition.idPointSale) + "',"
            + NUMBER_IN_RECEIPT + " = '" + QString::number(soldPosition.numberInReceipt) + "',"
            + DATE + " = '" + soldPosition.date.toString("yyyy-MM-dd hh:mm:ss") + "' "
            + " WHERE "
            + ID + " = '" + QString::number(soldPosition.id) + "';";

    return text;
}

QString QSoldPositionQueries::get_text(int idSoldPosition)
{
    QString text = "SELECT "
            + ID + ", "
            + ID_USER + ", "
            + COUNT + ", "
            + ID_PRODUCT + ", "
            + ID_TYPE + ", "
            + ID_PRICE + ", "
            + ID_VOLUME + ", "
            + ID_RECEIPT + ", "
            + ID_POINT_SALE + ", "
            + NUMBER_IN_RECEIPT + ", "
            + DATE + " "
            + " FROM "
            + TABLE
            + " WHERE "
            + ID + " = '"
            + QString::number(idSoldPosition) + "';";
    return text;
}

QString QSoldPositionQueries::getId_text(const QSoldPosition &soldPosition)
{
    QString text = "SELECT "
            + ID
            + " FROM "
            + TABLE
            + " WHERE "
            + ID_USER + " = '" + QString::number(soldPosition.idUser) + "' "
            + " AND "
            + COUNT + " = '" + QString::number(soldPosition.count) + "' "
            + " AND "
            + ID_PRODUCT + " = '" + QString::number(soldPosition.idProduct) + "' "
            + " AND "
            + ID_TYPE + " = '" + QString::number(soldPosition.idTypeProduct) + "' "
            + " AND "
            + ID_PRICE + " = '" + QString::number(soldPosition.idPrice) + "' "
            + " AND "
            + ID_VOLUME + " = '" + QString::number(soldPosition.idVolumeProduct) + "' "
            + " AND "
            + ID_RECEIPT + " = '" + QString::number(soldPosition.idReceipt) + "' "
            + " AND "
            + ID_POINT_SALE + " = '" + QString::number(soldPosition.idPointSale) + "' "
            + " AND "
            + NUMBER_IN_RECEIPT + " = '" + QString::number(soldPosition.numberInReceipt) + "' "
            + " AND "
            + DATE + " = '" + soldPosition.date.toString("yyyy-MM-dd hh:mm:ss") + "';";
    return text;
}

QString QSoldPositionQueries::getIdWithoutReceipt_text(const QSoldPosition &soldPosition)
{
    QString text = "SELECT "
            + ID
            + " FROM "
            + TABLE
            + " WHERE "
            + ID_USER + " = '" + QString::number(soldPosition.idUser) + "' "
            + " AND "
            + COUNT + " = '" + QString::number(soldPosition.count) + "' "
            + " AND "
            + ID_PRODUCT + " = '" + QString::number(soldPosition.idProduct) + "' "
            + " AND "
            + ID_TYPE + " = '" + QString::number(soldPosition.idTypeProduct) + "' "
            + " AND "
            + ID_PRICE + " = '" + QString::number(soldPosition.idPrice) + "' "
            + " AND "
            + ID_VOLUME + " = '" + QString::number(soldPosition.idVolumeProduct) + "' "
            + " AND "
            + ID_POINT_SALE + " = '" + QString::number(soldPosition.idPointSale) + "' "
            + " AND "
            + NUMBER_IN_RECEIPT + " = '" + QString::number(soldPosition.numberInReceipt) + "' "
            + " AND "
            + DATE + " = '" + soldPosition.date.toString("yyyy-MM-dd hh:mm:ss") + "';";
    return text;
}
