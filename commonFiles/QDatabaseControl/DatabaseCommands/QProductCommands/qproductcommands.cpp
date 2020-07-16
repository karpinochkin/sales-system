#include "qproductcommands.h"

using namespace DatabaseCommands;

QProductCommands::QProductCommands(QSqlDatabase *database, QObject *parent)
    : QParentDatabaseCommands(database, parent)
{
    productAndVolumeTable = new QProductAndVolumeTableCommands(database,
                                                               this);
    productAndCategoryTable = new QProductAndCategoryTableCommands(database,
                                                                   this);
}

bool QProductCommands::createTable()
{
    bool result = false;
    QSqlQuery *query = makeQuery(QProductQueries::createTable_text(),
                                 &result);

    if(result) {
        qDebug() << QProductQueries::getTableName() + " is created";
    }

    delete query;
    return result;
}

bool QProductCommands::clear()
{
    productAndVolumeTable->clear();
    productAndCategoryTable->clear();
    bool result = this->clearTable(QProductQueries::getTableName());
    return result;
}

QVector<QProduct> QProductCommands::getProducts()
{
    QVector<QProduct> output;
    bool result = false;
    QSqlQuery *query = makeQuery(QProductQueries::getProducts_text(),
                                 &result);
    if(result) {
        QProduct product;
        while (query->next()) {
            this->commonGet(query, product);

            output.push_back(product);
        }
    }
    delete query;
    return output;
}

QVector<QProduct> QProductCommands::getProducts(int idCategory)
{
    QVector<QProduct> output;
    QVector<int> idProducts;
    idProducts = productAndCategoryTable->getIdProducts(idCategory);

    for (int i = 0; i < idProducts.size(); i++) {
        output.push_back(this->get(idProducts.at(i)));
    }
    return output;
}


QVector<int> QProductCommands::getAllId()
{
    QVector<int> output;
    bool result = false;
    QSqlQuery *query = makeQuery(QProductQueries::getAllID_text(),
                                 &result);
    if(result) {
        while (query->next()) {
            int id = query->value(0).toInt();
            output.push_back(id);
        }
    }
    return output;
}


QVector<int> QProductCommands::getIdCategories(int idProduct)
{
    QVector<int> output = productAndCategoryTable->getIdCategories(idProduct);
    return output;
}

QProduct QProductCommands::get(int idProduct)
{
    QProduct product;
    bool result = false;
    QSqlQuery *query = makeQuery(QProductQueries::get_text(idProduct),
                                 &result);
    if(result) {
        if(query->next()) {
            this->commonGet(query, product);
        }
    }
    delete query;
    return product;
}

int QProductCommands::add(QProduct &product)
{
    int output = -1;
    int nextId = this->getNextId(QProductQueries::getTableName(),
                                 QProductQueries::getColumnName_ID());
    bool result = false;
    QSqlQuery *query = nullptr;
    if (product.idPicture <= 0) {
        query = makeQuery(QProductQueries::add_textEmptyPicture(nextId, product),
                                     &result);
    }
    else {
        query = makeQuery(QProductQueries::add_text(nextId, product),
                                     &result);
    }
    if(result) {
        if (product.idPicture <= 0) {
            output = product.id;
        }
        else {
            output = this->getId(product);
        }
        for(int i = 0; i < product.idCategories.size(); i++) {
            this->linkCategory(output, product.idCategories.at(i));
        }
    }
    delete query;
    return output;
}

int QProductCommands::add(int id, QProduct &product)
{
    int output = -1;
    bool result = false;
    QSqlQuery *query = nullptr;
    if (product.idPicture <= 0) {
        query = makeQuery(QProductQueries::add_textEmptyPicture(id, product),
                          &result);
    }
    else {
        query = makeQuery(QProductQueries::add_text(id, product),
                          &result);
    }
    if(result) {
        if (product.idPicture <= 0) {
            output = product.id;
        }
        else {
            output = this->getId(product);
        }
//        qDebug() << output<< product.id << product.idPicture << product.idCategories;
        unlinkCategories(output);
        for(int i = 0; i < product.idCategories.size(); i++) {
            this->linkCategory(output, product.idCategories.at(i));
        }
    }
    delete query;
    return output;
}

bool QProductCommands::linkCategory(int idProduct, int idCategory)
{
    bool result = productAndCategoryTable->linkCategory(idProduct,
                                                        idCategory);
    return result;
}

QVector<int> QProductCommands::getIdVolumes(int idProduct)
{
    QVector<int> Output = productAndVolumeTable->getIdVolumes(idProduct);
    return Output;
}

int QProductCommands::getId(QProduct &product)
{
    int output = -1;
    bool result = false;
    QSqlQuery *query = makeQuery(QProductQueries::getId_text(product),
                                 &result);
    if(result) {
        if(query->next()) {
            output = query->value(0).toInt();
        }
    }
    delete query;
    return output;
}

bool QProductCommands::edit(QProduct &product)
{
    bool output = false;
    QSqlQuery *query = nullptr;
    if (product.idPicture <= 0) {
        query = makeQuery(QProductQueries::edit_textEmptyPicture(product),
                          &output);
    }
    else {
        query = makeQuery(QProductQueries::edit_text(product),
                          &output);
    }

    if(output) {
        this->unlinkCategories(product.id);
        for(int i = 0; i < product.idCategories.size(); i++) {
            this->linkCategory(product.id, product.idCategories.at(i));
        }
    }
    delete query;
    return output;
}

bool QProductCommands::unlinkCategories(int idProduct)
{
    bool result = productAndCategoryTable->unlinkCategories(idProduct);
    return result;
}

void QProductCommands::commonGet(QSqlQuery *query, QProduct &value)
{
    value.id = query->value(0).toInt();
    value.name = query->value(1).toString();
    value.description = query->value(2).toString();
    value.color.setRed(query->value(3).toInt());
    value.color.setGreen(query->value(4).toInt());
    value.color.setBlue(query->value(5).toInt());
    value.idPicture = query->value(6).toInt();
    value.pictureHash = query->value(7).toString();
    value.idCategories = this->getIdCategories(value.id);
}

