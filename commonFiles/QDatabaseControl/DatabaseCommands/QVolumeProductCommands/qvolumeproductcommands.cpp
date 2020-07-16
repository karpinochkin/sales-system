#include "qvolumeproductcommands.h"

using namespace DatabaseCommands;

QVolumeProductCommands::QVolumeProductCommands(QSqlDatabase *database,
                                               QObject *parent)
    : QParentDatabaseCommands(database, parent)
{
    productAndVolumeCommands = new QProductAndVolumeTableCommands(database,
                                                                  this);
}

bool QVolumeProductCommands::createTable()
{
    bool result = false;
    QSqlQuery *query = makeQuery(QVolumeQueries::createTable_text(),
                                 &result);
    if (result) {
        qDebug() << QVolumeQueries::getTableName() + " is created";
    }
    delete query;
    return result;
}

bool QVolumeProductCommands::clear()
{
    productAndVolumeCommands->clear();
    bool result = this->clearTable(QVolumeQueries::getTableName());
    return result;
}

QVector<QVolumeProduct> QVolumeProductCommands::getVolumes()
{
    QVector<QVolumeProduct> output;
    bool result = false;
    QSqlQuery *query = makeQuery(QVolumeQueries::getVolumes_text(),
                                 &result);
    if(result) {
        QVolumeProduct volume;
        while (query->next()) {
            this->commonGet(query, volume);

            output.push_back(volume);
        }
    }
    delete query;
    return output;
}

QVector<QVolumeProduct> QVolumeProductCommands::getVolumes(int idProduct)
{
    QVector<QVolumeProduct> output;
    QVector<int> idVolumes = productAndVolumeCommands->getIdVolumes(idProduct);

    for(int i = 0; i < idVolumes.size(); i++) {
        output.push_back(this->get(idVolumes.at(i)));
    }

    return output;
}

QVolumeProduct QVolumeProductCommands::get(int idVolume)
{
    QVolumeProduct output;
    bool result = false;
    QSqlQuery *query = makeQuery(QVolumeQueries::get_text(idVolume),
                                 &result);
    if(result) {
        if (query->next()) {
            this->commonGet(query, output);
        }
    }
    delete query;
    return output;
}

int QVolumeProductCommands::getId(const QVolumeProduct &volume)
{
    int output = -1;
    bool result = false;
    QSqlQuery *query = makeQuery(QVolumeQueries::getId_text(volume),
                                 &result);
    if(result) {
        if(query->next()) {
            output = query->value(0).toInt();
        }
    }
    delete query;
    return output;
}

bool QVolumeProductCommands::remove(int id, const QString &name)
{
    DatabaseCommands::RemoveInformation obj;
    obj.id = id;
    obj.name = name;
    obj.tableName = QVolumeQueries::getTableName();
    obj.columnName_ID = QVolumeQueries::getColumnName_ID();
    obj.columnName_Name = QVolumeQueries::getColumnName_Name();

    bool result = QParentDatabaseCommands::remove(obj);
    return result;
}

QVector<int> QVolumeProductCommands::getIdProducts(int idVolume)
{
    QVector<int> output = productAndVolumeCommands->getIdProducts(idVolume);
    return output;
}

bool QVolumeProductCommands::linkProduct(int idVolume, int idProduct)
{
    bool output = productAndVolumeCommands->linkProduct(idVolume, idProduct);
    return output;
}

bool QVolumeProductCommands::unlinkProducts(int idVolume)
{
    bool output = productAndVolumeCommands->unlinkProducts(idVolume);
    return output;
}

int QVolumeProductCommands::add(const QVolumeProduct &volume)
{
    int output = -1;
    int nextId = this->getNextId(QVolumeQueries::getTableName(),
                                 QVolumeQueries::getColumnName_ID());
    bool result = false;
    QSqlQuery *query = makeQuery(QVolumeQueries::add_text(nextId, volume),
                                 &result);
    if(result) {
        output = this->getId(volume);
        for(int i = 0; i < volume.idProducts.size(); i++) {
            this->linkProduct(output, volume.idProducts.at(i));
        }
    }
    delete query;
    return output;
}

int QVolumeProductCommands::add(int id, const QVolumeProduct &volume)
{
    int output = -1;
    bool result = false;
    QSqlQuery *query = makeQuery(QVolumeQueries::add_text(id, volume),
                                 &result);
    if(result) {
        output = this->getId(volume);
        this->unlinkProducts(output);
        for(int i = 0; i < volume.idProducts.size(); i++) {
            this->linkProduct(output, volume.idProducts.at(i));
        }
    }
    delete query;
    return output;
}

bool QVolumeProductCommands::edit(const QVolumeProduct &volume)
{
    bool output = false;
    QSqlQuery *query = makeQuery(QVolumeQueries::edit_text(volume),
                                 &output);
    if(output) {
        this->unlinkProducts(volume.id);
        for(int i = 0; i < volume.idProducts.size(); i++) {
            this->linkProduct(volume.id, volume.idProducts.at(i));
        }
    }
    delete query;
    return output;
}

void QVolumeProductCommands::commonGet(QSqlQuery *query, QVolumeProduct &value)
{
    value.id = query->value(0).toInt();
    value.name = query->value(1).toString();
    value.volume = query->value(2).toInt();
    value.description = query->value(3).toString();
    value.units = query->value(4).toString();

    value.idProducts = this->getIdProducts(value.id);
}
