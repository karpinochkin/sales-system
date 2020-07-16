#ifndef QSALESPRODUCTPICTURE_H
#define QSALESPRODUCTPICTURE_H

#include "../QSalesObjects/qsalesobjects.h"

class QProductPicture : public QSalesObjects
{
public:
    explicit QProductPicture();
    ~QProductPicture() = default;

    int id;
    QString name;
    QByteArray data;

    void operator <<(QDataStream &stream);
    void operator >>(QDataStream &stream);

    bool isEmpty();
    void clear();
};

Q_DECLARE_METATYPE( QProductPicture )
#endif // QSALESPRODUCTPICTURE_H
