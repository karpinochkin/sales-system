#include "qshiftcommands.h"

using namespace DatabaseCommands;

QShiftCommands::QShiftCommands(QSqlDatabase *database, QObject *parent)
    : QParentDatabaseCommands(database, parent)
{

}

bool QShiftCommands::createTable()
{
    bool result = false;
    QSqlQuery *query = makeQuery(QShiftQueries::createTable_text(),
                                 &result);
    if (result) {
        qDebug() << QShiftQueries::getTableName() + " is created";
    }
    delete query;
    return result;
}

bool QShiftCommands::clear()
{
    bool result = this->clearTable(QShiftQueries::getTableName());
    return result;
}

QVector<QShift> QShiftCommands::getShifts()
{
    QVector<QShift> output;
    bool result = false;
    QSqlQuery *query = makeQuery(QShiftQueries::getShifts_text(),
                                 &result);
    if (result) {
        QShift shift;
        while (query->next()) {
            this->commonGet(query, shift);

            output.push_back(shift);
        }
    }
    delete query;
    return output;
}

QShift QShiftCommands::get(int idShift)
{
    QShift output;
    bool result = false;
    QSqlQuery *query = makeQuery(QShiftQueries::get_text(idShift),
                                 &result);
    if (result) {
        if (query->next()) {
            this->commonGet(query, output);
        }
    }
    delete query;
    return output;
}

QShift QShiftCommands::get(int idUser, int idPointSale)
{
    QShift output;
    bool result = false;
    QSqlQuery *query = makeQuery(QShiftQueries::get_text(idUser, idPointSale),
                                 &result);
    if (result) {
        if (query->next()) {
            this->commonGet(query, output);
        }
    }
    delete query;
    return output;
}

QShift QShiftCommands::getOpenedShift(int idUser, int idPointSale)
{
    QShift output;
    bool result = false;
    QSqlQuery *query = makeQuery(QShiftQueries::getOpenedShift_text(idUser, idPointSale),
                                 &result);
    if (result) {
        if (query->next()) {
            this->commonGet(query, output);
        }
    }
    delete query;
    return output;
}

int QShiftCommands::getId(const QShift &shift)
{
    int output = -1;
    bool result = false;
    QSqlQuery *query = makeQuery(QShiftQueries::getId_text(shift),
                                 &result);
    if (result) {
        if (query->next()) {
            output = query->value(0).toInt();
        }
    }
    delete query;
    return output;
}

int QShiftCommands::add(const QShift &shift)
{
    int output = -1;
    int nextId = this->getNextId(QShiftQueries::getTableName(),
                                 QShiftQueries::getColumnName_ID());
    bool result = false;
    QSqlQuery *query = makeQuery(QShiftQueries::add_text(nextId, shift),
                                 &result);
    if (result) {
        output = this->getId(shift);
    }
    delete query;
    return output;
}

int QShiftCommands::add(int id, const QShift &shift)
{
    int output = -1;

    bool result = false;
    QSqlQuery *query = makeQuery(QShiftQueries::add_text(id, shift),
                                 &result);
    if (result) {
        output = this->getId(shift);
    }
    delete query;
    return output;
}

bool QShiftCommands::edit(const QShift &shift)
{
    bool output = false;
    QSqlQuery *query = makeQuery(QShiftQueries::edit_text(shift),
                                 &output);
    delete query;
    return output;
}

bool QShiftCommands::isOpen(int idUser, int idPointSale)
{
    bool output = false;
    QShift shift = this->getOpenedShift(idUser, idPointSale);

    if (shift.id != -1) {
        output = true;
    }
    return output;
}

QShift QShiftCommands::open(int idUser, int idPointSale, bool *newShift)
{
    QShift output;
    bool isOpen = this->isOpen(idUser, idPointSale);

    if(isOpen) {
        output = this->getOpenedShift(idUser, idPointSale);
        if (newShift != nullptr) {
            *newShift = false;
        }
    } else {
        output.openTime = QDateTime::currentDateTime();
        output.open = true;
        output.closeTime = QDateTime::currentDateTime();
        output.idUser = idUser;
        output.idPointSale = idPointSale;
        output.close = false;

        output.id = this->add(output);

        if (newShift != nullptr) {
            *newShift = true;
        }
    }
    return output;
}

bool QShiftCommands::close(QShift &shift)
{
    bool output = false;
    bool isOpen = this->isOpen(shift.idUser, shift.idPointSale);
    if (isOpen) {
        shift.closeTime = QDateTime::currentDateTime();
        shift.close = true;
        this->edit(shift);
        output = true;
    } else {
        output = false;
        qDebug() << "Error close shift: open shift not found! shift info "
                 << shift.toString();
    }
    return output;
}

void QShiftCommands::commonGet(QSqlQuery *query, QShift &value)
{
    value.id = query->value(0).toInt();
    value.openTime = query->value(1).toDateTime();
    value.closeTime = query->value(2).toDateTime();
    value.open = query->value(3).toBool();
    value.close = query->value(4).toBool();
    value.idUser = query->value(5).toInt();
    value.idPointSale = query->value(6).toInt();
}
