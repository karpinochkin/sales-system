#ifndef QPOINTSALEANDPRICETABLECOMMANDS_H
#define QPOINTSALEANDPRICETABLECOMMANDS_H

#include <QObject>
#include "../QParentDatabaseCommands/qparentdatabasecommands.h"
#include "QPointSaleAndPriceQueries/qpointsaleandpricequeries.h"

namespace DatabaseCommands {

class QPointSaleAndPriceTableCommands : public QParentDatabaseCommands
{
    Q_OBJECT
public:
    explicit QPointSaleAndPriceTableCommands(QObject *parent = nullptr) = delete;
    ~QPointSaleAndPriceTableCommands() = default;
    QPointSaleAndPriceTableCommands(QSqlDatabase *database,
                                    QObject *parent = nullptr);

    bool createTable();
    bool clear();
    QVector<int> getIdPrices(int idPointSale);
    QVector<int> getIdPointSales(int idPrice);
    bool unlinkPointSales(int idPrice);
    bool linkPointSale(int idPrice, int idPointSale);
};

}


#endif // QPOINTSALEANDPRICETABLECOMMANDS_H
