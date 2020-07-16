#ifndef QPRODUCTQUERIES_H
#define QPRODUCTQUERIES_H

#include <QString>
#include "../commonFiles/SalesSystem/QProduct/qproduct.h"

class QProductQueries
{
public:
    static QString clear_text();
    static QString getTableName();
    static QString getColumnName_ID();
    static QString createTable_text();
    static QString getProducts_text();
    static QString get_text(int idProduct);
    static QString add_text(int id, QProduct &product);
    static QString add_textEmptyPicture(int id, QProduct &product);
    static QString edit_text(QProduct &product);
    static QString edit_textEmptyPicture(QProduct &product);
    static QString getId_text(QProduct &product);
    static QString getAllID_text();

private:
    QProductQueries();
    static const QString TABLE;
    static const QString ID;
    static const QString NAME;
    static const QString DESCRIPTION;
    static const QString RED;
    static const QString GREEN;
    static const QString BLUE;
    static const QString PICTURE_ID;
    static const QString HASH;
};

#endif // QPRODUCTQUERIES_H
