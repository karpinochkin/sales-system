#ifndef QPRODUCTANDCATEGORYTABLECOMMANDS_H
#define QPRODUCTANDCATEGORYTABLECOMMANDS_H

#include <QObject>
#include "../QParentDatabaseCommands/qparentdatabasecommands.h"
#include "QProductAndCategoryQueries/qproductandcategoryqueries.h"

namespace DatabaseCommands {

class QProductAndCategoryTableCommands : public QParentDatabaseCommands
{
public:
    QProductAndCategoryTableCommands(QObject *parent = nullptr) = delete;
    ~QProductAndCategoryTableCommands() = default;
    QProductAndCategoryTableCommands(QSqlDatabase *database,
                                     QObject *parent = nullptr);

    bool createTable();
    bool clear();
    QVector<int> getIdCategories(int idProduct);
    QVector<int> getIdProducts(int idCategory);
    bool linkCategory(int idProduct, int idCategory);
    bool unlinkCategories(int idProduct);
};

}
#endif // QPRODUCTANDCATEGORYTABLECOMMANDS_H
