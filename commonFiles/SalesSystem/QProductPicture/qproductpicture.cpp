#include "qproductpicture.h"

QProductPicture::QProductPicture()
{
    this->clear();
}

void QProductPicture::operator<<(QDataStream &stream)
{
    data.clear();
    stream >> id;
    stream >> name;
    stream >> data;
}

void QProductPicture::operator>>(QDataStream &stream)
{
    stream << id;
    stream << name;
    stream << data;
}

bool QProductPicture::isEmpty()
{
    bool Output = true;
    if (id == -1) {
        Output = true;
    }
    else {
        Output = false;
    }

    return Output;
}

void QProductPicture::clear()
{
    id = -1;
    name.clear();
    data.clear();
}
