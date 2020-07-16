#ifndef QUSERQUERIES_H
#define QUSERQUERIES_H

#include <QString>
#include "../commonFiles/SalesSystem/QUser/quser.h"
class QUserQueries
{
public:
    static QString createTable_text();
    static QString getTableName();
    static QString getColumnName_ID();
    static QString getColumnName_Name();
    static QString getColumnName_Login();
    static QString getUsers_QueryText();
    static QString get_QueryText(int idUser);
    static QString get_QueryText(const QString &login);
    static QString getId_QueryText(QUser &user);
    static QString add_QueryText(int id, const QUser &user);
    static QString edit_QueryText(const QUser &user);

private:
    QUserQueries();
    static const QString MAIN_TABLE;
    static const QString ID;
    static const QString LOGIN;
    static const QString PASSWORD;
    static const QString NAME;
    static const QString PATRONYMIC;
    static const QString SURNAME;

};

#endif // QUSERQUERIES_H
