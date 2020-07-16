#include "qusercommands.h"

using namespace DatabaseCommands;

QUserCommands::QUserCommands(QSqlDatabase *database, QObject *parent)
    :  QParentDatabaseCommands(database, parent)
{

}

bool QUserCommands::createTable()
{
    bool result = false;
    QSqlQuery *query = makeQuery(QUserQueries::createTable_text(),
                                 &result);
    if (result) {
        qDebug() << QUserQueries::getTableName() + " is created";
    }
    delete query;
    return result;
}

bool QUserCommands::clear()
{
    bool result = this->clearTable(QUserQueries::getTableName());
    return result;
}

QVector<QUser> QUserCommands::getUsers()
{
    QVector<QUser> output;
    bool result = false;
    QSqlQuery *query = makeQuery(QUserQueries::getUsers_QueryText(),
                                 &result);
    if(result) {
        QUser currentUser;
        while (query->next()) {
            this->commonGet(query, currentUser);

            output.push_back(currentUser);
        }
    }
    delete query;
    return output;
}

QUser QUserCommands::get(int idUser)
{
    QUser outputUser;
    bool result = false;
    QSqlQuery *query = makeQuery(QUserQueries::get_QueryText(idUser),
                                 &result);
    if(result) {
        if(query->next()) {
            this->commonGet(query, outputUser);
        }
    }
    delete query;
    return outputUser;
}

QUser QUserCommands::get(const QString &login)
{
    QUser outputUser;
    bool result = false;
    QSqlQuery *query = makeQuery(QUserQueries::get_QueryText(login),
                                 &result);
    if(result) {
        if(query->next()) {
            this->commonGet(query, outputUser);
        }
    }
    delete  query;
    return outputUser;
}

int QUserCommands::getId(QUser &user)
{
    int output = -1;
    bool result = false;
    QSqlQuery *query = makeQuery(QUserQueries::getId_QueryText(user),
                                 &result);
    if (result) {
        if (query->next()) {
            output = query->value(0).toInt();
        }
    }
    delete query;
    return output;
}

bool QUserCommands::remove(int id, const QString &name)
{
    DatabaseCommands::RemoveInformation obj;
    obj.id = id;
    obj.name = name;
    obj.tableName = QUserQueries::getTableName();
    obj.columnName_ID = QUserQueries::getColumnName_ID();
    obj.columnName_Name = QUserQueries::getColumnName_Login();

    bool result = QParentDatabaseCommands::remove(obj);
    return result;
}

int QUserCommands::add(QUser &user)
{
    int output = -1;
    int nextId = getNextId(QUserQueries::getTableName(),
                           QUserQueries::getColumnName_ID());
    bool result = false;
    QSqlQuery *query = makeQuery(QUserQueries::add_QueryText(nextId, user),
                                 &result);
    if(result) {
        output = this->getId(user);
    }

    delete query;
    return output;
}

int QUserCommands::add(int id, QUser &user)
{
    int output = -1;
    bool result = false;
    QSqlQuery *query = makeQuery(QUserQueries::add_QueryText(id, user),
                                 &result);
    if(result) {
        output = this->getId(user);
    }
    delete query;
    return output;
}

bool QUserCommands::edit(QUser &user)
{
    bool output = false;
    QSqlQuery *query = makeQuery(QUserQueries::edit_QueryText(user),
                                 &output);
    delete  query;
    return output;
}

void QUserCommands::commonGet(QSqlQuery *query, QUser &value)
{
    value.id = query->value(0).toInt();
    value.login = query->value(1).toString();
    value.password = query->value(2).toString();
    value.name = query->value(3).toString();
    value.patronymic = query->value(4).toString();
    value.surname = query->value(5).toString();
}
