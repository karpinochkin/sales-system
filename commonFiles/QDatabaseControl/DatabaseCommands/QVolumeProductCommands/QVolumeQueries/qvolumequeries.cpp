#include "qvolumequeries.h"

const QString QVolumeQueries::TABLE = "tbl_volumeProduct";
const QString QVolumeQueries::ID = "id_volumeProduct";
const QString QVolumeQueries::NAME = "name_volumeProduct";
const QString QVolumeQueries::VOLUME = "volume_volumeProduct";
const QString QVolumeQueries::DESCRIPTION = "description_volumeProduct";
const QString QVolumeQueries::UNIT = "units_volumeProduct";

QVolumeQueries::QVolumeQueries()
{

}

QString QVolumeQueries::createTable_text()
{
    QString text = "CREATE TABLE IF NOT EXISTS "
            + TABLE + " ("
            + ID + " INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,"
            + NAME + " text NOT NULL,"
            + VOLUME + " INTEGER NOT NULL,"
            + DESCRIPTION + " text NOT NULL,"
            + UNIT + " INTEGER NOT NULL);";
    return text;
}

QString QVolumeQueries::getTableName()
{
    return TABLE;
}

QString QVolumeQueries::getColumnName_ID()
{
    return ID;
}

QString QVolumeQueries::getColumnName_Name()
{
    return NAME;
}

QString QVolumeQueries::getVolumes_text()
{
    QString text = "SELECT "
            + ID + ", "
            + NAME + ", "
            + VOLUME + ", "
            + DESCRIPTION + ", "
            + UNIT + " "
            + " FROM "
            + TABLE + ";";
    return text;
}


QString QVolumeQueries::get_text(int idVolume)
{
    QString text = "SELECT "
            + ID + ", "
            + NAME + ", "
            + VOLUME + ", "
            + DESCRIPTION + ", "
            + UNIT + " "
            + " FROM "
            + TABLE
            + " WHERE "
            + ID + " = '"
            + QString::number(idVolume) + "';";
    return text;
}

QString QVolumeQueries::add_text(int id, const QVolumeProduct &volume)
{
    QString text = "INSERT INTO "
            + TABLE + " ("
            + ID + ", "
            + NAME + ", "
            + VOLUME + ", "
            + DESCRIPTION + ", "
            + UNIT + ") "

            + " VALUES ('"
            + QString::number(id) + "','"
            + volume.name + "','"
            + QString::number(volume.volume) + "','"
            + volume.description + "','"
            + volume.units + "');";
    return text;
}

QString QVolumeQueries::edit_text(const QVolumeProduct &volume)
{
    QString text = "UPDATE "
            + TABLE

            + " SET "
            + NAME + " = '"
            + volume.name + "',"

            + VOLUME + " = '"
            + QString::number(volume.volume) + "',"

            + DESCRIPTION + " = '"
            + volume.description + "',"

            + UNIT + " = '"
            + volume.units + "' "

            + " WHERE "
            + ID + " = '"
            + QString::number(volume.id) + "';";
    return text;
}

QString QVolumeQueries::getId_text(const QVolumeProduct &volume)
{
    QString text = "SELECT "
            + ID
            + " FROM "
            + TABLE
            + " WHERE "
            + NAME + " = '"
            + volume.name + "' "
            + " AND "
            + VOLUME + " = '"
            + QString::number(volume.volume) + "' "
            + " AND "
            + DESCRIPTION + " = '"
            + volume.description + "' "
            + " AND "
            + UNIT + " = '"
            + volume.units + "';";
    return text;
}

QString QVolumeQueries::remove_text(int id, const QString &name)
{
    QString text = "DELETE FROM "
            + TABLE
            + " WHERE "
            + ID + " = '" + QString::number(id) + "'"
            + " AND "
            + NAME + " = '" + name + "';";
    return text;
}
