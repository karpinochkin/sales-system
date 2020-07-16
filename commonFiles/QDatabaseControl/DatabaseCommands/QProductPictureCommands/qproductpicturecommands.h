#ifndef QPRODUCTPICTURECOMMANDS_H
#define QPRODUCTPICTURECOMMANDS_H

#include <QObject>
#include "../QParentDatabaseCommands/qparentdatabasecommands.h"
#include "../../../SalesSystem/QProductPicture/qproductpicture.h"
#include "QProductPictureQueries/qproductpicturequeries.h"

namespace DatabaseCommands {

class QProductPictureCommands : public QParentDatabaseCommands
{
public:
    QProductPictureCommands(QSqlDatabase *database,
                            QObject *parent = nullptr);
    QProductPictureCommands() = delete;
    ~QProductPictureCommands() = default;

    bool createTable();
    bool clear();
    QVector<QProductPicture> getPictures();
    QProductPicture get (int idPicture);
    int add (QProductPicture &picture);
    int add (int id, QProductPicture &picture);
    int getId(QProductPicture &picture);
    bool edit(QProductPicture &picture);
    bool remove(int id, const QString& name);

private:
    void commonGet(QSqlQuery *query, QProductPicture &value);
};

}

#endif // QPRODUCTPICTURECOMMANDS_H
