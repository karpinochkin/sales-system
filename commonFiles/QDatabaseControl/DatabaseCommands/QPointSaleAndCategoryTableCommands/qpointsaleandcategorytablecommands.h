#ifndef QPOINTSALEANDCATEGORYTABLECOMMANDS_H
#define QPOINTSALEANDCATEGORYTABLECOMMANDS_H

#include <QObject>
#include "../QParentDatabaseCommands/qparentdatabasecommands.h"
#include "../../../SalesSystem/QPointSale/qpointsale.h"
#include "QPointSaleAndCategoryTableQueries/qpointsaleandcategorytablequeries.h"

namespace DatabaseCommands {

class QPointSaleAndCategoryTableCommands : public QParentDatabaseCommands
{
    Q_OBJECT
public:
    QPointSaleAndCategoryTableCommands() = delete;
    ~QPointSaleAndCategoryTableCommands() = default;
    explicit QPointSaleAndCategoryTableCommands(QSqlDatabase *database,
                                                QObject *parent = nullptr);

    bool createTable();
    bool clear();
    QVector<int> getCategoriesId(int idPointSale);
    bool unlinkCategories(int idPointSale);
    bool linkCategory(int idPointSale, int idCategory);
    QVector<int> getIdPointSales(int idCategory);
    bool linkPointSale(int idCategory, int idPointSale);
    bool unlinkPointSales(int idCategory);
};

}

#endif // QPOINTSALEANDCATEGORYTABLECOMMANDS_H
