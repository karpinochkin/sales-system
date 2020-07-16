#ifndef QPRICTUREDIALOG_H
#define QPRICTUREDIALOG_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QListWidget>
#include <QLabel>
#include <QPixmap>
#include <QDialog>
#include <QBuffer>
#include <QMessageBox>
#include "../commonFiles/SalesSystem/QProductPicture/qproductpicture.h"
#include "qpicturewidgetitem.h"

namespace SalesWidgets {

class QPictureDialog : public QDialog
{
    Q_OBJECT
public:
    static QProductPicture getPicture(const QVector<QProductPicture>*,
                                      bool *ok = nullptr,
                                      QWidget *parent = nullptr);

    QProductPicture getSelectedPicture();
    QVector<QProductPicture> getSelectedPictures();

private:
    QPictureDialog(const QVector<QProductPicture>*, QWidget *parent = nullptr);

    const QVector<QProductPicture>* currentPictureList;
    QVector<QProductPicture> selectedPictures;
    QProductPicture selectedPicture;


    void createForm();
    void fillingForm();

    QListWidget * listWidget;
    QListWidgetItem* listWidgetItem;
    QPictureWidgetItem *pictureWidgetItem;


    QHBoxLayout *layoutButtons;
    QPushButton *buttonOk;
    QPushButton *buttonCancel;

signals:
    void signalUpdateItemsBackgroudColor(int);

public slots:
private slots:
    void slotPushOk();
    void slotPushCancel();
};

}
#endif // QPRICTUREDIALOG_H
