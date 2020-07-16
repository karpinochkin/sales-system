#include "qpointsaleandpricetablecommands.h"

using namespace DatabaseCommands;

QPointSaleAndPriceTableCommands::QPointSaleAndPriceTableCommands(QSqlDatabase *database,
                                                                 QObject *parent)
    : QParentDatabaseCommands(database, parent)
{

}

bool QPointSaleAndPriceTableCommands::createTable()
{
    bool result = false;
    QSqlQuery *query = makeQuery(QPointSaleAndPriceQueries::createTable_text(),
                                 &result);

    if(result) {
        qDebug() << "point sale and price table is created";
    }
    delete query;
    return result;
}

bool QPointSaleAndPriceTableCommands::clear()
{
    bool result = this->clearTable("tbl_pointSale_price");
    return result;
}

QVector<int> QPointSaleAndPriceTableCommands::getIdPrices(int idPointSale)
{
    QVector<int> output;
    bool result = false;
    QSqlQuery *query = makeQuery(QPointSaleAndPriceQueries::getIdPrices_text(idPointSale),
                                 &result);
    if(result) {
        while (query->next()) {
            output.push_back(query->value(0).toInt());
        }
    }

    delete query;
    return output;
}

QVector<int> QPointSaleAndPriceTableCommands::getIdPointSales(int idPrice)
{
    QVector<int> output;
    bool result = false;
    QSqlQuery *query = makeQuery(QPointSaleAndPriceQueries::getIdPointSales_text(idPrice),
                                 &result);
    if(result) {
        while (query->next()) {
            output.push_back(query->value(0).toInt());
        }
    }
    delete query;
    return output;
}

bool QPointSaleAndPriceTableCommands::unlinkPointSales(int idPrice)
{
    bool output = false;
    QSqlQuery *query = makeQuery(QPointSaleAndPriceQueries::unlinkPointSales_text(idPrice),
                                 &output);
    delete query;
    return output;
}

bool QPointSaleAndPriceTableCommands::linkPointSale(int idPrice,
                                                    int idPointSale)
{
    bool output = false;
    QSqlQuery *query = makeQuery(QPointSaleAndPriceQueries::linkPointSale_text(idPrice, idPointSale),
                                 &output);
    delete query;
    return output;
}
