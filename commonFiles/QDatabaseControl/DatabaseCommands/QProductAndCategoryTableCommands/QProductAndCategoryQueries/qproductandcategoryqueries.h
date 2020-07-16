#ifndef QPRODUCTANDCATEGORYQUERIES_H
#define QPRODUCTANDCATEGORYQUERIES_H

#include <QString>

class QProductAndCategoryQueries
{
public:
    static QString createTable_text();
    static QString getIdCategories_text(int idProduct);
    static QString getIdProducts_text(int idCategory);
    static QString linkCategory(int idProduct, int idCategory);
    static QString unlinkCategories(int idProduct);

private:
    QProductAndCategoryQueries();
};

#endif // QPRODUCTANDCATEGORYQUERIES_H
