#ifndef QSHIFTQUERIES_H
#define QSHIFTQUERIES_H

#include <QString>
#include "../commonFiles/SalesSystem/QShift/qshift.h"

class QShiftQueries
{
public:
    static QString createTable_text();
    static QString getTableName();
    static QString getColumnName_ID();
    static QString getShifts_text();
    static QString get_text(int idShift);
    static QString get_text(int idUser, int idPointSale);
    static QString add_text(int id, const QShift &shift);
    static QString edit_text(const QShift &shift);
    static QString open_text(int idUser, int IdPointSale, bool *newShift = nullptr);
    static QString close_text(const QShift &shift);
    static QString getId_text(const QShift &shift);
    static QString getOpenedShift_text(int idUser, int idPointSale);

private:
    QShiftQueries();
    static const QString TABLE;
    static const QString ID;
    static const QString OPEN_TIME;
    static const QString CLOSE_TIME;
    static const QString IS_OPEN;
    static const QString IS_CLOSE;
    static const QString ID_USER;
    static const QString ID_POINT_SALE;
};

#endif // QSHIFTQUERIES_H
