#include "productimageprovider.h"

ProductImageProvider::ProductImageProvider(QQmlImageProviderBase::ImageType type, QObject *parent, QQmlImageProviderBase::Flags flags)
    : QObject(parent) , QQuickImageProvider(type,flags)
{

}

QImage ProductImageProvider::requestImage(const QString &id, QSize *size, const QSize &requestedSize)
{
    Q_UNUSED(size)
    Q_UNUSED(requestedSize)

    emit signalGetImageFromDB(id.toInt());

    return newImage;
}

void ProductImageProvider::slotGetImageFromDB(QImage image)
{
    newImage = image;
}
