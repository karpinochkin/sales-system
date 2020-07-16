#ifndef QSOLDPOSITIONQUERIES_H
#define QSOLDPOSITIONQUERIES_H

#include <QString>
#include "../commonFiles/SalesSystem/QSoldPosition/qsoldposition.h"

class QSoldPositionQueries
{
public:
    static QString createTable_text();
    static QString getTableName();
    static QString getColumnName_ID();
    static QString remove_text(int idSoldPosition);
    static QString getSoldPositions_text();
    static QString getSoldPositions_text(QDateTime startDate, QDateTime endDate);
    static QString getSoldPositions_text(int idReceipt);
    static QString getSoldPositionsForProduct_text(int idProduct);
    static QString getSoldPositionsForProduct_text(int idProduct,
                                                   QDateTime startDate,
                                                   QDateTime endDate);
    static QString getSoldPositionsForPointSale_text(int idPointSale);
    static QString getSoldPositionsForPointSale_text(int idPointSale,
                                                     QDateTime startDate,
                                                     QDateTime endDate);
    static QString getSoldPositionsForUser_text(int idUser);
    static QString getSoldPositionsForUser_text(int idUser,
                                                QDateTime startDate,
                                                QDateTime endDate);
    static QString get_text(int idSoldPosition);
    static QString add_text(int id, const QSoldPosition &soldPosition);
    static QString edit_text(const QSoldPosition &soldPosition);
    static QString getId_text(const QSoldPosition &soldPosition);
    static QString getIdWithoutReceipt_text(const QSoldPosition &soldPosition);

private:
    QSoldPositionQueries();

    static const QString TABLE;
    static const QString ID;
    static const QString ID_USER;
    static const QString COUNT;
    static const QString ID_PRODUCT;
    static const QString ID_TYPE;
    static const QString ID_PRICE;
    static const QString ID_VOLUME;
    static const QString ID_RECEIPT;
    static const QString ID_POINT_SALE;
    static const QString NUMBER_IN_RECEIPT;
    static const QString DATE;
};

#endif // QSOLDPOSITIONQUERIES_H
