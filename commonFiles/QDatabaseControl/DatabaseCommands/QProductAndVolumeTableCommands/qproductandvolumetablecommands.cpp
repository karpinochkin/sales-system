#include "qproductandvolumetablecommands.h"

using namespace DatabaseCommands;

QProductAndVolumeTableCommands::QProductAndVolumeTableCommands(QSqlDatabase *database,
                                                               QObject *parent)
    : QParentDatabaseCommands(database, parent)
{

}

bool QProductAndVolumeTableCommands::createTable()
{
    bool result = false;
    QSqlQuery *query = makeQuery(QProductAndVolumeTableQueries::createTable_text(),
                                 &result);
    if (result) {
        qDebug() << " product and volume table is created";
    }
    delete query;
    return result;
}

bool QProductAndVolumeTableCommands::clear()
{
    bool result = this->clearTable("tbl_product_volumeProduct");
    return result;
}

QVector<int> QProductAndVolumeTableCommands::getIdVolumes(int idProduct)
{
    QVector<int> output;
    bool result = false;
    QSqlQuery *query = makeQuery(QProductAndVolumeTableQueries::getIdVolumes_text(idProduct),
                                 &result);
    if(result) {
        while (query->next()) {
            output.push_back(query->value(0).toInt());
        }
    }
    delete query;
    return output;
}

QVector<int> QProductAndVolumeTableCommands::getIdProducts(int idVolume)
{
    QVector<int> Output;
    bool result = false;
    QSqlQuery *query = makeQuery(QProductAndVolumeTableQueries::getIdProducts_text(idVolume),
                                 &result);
    if(result) {
        while (query->next()) {
            Output.push_back(query->value(0).toInt());
        }
    }
    delete  query;
    return Output;
}

bool QProductAndVolumeTableCommands::linkProduct(int idVolume, int idProduct)
{
    bool output = false;
    QSqlQuery *query = makeQuery(QProductAndVolumeTableQueries::linkProduct(idVolume, idProduct),
                                 &output);
    delete query;
    return output;
}

bool QProductAndVolumeTableCommands::unlinkProducts(int idVolume)
{
    bool output = false;
    QSqlQuery *query = makeQuery(QProductAndVolumeTableQueries::unlinkProducts(idVolume),
                                 &output);
    delete query;
    return output;
}
