#include "qpicturedialog.h"

using namespace SalesWidgets;

QPictureDialog::QPictureDialog(const QVector<QProductPicture> *inputList,
                               QWidget *parent)
    : QDialog(parent)
{
    setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint );
    this->setMinimumSize(800,600);
    currentPictureList = inputList;
    createForm();
    fillingForm();
}

QProductPicture QPictureDialog::getPicture(const QVector<QProductPicture>* inputList,
                                           bool *ok,
                                           QWidget *parent)
{
    QProductPicture Output;

    QPictureDialog *dlg = new QPictureDialog(inputList, parent);

    int ret = dlg->exec();
    if (ret == QDialog::Accepted)
    {
        Output = dlg->getSelectedPicture();

        if (ok!=nullptr)
        {
            *ok = true;
        }
    }

    if (ret==QDialog::Rejected)
    {
        if (ok!=nullptr)
        {
            *ok = false;
        }
    }

    dlg->deleteLater();
    return Output;
}

QProductPicture QPictureDialog::getSelectedPicture()
{
    return selectedPicture;
}

QVector<QProductPicture> QPictureDialog::getSelectedPictures()
{
    return selectedPictures;
}

void QPictureDialog::createForm()
{
    QVBoxLayout * mainLayout = new QVBoxLayout(this);
    listWidget = new QListWidget(this);
    listWidget->setFlow(QListView::LeftToRight);
    listWidget->setResizeMode(QListView::Adjust);
    listWidget->setGridSize(QSize(160, 160));
    listWidget->setSpacing(5);
    listWidget->setViewMode(QListView::IconMode);
    mainLayout->addWidget(listWidget,1);
    listWidget -> setMovement(QListView::Static);
    listWidget->setSelectionMode(QListWidget::SingleSelection);

    layoutButtons = new QHBoxLayout();
    mainLayout->addLayout(layoutButtons);
    layoutButtons->addStretch(1);
    buttonOk = new QPushButton(tr("Ok"),this);
    connect(buttonOk,SIGNAL(pressed()),this,SLOT(slotPushOk()));
    buttonOk->setMaximumWidth(80);
    layoutButtons->addWidget(buttonOk);
    layoutButtons->addSpacing(10);
    buttonCancel = new QPushButton(tr("Cancel"),this);
    connect(buttonCancel,SIGNAL(pressed()),this,SLOT(slotPushCancel()));
    buttonCancel->setMaximumWidth(80);
    layoutButtons->addWidget(buttonCancel);
}

void QPictureDialog::fillingForm()
{
    for (int i =0;i< currentPictureList->count();i++)
    {
        listWidgetItem = new QListWidgetItem(listWidget);
        listWidget->addItem (listWidgetItem);

        pictureWidgetItem = new QPictureWidgetItem(currentPictureList->at(i), listWidget);
        connect(pictureWidgetItem,SIGNAL(signalUpdateBackgroundColor(int)),this,SIGNAL(signalUpdateItemsBackgroudColor(int)) );
        connect(this,SIGNAL(signalUpdateItemsBackgroudColor(int)),pictureWidgetItem, SLOT(slotUpdateBackgroundColor(int)));
        listWidgetItem->setSizeHint (pictureWidgetItem->sizeHint ());
        listWidget->setItemWidget(listWidgetItem, pictureWidgetItem);
    }
}

void QPictureDialog::slotPushOk()
{
    bool result = false;

    for (int i=0;i< listWidget->count();i++)
    {
        pictureWidgetItem = dynamic_cast<QPictureWidgetItem*>(listWidget->itemWidget(listWidget->item(i)));
        if (pictureWidgetItem->isItemSelected())
        {
             selectedPicture = pictureWidgetItem->getPictureInfo();
             result = true;
             break;
        }
    }

    if (result)
    {
        emit accept();
    }
    else
    {
        QMessageBox::information(this,
                                 tr("Ошибка"),
                                 tr("Проверьте выделили ли вы картинку"));
    }
}

void QPictureDialog::slotPushCancel()
{
    emit reject();
}
