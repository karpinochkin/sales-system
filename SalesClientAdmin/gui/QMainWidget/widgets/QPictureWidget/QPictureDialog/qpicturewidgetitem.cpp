#include "qpicturewidgetitem.h"

using namespace SalesWidgets;

QPictureWidgetItem::QPictureWidgetItem(const QProductPicture &info, QWidget *parent)
    : QWidget (parent),
      infoAboutPicture(info)
{
    setCursor(Qt::ArrowCursor);
    createForm();
}

void QPictureWidgetItem::createForm()
{
    QVBoxLayout * layForPicture = new QVBoxLayout(this);
    labelForIcon = new QLabel(this);
    labelForIcon->setAlignment(Qt::AlignCenter);
    layForPicture->addWidget(labelForIcon);
    labelForIcon->setFixedSize(150,150);
    QPixmap  picture;
    picture.loadFromData(infoAboutPicture.data);
    picture = picture.scaled(128,128,Qt::KeepAspectRatio);
    labelForIcon->setPixmap(picture);
}

QProductPicture QPictureWidgetItem::getPictureInfo()
{
    return infoAboutPicture;
}

bool QPictureWidgetItem::isItemSelected()
{
    return itemSelected;
}

void QPictureWidgetItem::mousePressEvent(QMouseEvent *)
{
    this->setStyleSheet("background-color: rgba(51, 255, 255, 200); ");
}

void QPictureWidgetItem::mouseReleaseEvent(QMouseEvent *)
{
    emit signalUpdateBackgroundColor(infoAboutPicture.id);
}

void QPictureWidgetItem::slotUpdateBackgroundColor(int id)
{
    if (id == infoAboutPicture.id)
    {
        this->setStyleSheet("background-color: rgba(51, 255, 255, 100); ");
        itemSelected = true;
    }
    else
    {
        this->setStyleSheet("background-color: transparent; ");
        itemSelected = false;
    }

}

