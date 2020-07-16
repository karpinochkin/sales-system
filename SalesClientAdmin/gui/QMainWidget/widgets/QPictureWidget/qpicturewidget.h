#ifndef QPICTUREWIDGET_H
#define QPICTUREWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QImage>
#include <QMouseEvent>
#include <QDebug>
#include "QPictureDialog/qpicturedialog.h"
#include "../commonFiles/SalesSystem/QProductPicture/qproductpicture.h"

namespace SalesWidgets {

class QPictureWidget : public QWidget
{
    Q_OBJECT
public:
    explicit QPictureWidget(const QProductPicture &picture,
                            const QVector<QProductPicture> &pictures,
                            QWidget *parent = nullptr);

    void setPictureList(const QVector<QProductPicture>&);
    QProductPicture getPictureInfo();
    QProductPicture getInfoAboutNewPicture();
protected:
    virtual void mouseReleaseEvent(QMouseEvent*);

private:
    QLabel *labelForIcon;
    QPixmap currentPicture;

    QVector<QProductPicture> pictureList;
    QProductPicture newPicture;
    QProductPicture pictureInfo;
};

}
#endif // QPICTUREWIDGET_H
