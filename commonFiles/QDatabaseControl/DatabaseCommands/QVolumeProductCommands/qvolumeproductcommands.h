#ifndef QVOLUMEPRODUCTCOMMANDS_H
#define QVOLUMEPRODUCTCOMMANDS_H

#include <QObject>
#include "../QParentDatabaseCommands/qparentdatabasecommands.h"
#include "../../../SalesSystem/QVolumeProduct/qvolumeproduct.h"
#include "QVolumeQueries/qvolumequeries.h"
#include "../QProductAndVolumeTableCommands/qproductandvolumetablecommands.h"

namespace DatabaseCommands {

class QVolumeProductCommands : public QParentDatabaseCommands
{
public:
    QVolumeProductCommands() = delete ;
    explicit QVolumeProductCommands(QSqlDatabase *database,
                                    QObject *parent = nullptr);
    ~QVolumeProductCommands() = default;

    bool createTable();
    bool clear();
    QVector<QVolumeProduct> getVolumes();
    QVector<QVolumeProduct> getVolumes(int idProduct);
    QVolumeProduct get(int idVolume);
    int add(const QVolumeProduct &volume);
    int add(int id, const QVolumeProduct &volume);
    bool edit(const QVolumeProduct &volume);
    int getId(const QVolumeProduct &volume);
    bool remove(int id, const QString &name);


private:
    QProductAndVolumeTableCommands *productAndVolumeCommands = nullptr;
    QVector<int> getIdProducts(int idVolume);
    bool linkProduct(int idVolume, int idProduct);
    bool unlinkProducts(int idVolume);
    void commonGet(QSqlQuery *query, QVolumeProduct &value);

};

}

#endif // QVOLUMEPRODUCTCOMMANDS_H
