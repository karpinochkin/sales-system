#ifndef QSALESPRODUCT_H
#define QSALESPRODUCT_H

#include "../QColorConsole/qcolorconsole.h"
#include "../QSalesByteArray/qsalesbytearray.h"
#include "../QSalesObjects/qsalesobjects.h"

class QProduct : public QSalesObjects
{
public:
    explicit QProduct() = default;
    ~QProduct() = default;

    int id;
    QString name;
    QString description;
    QVector<int> idCategories;
    QColorConsole color;
    int idPicture;
    QString pictureHash;

    void operator <<(QDataStream &stream);
    void operator >>(QDataStream &stream);

    bool isEmpty();
    void clear();
    QString toString();
    QByteArray toByteArray();
    void fromByteArray(QByteArray &data);

private:
    void setIdCategoriesFromStream(int size, QDataStream &stream);
    void setIdCategoriesToStream(QDataStream &stream);
};

Q_DECLARE_METATYPE( QProduct )
#endif // QSALESPRODUCT_H
