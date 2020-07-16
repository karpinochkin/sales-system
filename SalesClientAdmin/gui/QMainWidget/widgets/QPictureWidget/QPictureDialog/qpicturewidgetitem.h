#ifndef QPICTUREWIDGETITEM_H
#define QPICTUREWIDGETITEM_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include "../commonFiles/SalesSystem/QProductPicture/qproductpicture.h"
#include <QMouseEvent>

namespace SalesWidgets {

class QPictureWidgetItem : public QWidget
{
    Q_OBJECT
public:
    explicit QPictureWidgetItem(const QProductPicture &info,QWidget *parent = nullptr);

    QProductPicture getPictureInfo();
    bool isItemSelected();
protected:
    virtual void mouseReleaseEvent(QMouseEvent*);
    virtual void mousePressEvent(QMouseEvent*);
signals:
    void signalUpdateBackgroundColor(int);

public slots:
    void slotUpdateBackgroundColor(int);

private:
    QLabel* labelForIcon;

    void createForm();

    bool itemSelected = false;
    QProductPicture infoAboutPicture;
};

}

#endif // QPICTUREWIDGETITEM_H
