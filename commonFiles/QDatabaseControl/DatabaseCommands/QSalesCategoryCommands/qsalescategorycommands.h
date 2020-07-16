#ifndef QSALESCATEGORYCOMMANDS_H
#define QSALESCATEGORYCOMMANDS_H

#include <QObject>
#include "../QParentDatabaseCommands/qparentdatabasecommands.h"
#include "../../../SalesSystem/QSalesСategory/qsalescategory.h"
#include "QSalesCategoryQueries/qsalescategoryqueries.h"
#include "../QPointSaleAndCategoryTableCommands/qpointsaleandcategorytablecommands.h"

namespace DatabaseCommands {

class QSalesCategoryCommands : public QParentDatabaseCommands
{
public:
    QSalesCategoryCommands() = delete;
    explicit QSalesCategoryCommands(QSqlDatabase *database,
                                    QObject *parent = nullptr);
    ~QSalesCategoryCommands() = default;

    bool createTable();
    bool clear();
    QVector<QSalesCategory> getCategories();
    QVector<QSalesCategory> getCategories(int idPointSale);
    QSalesCategory get(int idCategory);
    bool edit(QSalesCategory &category);
    int add(QSalesCategory &category);
    int add(int id, QSalesCategory &category);
    int getId(QSalesCategory &category);
    bool remove(int id, const QString &name);
    QVector<int> getIdPointSales(int idCategory);

private:
    QPointSaleAndCategoryTableCommands *pointAndCategoryTable = nullptr;

    bool linkPointSale(int idCategory, int idPointSale);
    bool unlinkPointSales(int idCategory);
    void commonGet(QSqlQuery *query, QSalesCategory &value);
};

}

#endif // QSALESCATEGORYCOMMANDS_H
