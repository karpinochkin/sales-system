#ifndef QABSTRACTDATABASECOMMANDS_H
#define QABSTRACTDATABASECOMMANDS_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QObject>
#include <QMutex>
#include <QDebug>

namespace DatabaseCommands {
struct RemoveInformation
{
    QString tableName;
    QString columnName_ID;
    QString columnName_Name;

    int id;
    QString name;
};

class QParentDatabaseCommands : public QObject
{
public:
    QParentDatabaseCommands() = delete;

protected:
    explicit QParentDatabaseCommands(QSqlDatabase *database, QObject *parent = nullptr);
    ~QParentDatabaseCommands();

    QSqlQuery* makeQuery(const QString &textQuery,
                         bool *result);
    QSqlQuery* makeQuery(const QString &textQuery,
                         QString bindName,
                         QVariant bindValue,
                         bool *result);
    int getNextId(QString table,
                  QString idName);
    bool clearTable(const QString &table);
    bool remove(const RemoveInformation &object);

private:
    QSqlDatabase currentDatabase;
    QMutex *mutexDataBase = nullptr;

    QSqlQuery *execQuery(const QString &textQuery,
                         bool *result = nullptr);
    QSqlQuery *execQuery(QString textQuery,
                         QString bindName,
                         QVariant bindValue,
                         bool *result = nullptr);
    void printTextError(const QString &textError,
                        const QString &textQuery);
};

}
#endif // QABSTRACTDATABASECOMMANDS_H
