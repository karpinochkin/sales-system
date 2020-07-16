#ifndef QSOLDPOSITIONCOMMANDS_H
#define QSOLDPOSITIONCOMMANDS_H

#include <QObject>
#include "../QParentDatabaseCommands/qparentdatabasecommands.h"
#include "../../../SalesSystem/QSoldPosition/qsoldposition.h"
#include "QSoldPositionQueries/qsoldpositionqueries.h"

namespace DatabaseCommands {

class QSoldPositionCommands : public QParentDatabaseCommands
{
public:
    QSoldPositionCommands() = delete;
    QSoldPositionCommands(QObject *parent = nullptr) = delete;
    QSoldPositionCommands(QSqlDatabase *database,
                          QObject *parent = nullptr);
    ~QSoldPositionCommands() = default;

    bool createTable();
    bool clear();
    void remove(int idSoldPosition);
    QVector<QSoldPosition> getSoldPositions();
    QVector<QSoldPosition> getSoldPositions(QDateTime startDate,
                                            QDateTime endDate);
    QVector<QSoldPosition> getSoldPositions(int idReceipt);
    QVector<QSoldPosition> getSoldPositionsForProduct(int idProduct);
    QVector<QSoldPosition> getSoldPositionsForProduct(int idProduct,
                                                      QDateTime startDate,
                                                      QDateTime endDate);
    QVector<QSoldPosition> getSoldPositionsForPointSale(int idPointSale);
    QVector<QSoldPosition> getSoldPositionsForPointSale(int idPointSale,
                                                        QDateTime startDate,
                                                        QDateTime endDate);
    QVector<QSoldPosition> getSoldPositionsForUser(int idUser);
    QVector<QSoldPosition> getSoldPositionsForUser(int idUser,
                                                   QDateTime startDate,
                                                   QDateTime endDate);
    QSoldPosition get(int idSoldPosition);
    int add(const QSoldPosition &soldPosition);
    int add(int id, const QSoldPosition &soldPosition);
    bool edit(const QSoldPosition &soldPosition);
    bool edit(int id, const QSoldPosition &soldPosition);
    int getId(const QSoldPosition &soldPosition);
    int getIdWithoutReceipt(const QSoldPosition &soldPosition);

private:
    void commonGet(QSqlQuery *query, QSoldPosition &value);
    void commonGetReceipts(bool result, QSqlQuery *query, QVector<QSoldPosition> *receipts);
};

}

#endif // QSOLDPOSITIONCOMMANDS_H
