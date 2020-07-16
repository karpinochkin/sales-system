#include "qparentdatabasecommands.h"

using namespace DatabaseCommands;

QParentDatabaseCommands::QParentDatabaseCommands(QSqlDatabase *database, QObject *parent)
    : QObject(parent), currentDatabase(*database)
{
    mutexDataBase = new QMutex();
}

QParentDatabaseCommands::~QParentDatabaseCommands()
{
    delete  mutexDataBase;
}

QSqlQuery* QParentDatabaseCommands::makeQuery(const QString &textQuery, bool *result)
{
    QSqlQuery *query = execQuery(textQuery, result);

    if(!(*result)) {
        printTextError(query->lastError().text(), textQuery);
    }

    return  query;
}

QSqlQuery* QParentDatabaseCommands::makeQuery(const QString &textQuery, QString bindName,
                                        QVariant bindValue, bool *result)
{
    QSqlQuery *query = execQuery(textQuery, bindName, bindValue, result);

    if (!(*result)) {
        printTextError(query->lastError().text(), textQuery);
    }
    return query;
}


QSqlQuery *QParentDatabaseCommands::execQuery(const QString &textQuery, bool *result)
{
    QSqlQuery *Output;

    mutexDataBase->lock();
    Output = new QSqlQuery(currentDatabase);

    if (currentDatabase.isValid()) {
        if (!currentDatabase.isOpen()) {
            currentDatabase.open();
        }

        if (currentDatabase.isOpen()) {
            if (Output->exec(textQuery)) {
                if (result != nullptr) {
                    *result = true;
                }
            }
            else if (result != nullptr) {
                if( Output->lastError().number() == 2006) {
                    currentDatabase.close();
                    if (currentDatabase.open() && Output->exec(textQuery)) {
                        *result = true;
                    }
                    else {
                        *result = false;
                    }
                }
            }
        }
        else if (result != nullptr) {
            *result = false;
        }
    }
    else if (result != nullptr) {
        *result = false;
    }

    mutexDataBase->unlock();

    return Output;
}

QSqlQuery *QParentDatabaseCommands::execQuery(QString textQuery, QString bindName,
                                              QVariant bindValue, bool *result)
{
    QSqlQuery *Output;

    mutexDataBase->lock();

    Output = new QSqlQuery(currentDatabase);
    Output->prepare(textQuery);
    Output->bindValue(bindName,bindValue);

    if (currentDatabase.isValid()) {
        if (!currentDatabase.isOpen())
            currentDatabase.open();

        if (currentDatabase.isOpen()) {

            if (Output->exec()) {
                if (result != nullptr) *result = true;

            } else if (result != nullptr) *result = false;

        } else if (result != nullptr) *result = false;

    } else if (result != nullptr) *result = false;


    mutexDataBase->unlock();

    return Output;
}

void QParentDatabaseCommands::printTextError(const QString &textError,
                                             const QString &textQuery)
{
    qDebug()<<"Error query: "<<textError;
    qDebug()<<"textQuery = "<<textQuery;
}

int QParentDatabaseCommands::getNextId(QString table, QString idName)
{
    int Output = -1;

    QString textQuery = "select max(" + idName +") from " + table + ";";
    bool result;
    QSqlQuery *query = makeQuery(textQuery, &result);

    if (result) {
        if (query->next())
            Output = query->value(0).toInt() + 1;
    }

    delete query;

    return Output;
}

bool QParentDatabaseCommands::clearTable(const QString &table)
{
    bool result = false;
    QString text = "DELETE FROM " + table + ";";

    QSqlQuery *query = makeQuery(text, &result);
    delete query;
    return result;
}

bool QParentDatabaseCommands::remove(const RemoveInformation &object)
{
    bool result = false;
    QString text = "DELETE FROM "
            + object.tableName
            + " WHERE "
            + object.columnName_ID + " = '" + QString::number(object.id) + "'"
            + " AND "
            + object.columnName_Name + " = '" + object.name + "';";
    QSqlQuery *query = makeQuery(text, &result);
    delete query;
    return result;
}

