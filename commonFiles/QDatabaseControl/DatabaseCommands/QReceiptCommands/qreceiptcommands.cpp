#include "qreceiptcommands.h"

using namespace DatabaseCommands;

QReceiptCommands::QReceiptCommands(QSqlDatabase *database, QObject *parent)
    : QParentDatabaseCommands(database, parent)
{

}

bool QReceiptCommands::createTable()
{
    bool result = false;
    QSqlQuery *query = makeQuery(QReceiptQueries::createTable_text(),
                                 &result);
    if (result) {
        qDebug() << QReceiptQueries::getTableName() + " is created";
    }
    delete query;
    return result;
}

bool QReceiptCommands::clear()
{
    bool result = this->clearTable(QReceiptQueries::getTableName());
    return result;
}

QHash<int, QReceipt> QReceiptCommands::getReceiptsHash()
{
    QHash<int, QReceipt> output;
    bool result = false;
    QSqlQuery *query = makeQuery(QReceiptQueries::getReceipts_text(),
                                 &result);
    if(result) {
        QReceipt receipt;
        while (query->next()) {
            this->commonGet(query, receipt);

            output.insert(receipt.id, receipt);
        }
    }
    delete query;
    return output;

}

QHash<int, QReceipt> QReceiptCommands::getReceiptsHash(QDateTime startDate, QDateTime endDate)
{
    QHash<int, QReceipt> output;
    bool result = false;
    QSqlQuery *query = makeQuery(QReceiptQueries::getReceipts_text(startDate, endDate),
                                 &result);
    if(result) {
        QReceipt receipt;
        while (query->next()) {
            this->commonGet(query, receipt);

            output.insert(receipt.id, receipt);
        }
    }
    delete query;
    return output;
}

QVector<QReceipt> QReceiptCommands::getReceipts()
{
    QVector<QReceipt> output;
    bool result = false;
    QSqlQuery *query = makeQuery(QReceiptQueries::getReceipts_text(),
                                 &result);
    this->commonGetReceipts(result, query, &output);
    delete query;
    return output;
}

QVector<QReceipt> QReceiptCommands::getReceipts(QDateTime startDate, QDateTime endDate)
{
    QVector<QReceipt> output;
    bool result = false;
    QSqlQuery *query = makeQuery(QReceiptQueries::getReceipts_text(startDate,
                                                                   endDate),
                                 &result);
    this->commonGetReceipts(result, query, &output);
    delete query;
    return output;
}

QVector<QReceipt> QReceiptCommands::getReceipts(int idShift)
{
    QVector<QReceipt> output;
    bool result = false;
    QSqlQuery *query = makeQuery(QReceiptQueries::getReceipts_text(idShift),
                                 &result);
    this->commonGetReceipts(result, query, &output);
    delete query;
    return output;
}

QVector<QReceipt> QReceiptCommands::getReceiptsForPointSale(int idPointSale)
{
    QVector<QReceipt> output;
    bool result = false;
    QSqlQuery *query = makeQuery(QReceiptQueries::getReceiptsForPointSale_text(idPointSale),
                                 &result);
    this->commonGetReceipts(result, query, &output);
    delete query;
    return output;
}

QVector<QReceipt> QReceiptCommands::getReceiptsForPointSaleByDateRange(int idPointSale,
                                                                       QDateTime startDate,
                                                                       QDateTime endDate)
{
    QVector<QReceipt> output;
    bool result = false;
    QSqlQuery *query = makeQuery(QReceiptQueries::getReceiptsForPointSaleByDateRange_text(idPointSale, startDate, endDate),
                                 &result);
    this->commonGetReceipts(result, query, &output);

    delete query;
    return output;
}

QReceipt QReceiptCommands::get(int idReceipt)
{
    QReceipt output;
    bool result = false;
    QSqlQuery *query = makeQuery(QReceiptQueries::get_text(idReceipt),
                                 &result);
    if(result) {
        QReceipt receipt;
        if(query->next()) {
            this->commonGet(query, receipt);
        }
    }
    delete query;
    return output;
}

int QReceiptCommands::getId(const QReceipt &receipt)
{
    int output = -1;
    bool result = false;
    QSqlQuery *query = makeQuery(QReceiptQueries::getId_text(receipt),
                                 &result);
    if (result) {
        if (query->next()) {
            output = query->value(0).toInt();
        }
    }
    delete query;
    return output;
}

int QReceiptCommands::add(const QReceipt &receipt)
{
    int output = -1;
    int nextId = this->getNextId(QReceiptQueries::getTableName(),
                                 QReceiptQueries::getColumnName_ID());
    bool result = false;
    QSqlQuery * query = makeQuery(QReceiptQueries::add_text(nextId, receipt),
                                  &result);
    if (result) {
        output = this->getId(receipt);
    }
    delete query;
    return output;
}

int QReceiptCommands::add(int id, const QReceipt &receipt)
{
    int output = -1;
    if (id == -1) {
        output = this->add(receipt);
    }
    else {
        bool result = false;
        QSqlQuery * query = makeQuery(QReceiptQueries::add_text(id, receipt),
                                      &result);
        if (result) {
            output = this->getId(receipt);
        }
        delete query;
    }

    return output;
}


bool QReceiptCommands::edit(const QReceipt &receipt)
{
    bool output = false;
    QSqlQuery *query = makeQuery(QReceiptQueries::edit_text(receipt),
                                 &output);
    delete query;
    return output;
}

bool QReceiptCommands::edit(int id, const QReceipt &receipt)
{
    bool output = false;
    id = getId(receipt);
    QSqlQuery *query = makeQuery(QReceiptQueries::edit_text(id, receipt),
                                 &output);
    delete query;
    return output;
}

void QReceiptCommands::commonGetReceipts(bool result, QSqlQuery *query, QVector<QReceipt> *receipts)
{
    if(result) {
        QReceipt receipt;
        while (query->next()) {
            this->commonGet(query, receipt);

            receipts->push_back(receipt);
        }
    }
}

void QReceiptCommands::commonGet(QSqlQuery *query, QReceipt &receipt)
{
    receipt.id = query->value(0).toInt();
    receipt.dateTime = query->value(1).toDateTime();
    receipt.sum = query->value(2).toDouble();
    receipt.idPointSale = query->value(3).toInt();
    receipt.idShift = query->value(4).toInt();
}

