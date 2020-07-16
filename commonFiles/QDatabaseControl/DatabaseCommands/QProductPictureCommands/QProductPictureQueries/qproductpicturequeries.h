#ifndef QPRODUCTPRICTUREQUERIES_H
#define QPRODUCTPRICTUREQUERIES_H

#include <QString>

class QProductPictureQueries
{
public:
    static QString getTableName();
    static QString getColumnName_ID();
    static QString getColumnName_Name();
    static QString createTable_text();
    static QString getPictures_text();
    static QString get_text(int idPicture);
    static QString add_text(int nextId , QString &name);
    static QString getId_text(QString &name);
    static QString edit_text(int id, QString &name);
    static QString remove_text(int id, const QString &name);

private:
    QProductPictureQueries();

    static const QString TABLE;
    static const QString ID;
    static const QString NAME;
    static const QString DATA;
};

#endif // QPRODUCTPRICTUREQUERIES_H

