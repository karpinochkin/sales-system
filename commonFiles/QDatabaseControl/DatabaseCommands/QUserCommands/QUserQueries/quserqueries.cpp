#include "quserqueries.h"

const QString QUserQueries::MAIN_TABLE = "tbl_user";
const QString QUserQueries::ID = "id_user";
const QString QUserQueries::LOGIN = "login_user";
const QString QUserQueries::PASSWORD = "password_user";
const QString QUserQueries::NAME = "name_user";
const QString QUserQueries::PATRONYMIC = "patronymic_user";
const QString QUserQueries::SURNAME = "surname_user";

QUserQueries::QUserQueries()
{

}

QString QUserQueries::createTable_text()
{
    QString text = "CREATE TABLE IF NOT EXISTS "
            + MAIN_TABLE + " ("
            + ID + " INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,"
            + LOGIN + " text NOT NULL,"
            + PASSWORD + " text,"
            + NAME + " text NOT NULL,"
            + PATRONYMIC + " text NOT NULL,"
            + SURNAME + " text NOT NULL);";
    return text;
}

QString QUserQueries::getTableName()
{
    return MAIN_TABLE;
}

QString QUserQueries::getColumnName_ID()
{
    return ID;
}

QString QUserQueries::getColumnName_Name()
{
    return NAME;
}

QString QUserQueries::getColumnName_Login()
{
    return LOGIN;
}

QString QUserQueries::getUsers_QueryText()
{
    QString text = "SELECT "

            + ID + ", "
            + LOGIN + ", "
            + PASSWORD + ", "
            + NAME + ", "
            + PATRONYMIC + ", "
            + SURNAME

            + " FROM "
            + MAIN_TABLE + ";";
    return  text;
}

QString QUserQueries::get_QueryText(int idUser)
{
    QString text = "SELECT "

            + ID + ", "
            + LOGIN + ", "
            + PASSWORD + ", "
            + NAME + ", "
            + PATRONYMIC + ", "
            + SURNAME

            + " FROM "
            + MAIN_TABLE

            + " WHERE "
            + ID
            + " = '"
            + QString::number(idUser)
            + "';";

    return  text;
}

QString QUserQueries::get_QueryText(const QString &login)
{
    QString text = "SELECT "

            + ID + ", "
            + LOGIN + ", "
            + PASSWORD + ", "
            + NAME + ", "
            + PATRONYMIC + ", "
            + SURNAME

            + " FROM "
            + MAIN_TABLE

            + " WHERE "
            + LOGIN
            + " = '"
            + login
            + "';";
    return text;
}

QString QUserQueries::getId_QueryText(QUser &user)
{
    QString text = "SELECT "
            + ID

            + " FROM "
            + MAIN_TABLE

            + " WHERE "
            + LOGIN + " = '"
            + user.login + "' "

            + " AND "
            + PASSWORD + " = '"
            + user.password + "' "

            + " AND "
            + NAME + " = '"
            + user.name + "' "

            + " AND "
            + PATRONYMIC + " = '"
            + user.patronymic + "' "

            + " AND "
            + SURNAME + " = '"
            + user.surname + "';";
    return text;
}

QString QUserQueries::add_QueryText(int id, const QUser &user)
{
    QString text = "INSERT INTO "
            + MAIN_TABLE + " ("
            + ID + ", "
            + LOGIN + ", "
            + PASSWORD + ", "
            + NAME + ", "
            + PATRONYMIC + ", "
            + SURNAME + ") "

            + " VALUES ('"
            + QString::number(id) + "','"
            + user.login + "','"
            + user.password + "','"
            + user.name + "','"
            + user.patronymic + "','"
            + user.surname + "');";
    return text;
}

QString QUserQueries::edit_QueryText(const QUser &user)
{
    QString text = "UPDATE "
            + MAIN_TABLE

            + " SET "
            + LOGIN + " = '"
            + user.login + "',"

            + PASSWORD + " = '"
            + user.password + "',"

            + NAME + " = '"
            + user.name + "',"

            + PATRONYMIC + " = '"
            + user.patronymic + "',"

            + SURNAME + " = '"
            + user.surname + "' "

            + " WHERE "
            + ID + " = '"
            + QString::number(user.id) + "';";
    return text;
}
