#ifndef QRECEIPTQUERIES_H
#define QRECEIPTQUERIES_H

#include <QString>
#include "../commonFiles/SalesSystem/QReceipt/qreceipt.h"

class QReceiptQueries
{
public:
    static QString createTable_text();
    static QString getTableName();
    static QString getColumnName_ID();
    static QString getReceipts_text();
    static QString getReceipts_text(QDateTime startDate, QDateTime endDate);
    static QString getReceipts_text(int idShift);
    static QString getReceiptsForPointSale_text(int idPointSale);
    static QString getReceiptsForPointSaleByDateRange_text(int idPointSale, QDateTime startDate, QDateTime endDate);
    static QString get_text(int idReceipt);
    static QString add_text(int id, const QReceipt &receipt);
    static QString edit_text(const QReceipt &receipt);
    static QString edit_text(int id, const QReceipt &receipt);
    static QString getId_text(const QReceipt &receipt);

private:
    QReceiptQueries();

    static const QString TABLE;
    static const QString ID;
    static const QString DATE;
    static const QString SUM;
    static const QString ID_POINT_SALE;
    static const QString ID_SHIFT;
};

#endif // QRECEIPTQUERIES_H
