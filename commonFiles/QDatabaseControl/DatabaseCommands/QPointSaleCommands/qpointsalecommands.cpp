#include "qpointsalecommands.h"

using namespace DatabaseCommands;

QPointSaleCommands::QPointSaleCommands(QSqlDatabase *database, QObject *parent)
    :  QParentDatabaseCommands(database, parent)
{
    pointAndCategoryTable = new QPointSaleAndCategoryTableCommands(database,
                                                                   this);
}

bool QPointSaleCommands::createTable()
{
    bool result = false;
    QSqlQuery *query = makeQuery(QPointSaleQueries::createTable_text(),
                                 &result);
    if (result) {
        qDebug() << QPointSaleQueries::getTableName() + " is created";
    }
    delete query;
    return result;
}

bool QPointSaleCommands::createPointSaleAndProductTable()
{
    bool result = false;
    QSqlQuery *query = makeQuery(QPointSaleQueries::createPointSaleAndProductTable_text(),
                                 &result);

    if (result) {
        qDebug () << "ProductAndPointSaleTable is created";
    }
    delete query;
    return result;
}

bool QPointSaleCommands::createPointSaleAndCategoryTable()
{
    bool result = pointAndCategoryTable->createTable();
    return result;
}

bool QPointSaleCommands::clear()
{
    pointAndCategoryTable->clear();
    bool result = this->clearTable(QPointSaleQueries::getTableName());
    return result;
}

QVector<QPointSale> QPointSaleCommands::getPointSales()
{
    QVector<QPointSale> Output;
    bool result = false;

    QSqlQuery *query = makeQuery(QPointSaleQueries::getPointSales_QueryText(),
                                 &result);

    if(result) {
        QPointSale currentPointSale;
        while (query->next()) {
            this->commonGet(query, currentPointSale);

            Output.push_back(currentPointSale);
        }
    }

    delete query;
    return Output;
}



QVector<int> QPointSaleCommands::getProductsId(int idPointSale)
{
    QVector<int> Output;
    bool result = false;
    QSqlQuery *query = makeQuery(QPointSaleQueries::getProductsId_QueryText(idPointSale),
                                 &result);

    if(result) {
        int currentId;
        while(query->next()) {
            currentId = query->value(0).toInt();

            Output.push_back(currentId);
        }
    }

    delete  query;
    return Output;
}

bool QPointSaleCommands::remove(int id, const QString &name)
{
    DatabaseCommands::RemoveInformation obj;
    obj.id = id;
    obj.name = name;
    obj.tableName = QPointSaleQueries::getTableName();
    obj.columnName_ID = QPointSaleQueries::getColumnName_ID();
    obj.columnName_Name = QPointSaleQueries::getColumnName_Name();

    bool result = QParentDatabaseCommands::remove(obj);
    return result;
}

QVector<int> QPointSaleCommands::getCategoriesId(int idPointSale)
{
    QVector<int> output = pointAndCategoryTable->getCategoriesId(idPointSale);
    return  output;
}

QPointSale QPointSaleCommands::get(int idPointSale)
{
    QPointSale Output;
    bool result = false;
    QSqlQuery *query = makeQuery(QPointSaleQueries::get_QueryText(idPointSale),
                                 &result);
    if(result) {
        if (query->next()) {
            this->commonGet(query, Output);
        }
    }

    delete  query;
    return  Output;
}


bool QPointSaleCommands::edit(const QPointSale &pointSale)
{
    bool Output;

    unlinkProducts(pointSale.id);
    unlinkCategories(pointSale.id);

    linkAllCategories(pointSale);
    linkAllProducts(pointSale);

    QSqlQuery *query = makeQuery(QPointSaleQueries::edit_QueryText(pointSale.id, pointSale.name),
                                 &Output);


    delete query;
    return Output;
}


bool QPointSaleCommands::unlinkProducts(int idPointSale)
{
    bool Output = false;
    QSqlQuery *query = makeQuery(QPointSaleQueries::unlinkProducts(idPointSale),
                                 &Output);
    delete query;
    return Output;
}


bool QPointSaleCommands::unlinkCategories(int idPointSale)
{
    bool result = pointAndCategoryTable->unlinkCategories(idPointSale);
    return result;
}

void QPointSaleCommands::linkAllCategories(const QPointSale &pointSale)
{
    int currentId;
    for (int i = 0; i < pointSale.idCategories.size(); i++) {
        currentId = pointSale.idCategories.at(i);
        this->linkCategory(pointSale.id, currentId);
    }
}

bool QPointSaleCommands::linkCategory(int idPointSale, int idCategory)
{
    bool result = pointAndCategoryTable->linkCategory(idPointSale, idCategory);
    return result;
}

void QPointSaleCommands::linkAllProducts(const QPointSale &pointSale)
{
    int currentId;
    for (int i = 0; i < pointSale.idProducts.size(); i++) {
        currentId = pointSale.idProducts.at(i);
        linkProduct(pointSale.id, currentId);
    }
}

bool QPointSaleCommands::linkProduct(int idPointSale, int idProduct)
{
    bool output = false;
    QSqlQuery *query = makeQuery(QPointSaleQueries::linkProduct(idPointSale,idProduct),
                                 &output);
    delete query;
    return output;
}

int QPointSaleCommands::add(const QPointSale &pointSale)
{
    int output = -1;
    int nextId = getNextId(QPointSaleQueries::getTableName(),
                           QPointSaleQueries::getColumnName_ID());
    bool result = false;
    QSqlQuery *query = makeQuery(QPointSaleQueries::add(nextId, pointSale.name),
                                 &result);
    if(result) {
        int currentPointId = getId(pointSale);

        if (currentPointId >= 0) {
            for (int i = 0; i < pointSale.idCategories.size();i++) {
                linkCategory(currentPointId, pointSale.idCategories.at(i));
            }

            for (int i = 0; i < pointSale.idProducts.size();i++) {
                linkProduct(currentPointId, pointSale.idProducts.at(i));
            }

            output = currentPointId;
        }
    }
    delete query;
    return output;
}

int QPointSaleCommands::add(int id, const QPointSale &pointSale)
{
    int output = -1;
    bool result = false;
    QSqlQuery *query = makeQuery(QPointSaleQueries::add(id, pointSale.name),
                                 &result);
    if(result) {
        int currentPointId = getId(pointSale);
        unlinkCategories(pointSale.id);
        if (currentPointId >= 0) {
            for (int i = 0; i < pointSale.idCategories.size();i++) {
                linkCategory(currentPointId, pointSale.idCategories.at(i));
            }

            for (int i = 0; i < pointSale.idProducts.size();i++) {
                linkProduct(currentPointId, pointSale.idProducts.at(i));
            }

            output = currentPointId;
        }
    }
    delete query;
    return output;
}

int QPointSaleCommands::getId(const QPointSale &pointSale)
{
    int output = -1;
    bool result = false;
    QSqlQuery *query = makeQuery(QPointSaleQueries::getId_QueryText(pointSale.name),
                                 &result);
    if(result) {
        if(query->next()) {
            output = query->value(0).toInt();
        }
    }

    delete query;
    return output;

}

void QPointSaleCommands::commonGet(QSqlQuery *query, QPointSale &output)
{
    output.id = query->value(0).toInt();
    output.name = query->value(1).toString();

    output.idProducts = getProductsId(output.id);
    output.idCategories = getCategoriesId(output.id);
}
