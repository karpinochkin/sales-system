#ifndef QPOINTSALECOMMANDS_H
#define QPOINTSALECOMMANDS_H

#include <QObject>
#include "../QParentDatabaseCommands/qparentdatabasecommands.h"
#include "../../../SalesSystem/QPointSale/qpointsale.h"
#include "QPointSaleQueries/qpointsalequeries.h"
#include "../QPointSaleAndCategoryTableCommands/qpointsaleandcategorytablecommands.h"

namespace DatabaseCommands {

class QPointSaleCommands : public QParentDatabaseCommands
{
public:
    QPointSaleCommands() = delete;
    ~QPointSaleCommands() = default;
    explicit QPointSaleCommands(QSqlDatabase *database,
                                QObject *parent = nullptr);


    bool createTable();
    bool clear();
    bool createPointSaleAndProductTable();
    bool createPointSaleAndCategoryTable();
    QVector<QPointSale> getPointSales();
    QPointSale get(int idPointSale);
    bool edit(const QPointSale &pointSale);
    int add(const QPointSale &pointSale);
    int add(int id, const QPointSale &pointSale);
    int getId(const QPointSale &pointSale);
    QVector<int> getProductsId(int idPointSale);
    bool remove(int id, const QString &name);

private:
    QPointSaleAndCategoryTableCommands *pointAndCategoryTable;

    QVector<int> getCategoriesId(int idPointSale);
    bool unlinkProducts(int idPointSale);
    bool unlinkCategories(int idPointSale);
    bool linkProduct(int idPointSale, int idProdusct);
    bool linkCategory(int idPointSale, int idCategory);
    void linkAllCategories(const QPointSale &pointSale);
    void linkAllProducts(const QPointSale &pointSale);
    void commonGet(QSqlQuery *query, QPointSale &output);
};

}

#endif // QPOINTSALECOMMANDS_H
