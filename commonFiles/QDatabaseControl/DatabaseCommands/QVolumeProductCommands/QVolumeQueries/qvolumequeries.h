#ifndef QVOLUMEQUERIES_H
#define QVOLUMEQUERIES_H

#include <QString>
#include "../commonFiles/SalesSystem/QVolumeProduct/qvolumeproduct.h"

class QVolumeQueries
{
public:
    static QString createTable_text();
    static QString getTableName();
    static QString getColumnName_ID();
    static QString getColumnName_Name();
    static QString getVolumes_text();
    static QString get_text(int idVolume);
    static QString add_text(int id, const QVolumeProduct &volume);
    static QString edit_text(const QVolumeProduct &volume);
    static QString getId_text(const QVolumeProduct &volume);
    static QString remove_text(int id, const QString &name);

private:
    QVolumeQueries();
    static const QString TABLE;
    static const QString ID;
    static const QString NAME;
    static const QString VOLUME;
    static const QString DESCRIPTION;
    static const QString UNIT;
};

#endif // QVOLUMEQUERIES_H
