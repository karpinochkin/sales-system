#ifndef QSHIFTCOMMANDS_H
#define QSHIFTCOMMANDS_H

#include "../QParentDatabaseCommands/qparentdatabasecommands.h"
#include "../../../SalesSystem/QShift/qshift.h"
#include "QShiftQueries/qshiftqueries.h"

namespace DatabaseCommands {

class QShiftCommands : public QParentDatabaseCommands
{
public:
    QShiftCommands() = delete;
    QShiftCommands(QObject *parent = nullptr) = delete;
    QShiftCommands(QSqlDatabase *database, QObject *parent = nullptr);
    ~QShiftCommands() = default;

    bool createTable();
    bool clear();
    QVector<QShift> getShifts();
    QShift get(int idShift);
    QShift get(int idUser, int idPointSale);
    int add(const QShift &shift);
    int add(int id, const QShift &shift);
    bool edit(const QShift &shift);
    QShift open(int idUser, int IdPointSale, bool *newShift = nullptr);
    bool close(QShift &shift);
    int getId(const QShift &shift);

private:
    QShift getOpenedShift(int idUser, int idPointSale);
    bool isOpen(int idUser, int idPointSale);
    void commonGet(QSqlQuery *query, QShift &value);
};

}

#endif // QSHIFTCOMMANDS_H
