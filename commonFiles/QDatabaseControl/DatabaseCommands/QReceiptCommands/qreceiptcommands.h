#ifndef QRECEIPTCOMMANDS_H
#define QRECEIPTCOMMANDS_H

#include <QObject>
#include "../QParentDatabaseCommands/qparentdatabasecommands.h"
#include "../../../SalesSystem/QReceipt/qreceipt.h"
#include "QReceiptQueries/qreceiptqueries.h"

namespace DatabaseCommands {

class QReceiptCommands : public QParentDatabaseCommands
{
public:
    QReceiptCommands() = delete;
    QReceiptCommands(QObject *parent = nullptr) = delete;
    explicit QReceiptCommands(QSqlDatabase *database,
                     QObject *parent = nullptr);
    ~QReceiptCommands() = default;

    bool createTable();
    bool clear();
    QHash<int, QReceipt> getReceiptsHash();
    QHash<int, QReceipt> getReceiptsHash(QDateTime startDate, QDateTime endDate);
    QVector<QReceipt> getReceipts();
    QVector<QReceipt> getReceipts(QDateTime startDate, QDateTime endDate);
    QVector<QReceipt> getReceipts(int idShift);
    QVector<QReceipt> getReceiptsForPointSale(int idPointSale);
    QVector<QReceipt> getReceiptsForPointSaleByDateRange(int idPointSale, QDateTime startDate, QDateTime endDate);
    QReceipt get(int idReceipt);
    int add(const QReceipt &receipt);
    int add(int id, const QReceipt &receipt);
    bool edit(const QReceipt &receipt);
    bool edit(int id, const QReceipt &receipt);
    int getId(const QReceipt &receipt);

private:
    void commonGet(QSqlQuery *query, QReceipt &receipt);
    void commonGetReceipts(bool result, QSqlQuery *query, QVector<QReceipt> *receipts);
};

}

#endif // QRECEIPTCOMMANDS_H
