#ifndef PRODUCTIMAGEPROVIDER_H
#define PRODUCTIMAGEPROVIDER_H

#include "QQuickImageProvider"
#include <QDebug>

class ProductImageProvider : public QObject, public QQuickImageProvider
{
    Q_OBJECT
public:
    explicit ProductImageProvider(ImageType type, QObject *parent = nullptr, Flags flags = nullptr);
    ~ProductImageProvider() override = default;

    QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize) override;

private:
    QImage newImage;

signals:
    void signalGetImageFromDB(int);

public slots:
    void slotGetImageFromDB(QImage);
};

#endif // PRODUCTIMAGEPROVIDER_H
