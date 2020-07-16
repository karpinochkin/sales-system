#include "qsoldpositioncommands.h"

using namespace DatabaseCommands;

QSoldPositionCommands::QSoldPositionCommands(QSqlDatabase *databse,
                                             QObject *parent)
    : QParentDatabaseCommands(databse, parent)
{

}

bool QSoldPositionCommands::createTable()
{
    bool result = false;
    QSqlQuery *query = makeQuery(QSoldPositionQueries::createTable_text(),
                                 &result);
    if (result) {
        qDebug() << QSoldPositionQueries::getTableName() + " is created";
    }
    delete query;
    return result;
}

bool QSoldPositionCommands::clear()
{
    bool result = this->clearTable(QSoldPositionQueries::getTableName());
    return result;
}

QVector<QSoldPosition> QSoldPositionCommands::getSoldPositions()
{
    QVector<QSoldPosition> output;
    bool result = false;
    QSqlQuery *query = makeQuery(QSoldPositionQueries::getSoldPositions_text(),
                                 &result);
    this->commonGetReceipts(result, query, &output);
    delete query;
    return output;
}

QVector<QSoldPosition> QSoldPositionCommands::getSoldPositions(QDateTime startDate, QDateTime endDate)
{
    QVector<QSoldPosition> output;
    bool result = false;
    QSqlQuery *query = makeQuery(QSoldPositionQueries::getSoldPositions_text(startDate, endDate),
                                 &result);
    this->commonGetReceipts(result, query, &output);
    delete query;
    return output;
}

QVector<QSoldPosition> QSoldPositionCommands::getSoldPositions(int idReceipt)
{
    QVector<QSoldPosition> output;
    bool result = false;
    QSqlQuery *query = makeQuery(QSoldPositionQueries::getSoldPositions_text(idReceipt),
                                 &result);
    this->commonGetReceipts(result, query, &output);
    delete query;
    return output;
}

QVector<QSoldPosition> QSoldPositionCommands::getSoldPositionsForProduct(int idProduct)
{
    QVector<QSoldPosition> output;
    bool result = false;
    QSqlQuery *query = makeQuery(QSoldPositionQueries::getSoldPositionsForProduct_text(idProduct),
                                 &result);
    this->commonGetReceipts(result, query, &output);
    delete query;
    return output;
}

QVector<QSoldPosition> QSoldPositionCommands::getSoldPositionsForProduct(int idProduct,
                                                                         QDateTime startDate,
                                                                         QDateTime endDate)
{
    QVector<QSoldPosition> output;
    bool result = false;
    QSqlQuery *query = makeQuery(QSoldPositionQueries::
                                 getSoldPositionsForProduct_text(idProduct, startDate, endDate),
                                 &result);
    this->commonGetReceipts(result, query, &output);
    delete query;
    return output;
}

QVector<QSoldPosition> QSoldPositionCommands::getSoldPositionsForPointSale(int idPointSale)
{
    QVector<QSoldPosition> output;
    bool result = false;
    QSqlQuery *query = makeQuery(QSoldPositionQueries::getSoldPositionsForPointSale_text(idPointSale),
                                 &result);
    this->commonGetReceipts(result, query, &output);
    delete query;
    return output;
}

QVector<QSoldPosition> QSoldPositionCommands::getSoldPositionsForPointSale(int idPointSale, QDateTime startDate, QDateTime endDate)
{
    QVector<QSoldPosition> output;
    bool result = false;
    QSqlQuery *query = makeQuery(QSoldPositionQueries::
                                 getSoldPositionsForPointSale_text(idPointSale, startDate, endDate),
                                 &result);
    this->commonGetReceipts(result, query, &output);
    delete query;
    return output;
}

QVector<QSoldPosition> QSoldPositionCommands::getSoldPositionsForUser(int idUser)
{
    QVector<QSoldPosition> output;
    bool result = false;
    QSqlQuery *query = makeQuery(QSoldPositionQueries::getSoldPositionsForUser_text(idUser),
                                 &result);
    this->commonGetReceipts(result, query, &output);
    delete query;
    return output;
}

