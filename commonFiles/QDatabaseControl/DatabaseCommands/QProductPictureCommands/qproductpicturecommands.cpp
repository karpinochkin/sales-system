#include "qproductpicturecommands.h"

using namespace DatabaseCommands;

QProductPictureCommands::QProductPictureCommands(QSqlDatabase *database, QObject *parent)
    : QParentDatabaseCommands(database, parent)
{

}

bool QProductPictureCommands::createTable()
{
    bool result = false;
    QSqlQuery *query = makeQuery(QProductPictureQueries::createTable_text(),
                                 &result);
    if (result) {
        qDebug() << QProductPictureQueries::getTableName() + "is created";
    }
    delete query;
    return result;
}

bool QProductPictureCommands::clear()
{
    bool result = this->clearTable(QProductPictureQueries::getTableName());
    return result;
}

QVector<QProductPicture> QProductPictureCommands::getPictures()
{
    QVector<QProductPicture> pictures;
    bool result = false;
    QSqlQuery *query = makeQuery(QProductPictureQueries::getPictures_text(),
                                 &result);
    if (result) {
        QProductPicture picture;
        while (query->next()) {
            this->commonGet(query, picture);
            pictures.push_back(picture);
        }
    }
    delete query;
    return pictures;
}

QProductPicture QProductPictureCommands::get (int idPicture)
{
    QProductPicture output;
    bool result = false;
    QSqlQuery *query = makeQuery(QProductPictureQueries::get_text(idPicture),
                                 &result);
    if (result) {
        if (query->next()) {
            this->commonGet(query, output);
        }
    }
    delete query;
    return output;
}

int QProductPictureCommands::add (QProductPicture &picture)
{
    int output = -1;
    int nextId = getNextId(QProductPictureQueries::getTableName(),
                           QProductPictureQueries::getColumnName_ID());
    bool result = false;
    QSqlQuery *query = makeQuery(QProductPictureQueries::add_text(nextId, picture.name),
                                 ":imageData",
                                 picture.data,
                                 &result);
    if (result) {
        output = nextId;
    }
    delete query;
    return output;
}

int QProductPictureCommands::add(int id, QProductPicture &picture)
{
    int output = -1;
    bool result = false;
    QSqlQuery *query = makeQuery(QProductPictureQueries::add_text(id, picture.name),
                                 ":imageData",
                                 picture.data,
                                 &result);
    if (result) {
        output = id;
    }
    delete query;
    return output;
}

int QProductPictureCommands::getId(QProductPicture &picture)
{
    int output = -1;
    bool result = false;
    QSqlQuery *query = makeQuery(QProductPictureQueries::getId_text(picture.name),
                                 "imageData",
                                 picture.data,
                                 &result);
    if (result) {
        if (query->next()) {
            output = query->value(0).toInt();
        }
    }
    delete query;
    return output;
}


bool QProductPictureCommands::edit(QProductPicture &picture)
{
    bool result = false;
    QSqlQuery *query = makeQuery(QProductPictureQueries::edit_text(picture.id, picture.name),
                                 ":imageData",
                                 picture.data,
                                 &result);
    delete query;
    return result;
}

bool QProductPictureCommands::remove(int id, const QString &name)
{
    DatabaseCommands::RemoveInformation obj;
    obj.id = id;
    obj.name = name;
    obj.tableName = QProductPictureQueries::getTableName();
    obj.columnName_ID = QProductPictureQueries::getColumnName_ID();
    obj.columnName_Name = QProductPictureQueries::getColumnName_Name();

    bool result = QParentDatabaseCommands::remove(obj);
    return result;
}

void QProductPictureCommands::commonGet(QSqlQuery *query, QProductPicture &value)
{
    value.id = query->value(0).toInt();
    value.name = query->value(1).toString();
    value.data = query->value(2).toByteArray();
}

