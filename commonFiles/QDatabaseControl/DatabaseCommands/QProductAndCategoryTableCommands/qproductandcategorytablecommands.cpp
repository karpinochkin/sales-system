#include "qproductandcategorytablecommands.h"

using namespace DatabaseCommands;

QProductAndCategoryTableCommands::QProductAndCategoryTableCommands(QSqlDatabase *database,
                                                                   QObject *parent)
    : QParentDatabaseCommands(database, parent)
{

}

bool QProductAndCategoryTableCommands::createTable()
{
    bool result = false;
    QSqlQuery *query = makeQuery(QProductAndCategoryQueries::createTable_text(),
                                 &result);
    if (result) {
        qDebug() << "tbl_product_category is created";
    }
    delete query;
    return result;
}

bool QProductAndCategoryTableCommands::clear()
{
    bool result = this->clearTable("tbl_product_category");
    return result;
}

QVector<int> QProductAndCategoryTableCommands::getIdCategories(int idProduct)
{
    QVector<int> output;
    bool result = false;
    QSqlQuery *query = makeQuery(QProductAndCategoryQueries::getIdCategories_text(idProduct),
                                 &result);
    if(result) {
        while (query->next()) {
            output.push_back(query->value(0).toInt());
        }
    }
    delete query;
    return output;
}

QVector<int> QProductAndCategoryTableCommands::getIdProducts(int idCategory)
{
    QVector<int> output;
    bool result = false;
    QSqlQuery *query = makeQuery(QProductAndCategoryQueries::getIdProducts_text(idCategory),
                                 &result);
    if(result) {
        int currentId;
        while (query->next()) {
            currentId = query->value(0).toInt();
            output.push_back(currentId);
        }
    }
    delete query;
    return output;
}

bool QProductAndCategoryTableCommands::linkCategory(int idProduct, int idCategory)
{
    bool output = false;
    QSqlQuery *query = makeQuery(QProductAndCategoryQueries::linkCategory(idProduct, idCategory),
                                 &output);
    delete query;
    return output;
}

bool QProductAndCategoryTableCommands::unlinkCategories(int idProduct)
{
    bool output = false;
    QSqlQuery *query = makeQuery(QProductAndCategoryQueries::unlinkCategories(idProduct),
                                 &output);
    delete query;
    return output;
}