QVector<QSoldPosition> QSoldPositionCommands::getSoldPositionsForUser(int idUser,
                                                                      QDateTime startDate,
                                                                      QDateTime endDate)
{
    QVector<QSoldPosition> output;
    bool result = false;
    QSqlQuery *query = makeQuery(QSoldPositionQueries::
                                 getSoldPositionsForUser_text(idUser, startDate, endDate),
                                 &result);
    this->commonGetReceipts(result, query, &output);
    delete query;
    return output;
}


QSoldPosition QSoldPositionCommands::get(int idSoldPosition)
{
    QSoldPosition output;
    bool result = false;
    QSqlQuery *query = makeQuery(QSoldPositionQueries::get_text(idSoldPosition),
                                 &result);
    if (result) {
        if (query->next()) {
            this->commonGet(query, output);
        }
    }
    delete query;
    return output;
}

int QSoldPositionCommands::getId(const QSoldPosition &soldPosition)
{
    int output = -1;
    bool result = false;
    QSqlQuery *query = makeQuery(QSoldPositionQueries::getId_text(soldPosition),
                                 &result);
    if (result) {
        if (query->next()) {
            output = query->value(0).toInt();
        }
    }
    delete query;
    return output;
}

int QSoldPositionCommands::getIdWithoutReceipt(const QSoldPosition &soldPosition)
{
    int output = -1;
    bool result = false;
    QSqlQuery *query = makeQuery(QSoldPositionQueries::getIdWithoutReceipt_text(soldPosition),
                                 &result);
    if (result) {
        if (query->next()) {
            output = query->value(0).toInt();
        }
    }
    delete query;
    return output;
}

int QSoldPositionCommands::add(const QSoldPosition &soldPosition)
{
    int output = -1;
    int nextId = this->getNextId(QSoldPositionQueries::getTableName(),
                                 QSoldPositionQueries::getColumnName_ID());
    bool result = false;
    QSqlQuery *query = makeQuery(QSoldPositionQueries::add_text(nextId,soldPosition),
                                 &result);
    if (result) {
        output = this->getId(soldPosition);
    }
    delete query;
    return output;
}

int QSoldPositionCommands::add(int id, const QSoldPosition &soldPosition)
{
    int Output = -1;
    if (soldPosition.id == -1) {
        Output = this->add(soldPosition);
    }
    else {
        bool result = false;
        QSqlQuery *query = makeQuery(QSoldPositionQueries::add_text(id, soldPosition),
                                     &result);
        if (result) {
            Output = this->getId(soldPosition);
        }
        delete query;
    }

    return Output;
}

bool QSoldPositionCommands::edit(const QSoldPosition &soldPosition)
{
    bool output = false;
    QSqlQuery *query = makeQuery(QSoldPositionQueries::edit_text(soldPosition),
                                 &output);
    delete query;
    return output;
}

bool QSoldPositionCommands::edit(int id, const QSoldPosition &soldPosition)
{
    bool output = false;
    id = getIdWithoutReceipt(soldPosition);
    if (id == soldPosition.id) {
        output = this->edit(soldPosition);
    }
    else {
        this->remove(id);
        this->add(id, soldPosition);
    }
    return output;
}
void QSoldPositionCommands::remove(int idSoldPosition)
{
    bool result = false;
    QSqlQuery *query = makeQuery(QSoldPositionQueries::remove_text(idSoldPosition),
                                 &result);
    delete query;
}


void QSoldPositionCommands::commonGet(QSqlQuery *query, QSoldPosition &value)
{
    value.id = query->value(0).toInt();
    value.idUser = query->value(1).toInt();
    value.count = query->value(2).toInt();
    value.idProduct = query->value(3).toInt();
    value.idTypeProduct = query->value(4).toInt();
    value.idPrice = query->value(5).toInt();
    value.idVolumeProduct = query->value(6).toInt();
    value.idReceipt = query->value(7).toInt();
    value.idPointSale = query->value(8).toInt();
    value.numberInReceipt = query->value(9).toInt();
    value.date = query->value(10).toDateTime();
}

void QSoldPositionCommands::commonGetReceipts(bool result, QSqlQuery *query, QVector<QSoldPosition> *receipts)
{
    if (result) {
        QSoldPosition soldPosition;
        while (query->next()) {
            this->commonGet(query, soldPosition);

            receipts->push_back(soldPosition);
        }
    }
}
