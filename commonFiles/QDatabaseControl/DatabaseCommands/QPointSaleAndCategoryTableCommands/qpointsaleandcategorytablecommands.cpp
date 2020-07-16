#include "qpointsaleandcategorytablecommands.h"

using namespace DatabaseCommands;

QPointSaleAndCategoryTableCommands::QPointSaleAndCategoryTableCommands(QSqlDatabase *database,
                                                                       QObject *parent)
    :  QParentDatabaseCommands(database, parent)
{

}

bool QPointSaleAndCategoryTableCommands::createTable()
{
    bool result = false;
    QSqlQuery *query = makeQuery(QPointSaleAndCategoryTableQueries::createTable_text(),
                                 &result);

    if (result) {
        qDebug() << "Point Sale and cetegory table is created";
    }
    delete query;
    return result;
}

bool QPointSaleAndCategoryTableCommands::clear()
{
    bool result = this->clearTable("tbl_pointSale_productСategory");
    return result;
}

QVector<int> QPointSaleAndCategoryTableCommands::getCategoriesId(int idPointSale)
{
    QVector<int> Output;
    bool result = false;
    QSqlQuery *query = makeQuery(QPointSaleAndCategoryTableQueries::getCategoriesId_QueryText(idPointSale),
                                 &result);
    if(result) {
        int currentId;
        while (query->next()) {
            currentId = query->value(0).toInt();
            Output.push_back(currentId);
        }
    }

    delete  query;
    return  Output;
}

bool QPointSaleAndCategoryTableCommands::unlinkCategories(int idPointSale)
{
    bool Output = false;
    QSqlQuery *query = makeQuery(QPointSaleAndCategoryTableQueries::unlinkCategories(idPointSale),
                                 &Output);
    delete query;
    return Output;
}

bool QPointSaleAndCategoryTableCommands::linkCategory(int idPointSale, int idCategory)
{
    bool output = false;
    QSqlQuery *query = makeQuery(QPointSaleAndCategoryTableQueries::linkCategory(idPointSale,
                                                                                 idCategory),
                                 &output);
    delete query;
    return output;
}

QVector<int> QPointSaleAndCategoryTableCommands::getIdPointSales(int idCategory)
{
    QVector<int> output;
    bool result = false;
    QSqlQuery *query = makeQuery(QPointSaleAndCategoryTableQueries::getPointSalesId_QueryText(idCategory),
                                 &result);
    if(result) {
        while (query->next()) {
            output.push_back(query->value(0).toInt());
        }
    }
    delete query;
    return output;

}

bool  QPointSaleAndCategoryTableCommands::linkPointSale(int idCategory, int idPointSale)
{
    bool output = false;
    QSqlQuery *query = makeQuery(QPointSaleAndCategoryTableQueries::linkPointSale(idCategory, idPointSale),
                                 &output);
    delete query;
    return output;
}

bool QPointSaleAndCategoryTableCommands::unlinkPointSales(int idCategory)
{
    bool output = false;
    QSqlQuery *query = makeQuery(QPointSaleAndCategoryTableQueries::unlinkPointSales(idCategory),
                                 &output);
    delete query;
    return output;
}
