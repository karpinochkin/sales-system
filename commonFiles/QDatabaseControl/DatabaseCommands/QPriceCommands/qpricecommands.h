#ifndef QPRICECOMMANDS_H
#define QPRICECOMMANDS_H

#include <QObject>
#include "../QParentDatabaseCommands/qparentdatabasecommands.h"
#include "../../../SalesSystem/QPrice/qprice.h"
#include "../QPointSaleAndPriceTableCommands/qpointsaleandpricetablecommands.h"
#include "QPriceQueries/qpricequeries.h"

namespace DatabaseCommands {

class QPriceCommands : public QParentDatabaseCommands
{
public:
    explicit QPriceCommands(QObject *parent = nullptr) = delete;
    ~QPriceCommands() = default;
    QPriceCommands(QSqlDatabase *database,
                   QObject *parent = nullptr);

    bool createTable();
    bool createPointSaleAndPriceTable();
    bool clear();
    QVector<QPrice> getPrices();
    QVector<QPrice> getPrices(int idPointSale);
    QPrice get(int idPrice);
    QPrice get(int idCategory, int idDrink, int idVolume);
    int add(const QPrice &price);
    int add(int id, const QPrice &price);
    bool edit(const QPrice &price);
    int getId(const QPrice &price);
    QVector<int> getIdPointSales(int idPrice);

private:
    QPointSaleAndPriceTableCommands *pointSaleAndPrice = nullptr;
    bool unlinkPointSales(int idPrice);
    bool linkPointSale(int idPrice, int idPointSale);
    void commonGet(QSqlQuery *query, QPrice &output);
};

}

#endif // QPRICECOMMANDS_H
