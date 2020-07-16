#ifndef QPRODUCTANDVOLUMETABLECOMMANDS_H
#define QPRODUCTANDVOLUMETABLECOMMANDS_H

#include <QObject>
#include "../QParentDatabaseCommands/qparentdatabasecommands.h"
#include "QProductAndVolumeTableQueries/qproductandvolumetablequeries.h"

namespace DatabaseCommands {

class QProductAndVolumeTableCommands : public QParentDatabaseCommands
{
public:
    QProductAndVolumeTableCommands() = delete;
    ~QProductAndVolumeTableCommands() = default;
    explicit QProductAndVolumeTableCommands(QSqlDatabase *database,
                                            QObject *parent = nullptr);

    bool createTable();
    bool clear();
    QVector<int> getIdVolumes(int idProduct);
    QVector<int> getIdProducts(int idVolume);

    bool linkProduct(int idVolume, int idProduct);
    bool unlinkProducts(int idVolume);
};

}

#endif // QPRODUCTANDVOLUMETABLECOMMANDS_H
