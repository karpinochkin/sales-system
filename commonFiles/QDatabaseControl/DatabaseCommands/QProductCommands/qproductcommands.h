#ifndef QPRODUCTCOMMANDS_H
#define QPRODUCTCOMMANDS_H

#include <QObject>
#include "../QParentDatabaseCommands/qparentdatabasecommands.h"
#include "../../../SalesSystem/QProduct/qproduct.h"
#include "../QProductAndVolumeTableCommands/qproductandvolumetablecommands.h"
#include "../QProductAndCategoryTableCommands/qproductandcategorytablecommands.h"
#include "QProductQueries/qproductqueries.h"
namespace DatabaseCommands {

class QProductCommands : public QParentDatabaseCommands
{
public:
    explicit QProductCommands(QObject *parent = nullptr) = delete;
    ~QProductCommands() = default;
    explicit QProductCommands(QSqlDatabase *database,
                     QObject *parent = nullptr);

    bool createTable();
    bool clear();
    QVector<QProduct> getProducts();
    QVector<QProduct> getProducts(int idCategory);
    QVector<int> getAllId();
    QProduct get(int idProduct);
    int add(QProduct &product);
    int add(int id, QProduct &product);
    bool edit(QProduct &product);
    QVector<int> getIdVolumes(int idProduct);
    int getId(QProduct &product);
    QVector<int> getIdCategories(int idProduct);

    QProductAndVolumeTableCommands *productAndVolumeTable = nullptr;
    QProductAndCategoryTableCommands *productAndCategoryTable = nullptr;

private:
    bool linkCategory(int idProduct, int idCategory);
    bool unlinkCategories(int idProduct);

    void commonGet(QSqlQuery *query, QProduct &value);
};

}

#endif // QPRODUCTCOMMANDS_H
