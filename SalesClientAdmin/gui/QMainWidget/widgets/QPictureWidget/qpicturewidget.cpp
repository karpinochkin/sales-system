#include "qpicturewidget.h"

using namespace SalesWidgets;

QPictureWidget::QPictureWidget(const QProductPicture &info,
                               const QVector<QProductPicture> &pictures,
                               QWidget *parent)
    : QWidget(parent),
      pictureList(pictures),
      pictureInfo(info)
{
    this->setCursor(Qt::PointingHandCursor);
    setAttribute(Qt::WA_DeleteOnClose);
    this->setFixedSize(128,128);
    newPicture = pictureInfo;

    labelForIcon = new QLabel(this);
    labelForIcon->setAlignment(Qt::AlignCenter);
    labelForIcon->setFixedSize(128,128);

    if (pictureInfo.data.isEmpty()) {
        currentPicture.load(":/images/icons/other/emptyImage.png");
    }
    else {
        currentPicture.loadFromData(pictureInfo.data);
    }
    currentPicture = currentPicture.scaled(this->width(),this->height(),Qt::KeepAspectRatio);\
    labelForIcon->setPixmap(currentPicture);


}

void QPictureWidget::setPictureList(const QVector<QProductPicture> &list)
{
    pictureList = list;
}

QProductPicture QPictureWidget::getPictureInfo()
{
    return pictureInfo;
}

QProductPicture QPictureWidget::getInfoAboutNewPicture()
{
    return newPicture;
}

void QPictureWidget::mouseReleaseEvent(QMouseEvent *)
{
    bool ok;
    QProductPicture info = QPictureDialog::getPicture(&pictureList, &ok, this);

    if (ok) {
        newPicture = info;
        currentPicture.loadFromData(info.data);
        currentPicture = currentPicture.scaled(this->width(),this->height(),Qt::KeepAspectRatio);
        labelForIcon->setPixmap(currentPicture);
    }
}
