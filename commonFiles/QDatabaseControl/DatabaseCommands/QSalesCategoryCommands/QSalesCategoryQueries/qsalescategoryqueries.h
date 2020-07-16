#ifndef QSALESCATEGORYQUERIES_H
#define QSALESCATEGORYQUERIES_H

#include <QString>
#include "../commonFiles/SalesSystem/QSalesСategory/qsalescategory.h"

class QSalesCategoryQueries
{
public:
    static QString getTableName();
    static QString getColumnName_ID();
    static QString getColumnName_Name();
    static QString createTable_text();
    static QString getCategories_QueryText();
    static QString getCategories_QueryText(int idPointSale);
    static QString get_QueryText(int idCategory);
    static QString edit_QueryText(QSalesCategory &category);
    static QString add_QueryText(int id, QSalesCategory &category);
    static QString getId_QueryText(QSalesCategory &category);

private:
    QSalesCategoryQueries();

    static const QString TABLE;
    static const QString ID;
    static const QString NAME;
    static const QString DESCRIPTION;
    static const QString RED;
    static const QString GREEN;
    static const QString BLUE;
};

#endif // QSALESCATEGORYQUERIES_H
