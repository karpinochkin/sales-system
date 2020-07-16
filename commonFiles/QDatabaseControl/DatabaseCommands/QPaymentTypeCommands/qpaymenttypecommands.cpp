#include "qpaymenttypecommands.h"

using namespace DatabaseCommands;

QPaymentTypeCommands::QPaymentTypeCommands(QSqlDatabase *database, QObject *parent)
    : QParentDatabaseCommands(database, parent)
{

}

bool QPaymentTypeCommands::createTable()
{
    bool result = false;
    QSqlQuery *query = makeQuery(QPaymentTypeQueries::createTable_text(),
                                 &result);
    if (result) {
        qDebug() << QPaymentTypeQueries::getTableName() + " is created";
    }
    delete query;
    return result;
}

bool QPaymentTypeCommands::clear()
{
    bool result = this->clearTable(QPaymentTypeQueries::getTableName());
    return result;
}

QVector<QPaymentType> QPaymentTypeCommands::getTypes()
{
    QVector<QPaymentType> output;
    bool result = false;
    QSqlQuery *query  = makeQuery(QPaymentTypeQueries::getTypes_text(),
                                  &result);
    if(result) {
        QPaymentType type;
        while (query->next()) {
            this->commonGet(query, type);

            output.push_back(type);
        }
    }
    delete query;
    return output;
}

QPaymentType QPaymentTypeCommands::get(int idTypeProduct)
{
    QPaymentType output;
    bool result = false;
    QSqlQuery *query = makeQuery(QPaymentTypeQueries::get_text(idTypeProduct),
                                 &result);
    if(result) {
        if(query->next()) {
            this->commonGet(query, output);
        }
    }
    delete  query;
    return output;
}

int QPaymentTypeCommands::getId(const QPaymentType &type)
{
    int Output = -1;
    bool result = false;
    QSqlQuery *query = makeQuery(QPaymentTypeQueries::getId_text(type),
                                 &result);
    if(result) {
        if(query->next()) {
            Output = query->value(0).toInt();
        }
    }
    delete query;
    return Output;
}

bool QPaymentTypeCommands::remove(int id, const QString &name)
{
    DatabaseCommands::RemoveInformation obj;
    obj.id = id;
    obj.name = name;
    obj.tableName = QPaymentTypeQueries::getTableName();
    obj.columnName_ID = QPaymentTypeQueries::getColumnName_ID();
    obj.columnName_Name = QPaymentTypeQueries::getColumnName_Name();

    bool result = QParentDatabaseCommands::remove(obj);
    return result;
}

int QPaymentTypeCommands::add(const QPaymentType &type)
{
    int output = -1;
    int nextID = this->getNextId(QPaymentTypeQueries::getTableName(),
                                 QPaymentTypeQueries::getColumnName_ID());
    bool result = false;
    QSqlQuery *query = makeQuery(QPaymentTypeQueries::add_text(nextID, type),
                                 &result);
    if (result) {
        output = this->getId(type);
    }
    delete query;
    return output;
}

int QPaymentTypeCommands::add(int id, const QPaymentType &type)
{
    int output = -1;
    bool result = false;
    QSqlQuery *query = makeQuery(QPaymentTypeQueries::add_text(id, type),
                                 &result);
    if (result) {
        output = this->getId(type);
    }
    delete query;
    return output;
}

bool QPaymentTypeCommands::edit(const QPaymentType &type)
{
    bool output = false;
    QSqlQuery *query = makeQuery(QPaymentTypeQueries::edit_text(type),
                                 &output);
    delete query;
    return output;
}

void QPaymentTypeCommands::commonGet(QSqlQuery *query, QPaymentType &type)
{
    type.id = query->value(0).toInt();
    type.name = query->value(1).toString();
    type.description = query->value(2).toString();
}
