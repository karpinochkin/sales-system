#ifndef QPRODUCTANDVOLUMETABLEQUERIES_H
#define QPRODUCTANDVOLUMETABLEQUERIES_H

#include <QString>

class QProductAndVolumeTableQueries
{
public:
    static QString createTable_text();
    static QString getIdVolumes_text(int idProduct);
    static QString getIdProducts_text(int idVolume);
    static QString linkProduct(int idVolume, int idProduct);
    static QString unlinkProducts(int idVolume);

private:
    QProductAndVolumeTableQueries();
};

#endif // QPRODUCTANDVOLUMETABLEQUERIES_H
