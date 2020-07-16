#ifndef QUSERCOMMANDS_H
#define QUSERCOMMANDS_H

#include <QObject>
#include "../QParentDatabaseCommands/qparentdatabasecommands.h"
#include "../../../SalesSystem/QUser/quser.h"
#include "QUserQueries/quserqueries.h"

namespace DatabaseCommands {

class QUserCommands : public QParentDatabaseCommands
{
public:
    explicit QUserCommands(QSqlDatabase *database,
                           QObject *parent = nullptr);
    QUserCommands() = delete;
    ~QUserCommands() = default;

    bool createTable();
    bool clear();
    QVector<QUser> getUsers();
    QUser get(int idUser);
    QUser get(const QString &login);
    int add(QUser &user);
    int add(int id, QUser &user);
    bool edit(QUser &user);
    int getId(QUser &user);
    bool remove(int id, const QString &name);

private:
    void commonGet(QSqlQuery *query, QUser &value);
};

}

#endif // QUSERCOMMANDS_H
