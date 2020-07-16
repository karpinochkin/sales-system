#include "qsalescategorycommands.h"

using namespace DatabaseCommands;

QSalesCategoryCommands::QSalesCategoryCommands(QSqlDatabase *database, QObject *parent)
    :  QParentDatabaseCommands(database, parent)
{
    pointAndCategoryTable = new QPointSaleAndCategoryTableCommands(database,
                                                                   this);
}

bool QSalesCategoryCommands::createTable()
{
    bool result = false;
    QSqlQuery* query = makeQuery(QSalesCategoryQueries::createTable_text(),
                                 &result);
    if (result) {
        qDebug() << QSalesCategoryQueries::getTableName() + " is created";
    }
    delete query;
    return result;
}

bool QSalesCategoryCommands::clear()
{
    pointAndCategoryTable->clear();
    bool result = this->clearTable(QSalesCategoryQueries::getTableName());
    return result;
}

QVector<QSalesCategory> QSalesCategoryCommands::getCategories()
{
    QVector<QSalesCategory> categories;
    bool result = false;
    QSqlQuery *query = makeQuery(QSalesCategoryQueries::getCategories_QueryText(),
                                 &result);
    if(result) {
        QSalesCategory category;
        while (query->next()) {
            this->commonGet(query, category);

            categories.push_back(category);
        }
    }
    delete query;
    return categories;
}

QVector<QSalesCategory> QSalesCategoryCommands::getCategories(int idPointSale)
{
    QVector<QSalesCategory> categories;
    QVector<int> idCategories = pointAndCategoryTable->getCategoriesId(idPointSale);
    int idCategory;
    QSalesCategory category;
    for (int i=0;i<idCategories.length();i++) {
        idCategory = idCategories.at(i);
        category = this->get(idCategory);
        categories.push_back(category);
    }
    return categories;
}

QSalesCategory QSalesCategoryCommands::get(int idCategory)
{
    QSalesCategory output;
    bool result = false;
    QSqlQuery *query = makeQuery(QSalesCategoryQueries::get_QueryText(idCategory),
                                 &result);
    if(result) {
        query->next();
        this->commonGet(query, output);
    }
    delete query;
    return output;
}


bool QSalesCategoryCommands::edit(QSalesCategory &category)
{
    bool output = false;
    this->unlinkPointSales(category.id);
    QSqlQuery *query = makeQuery(QSalesCategoryQueries::edit_QueryText(category),
                                 &output);
    if(output) {
        for(int i = 0; i < category.idPointSale.size(); i++) {
            this->linkPointSale(category.id, category.idPointSale.at(i));
        }
}
    delete  query;
    return output;
}

int QSalesCategoryCommands::add(QSalesCategory &category)
{
    int output = -1;
    int nextId = this->getNextId(QSalesCategoryQueries::getTableName(),
                                 QSalesCategoryQueries::getColumnName_ID());
    bool result = false;
    QSqlQuery *query = makeQuery(QSalesCategoryQueries::add_QueryText(nextId, category),
                                 &result);
    if(result) {
        output = this->getId(category);
        for (int i=0;i<category.idPointSale.size();i++) {
            this->linkPointSale(output, category.idPointSale.at(i));
        }
    }
    delete query;
    return output;
}

int QSalesCategoryCommands::add(int id, QSalesCategory &category)
{
    int output = -1;

    bool result = false;
    QSqlQuery *query = makeQuery(QSalesCategoryQueries::add_QueryText(id, category),
                                 &result);
    if(result) {
        output = this->getId(category);
        this->unlinkPointSales(id);
        for (int i = 0; i < category.idPointSale.size(); i++) {
            this->linkPointSale(output, category.idPointSale.at(i));
        }
    }
    delete query;
    return output;
}

QVector<int> QSalesCategoryCommands::getIdPointSales(int idCategory)
{
    QVector<int> output = pointAndCategoryTable->getIdPointSales(idCategory);
    return output;
}


bool QSalesCategoryCommands::linkPointSale(int idCategory, int idPointSale)
{
    bool result = pointAndCategoryTable->linkPointSale(idCategory, idPointSale);
    return result;
}

bool QSalesCategoryCommands::unlinkPointSales(int idCategory)
{
    bool result = pointAndCategoryTable->unlinkPointSales(idCategory);
    return result;
}

int QSalesCategoryCommands::getId(QSalesCategory &category)
{
    int output = -1;
    bool result = false;
    QSqlQuery *query = makeQuery(QSalesCategoryQueries::getId_QueryText(category),
                                 &result);
    if(result) {
        if(query->next()) {
            output = query->value(0).toInt();
        }
    }
    delete  query;
    return output;
}

bool QSalesCategoryCommands::remove(int id, const QString &name)
{
    DatabaseCommands::RemoveInformation obj;
    obj.id = id;
    obj.name = name;
    obj.tableName = QSalesCategoryQueries::getTableName();
    obj.columnName_ID = QSalesCategoryQueries::getColumnName_ID();
    obj.columnName_Name = QSalesCategoryQueries::getColumnName_Name();

    bool result = QParentDatabaseCommands::remove(obj);
    return result;
}

void QSalesCategoryCommands::commonGet(QSqlQuery *query, QSalesCategory &value)
{
    value.id = query->value(0).toInt();
    value.name = query->value(1).toString();
    value.description = query->value(2).toString();

    value.color.setRed(query->value(3).toInt());
    value.color.setGreen(query->value(4).toInt());
    value.color.setBlue(query->value(5).toInt());

    value.idPointSale = this->getIdPointSales(value.id);
}
