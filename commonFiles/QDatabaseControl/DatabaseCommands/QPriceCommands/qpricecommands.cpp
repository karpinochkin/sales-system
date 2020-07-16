#include "qpricecommands.h"

using namespace DatabaseCommands;

QPriceCommands::QPriceCommands(QSqlDatabase *database, QObject *parent)
    : QParentDatabaseCommands(database, parent)
{
    pointSaleAndPrice = new QPointSaleAndPriceTableCommands(database,
                                                            parent);
}

bool QPriceCommands::createTable()
{
    bool result = false;
    QSqlQuery *query = makeQuery(QPriceQueries::createTable_text(),
                                 &result);
    if (result) {
        qDebug () << QPriceQueries::getTableName() + " is created";
    }
    delete query;
    return result;
}

bool QPriceCommands::createPointSaleAndPriceTable()
{
    bool result = pointSaleAndPrice->createTable();
    return result;
}

bool QPriceCommands::clear()
{
    pointSaleAndPrice->clear();
    bool result = this->clearTable(QPriceQueries::getTableName());
    return result;
}

QVector<QPrice> QPriceCommands::getPrices()
{
    QVector<QPrice> output;
    bool result = false;
    QSqlQuery *query = makeQuery(QPriceQueries::getPrices_text(),
                                 &result);
    if(result) {
        QPrice price;
        while (query->next()) {
            this->commonGet(query, price);

            output.push_back(price);
        }
    }
    delete query;
    return output;
}

QVector<QPrice> QPriceCommands::getPrices(int idPointSale)
{
    QVector<QPrice> output;
    QVector<int> idPrices = pointSaleAndPrice->getIdPrices(idPointSale);

    for(int i = 0; i < idPrices.size(); i++) {
        output.push_back(this->get(idPrices.at(i)));
    }

    return output;
}

QPrice QPriceCommands::get(int idPrice)
{
    QPrice output;
    bool result = false;
    QSqlQuery *query = makeQuery(QPriceQueries::get_text(idPrice),
                                 &result);
    if(result) {
        if(query->next()) {
            this->commonGet(query, output);
        }
    }

    delete query;
    return output;
}

QPrice QPriceCommands::get(int idCategory, int idProduct, int idVolume)
{
    QPrice output;
    bool result = false;
    QSqlQuery *query = makeQuery(QPriceQueries::get_text(idCategory, idProduct, idVolume),
                                 &result);
    if(result) {
        if (query->next()) {
            this->commonGet(query, output);
        }
    }
    delete query;
    return output;
}

int QPriceCommands::getId(const QPrice &price)
{
    int output = -1;
    bool result = false;
    QSqlQuery *query = makeQuery(QPriceQueries::getId_text(price),
                                 &result);
    if(result) {
        if(query->next()) {
            output = query->value(0).toInt();
        }
    }
    delete query;
    return output;
}

QVector<int> QPriceCommands::getIdPointSales(int idPrice)
{
    QVector<int> output = pointSaleAndPrice->getIdPointSales(idPrice);
    return output;
}

bool QPriceCommands::unlinkPointSales(int idPrice)
{
    bool result = pointSaleAndPrice->unlinkPointSales(idPrice);
    return result;
}

bool QPriceCommands::linkPointSale(int idPrice, int idPointSale)
{
    bool result = pointSaleAndPrice->linkPointSale(idPrice, idPointSale);
    return result;
}

int QPriceCommands::add(const QPrice &price)
{
    int output = -1;
    int nextId = this->getNextId(QPriceQueries::getTableName(),
                                 QPriceQueries::getColumnName_ID());
    bool result = false;
    QSqlQuery *query = makeQuery(QPriceQueries::add_text(nextId, price),
                                 &result);
    if(result) {
        output = this->getId(price);
        for (int i = 0; i < price.idPointSales.size(); i++) {
            this->linkPointSale(output, price.idPointSales.at(i));
        }
    }
    delete query;
    return output;
}

int QPriceCommands::add(int id, const QPrice &price)
{
    int output = -1;
    bool result = false;
    QSqlQuery *query = makeQuery(QPriceQueries::add_text(id, price),
                                 &result);
    if(result) {
        output = this->getId(price);
        unlinkPointSales(output);
        for (int i = 0; i < price.idPointSales.size(); i++) {
            this->linkPointSale(output, price.idPointSales.at(i));
        }
    }
    delete query;
    return output;
}


bool QPriceCommands::edit(const QPrice &price)
{
    bool output = false;
    QSqlQuery *query = makeQuery(QPriceQueries::edit_text(price),
                                 &output);
    if (output) {
        this->unlinkPointSales(price.id);
        for (int i = 0; i < price.idPointSales.size(); i++) {
            this->linkPointSale(price.id, price.idPointSales.at(i));
        }
    }
    delete query;
    return output;
}

void QPriceCommands::commonGet(QSqlQuery *query, QPrice &output)
{
    output.id = query->value(0).toInt();
    output.value = query->value(1).toDouble();
    output.startDate = query->value(2).toDateTime();
    output.description = query->value(3).toString();
    output.idProduct = query->value(4).toInt();
    output.idVolume = query->value(5).toInt();
    output.idProductCategory = query->value(6).toInt();

    output.idPointSales = this->getIdPointSales(output.id);
}
