#include "qhostsdialog.h"

using namespace Gui::Loader;

QHostsDialog::QHostsDialog(QWidget *parent) : QDialog(parent)
{
    setParent(parent);
    setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint);

    createForm();
    connects();
    addToWidget();
}

QHostsDialog::QHostsDialog(HostInfo host,QWidget *parent)
{
    setParent(parent);
    setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint);

    createForm();
    connects();
    addToWidget();

    editAddress->setText(host.address);
    editPort->setText(QString::number(host.port));
}

void QHostsDialog::createForm()
{
    mainlayout = new QGridLayout(this);
    labelAddress = new QLabel(tr("Адрес"),this);
    editAddress = new QLineEdit(this);
    labelPort = new QLabel(tr("Порт"),this);
    editPort = new QLineEdit(this);
    layoutButtons = new QHBoxLayout;
    layoutButtons->setMargin(0);
    buttonOk = new QPushButton(tr("Далее"),this);
    buttonCancel = new QPushButton(tr("Отмена"),this);
    setWindowFlag(Qt::WindowStaysOnTopHint);

}

void QHostsDialog::connects()
{
    connect(buttonOk,SIGNAL(pressed()),this,SLOT(accept()));
    connect(buttonCancel,SIGNAL(pressed()),this,SLOT(reject()));
}

void QHostsDialog::addToWidget()
{

    mainlayout->addWidget(labelAddress,0,0,1,1);
    mainlayout->addWidget(editAddress,0,1,1,1);
    mainlayout->addWidget(labelPort,1,0,1,1);
    mainlayout->addWidget(editPort);
    mainlayout->addLayout(layoutButtons,2,0,1,2);
    layoutButtons->addWidget(buttonOk);
    layoutButtons->addWidget(buttonCancel);
}

HostInfo QHostsDialog::getHost(bool *ok, QWidget *parent)
{
    HostInfo Output;
    QHostsDialog *dlg = new QHostsDialog(parent);
    dlg->setModal(true);
    dlg->setWindowTitle(tr("Введите новый хост"));
    int ret = dlg->exec();
    if (ret == QDialog::Accepted)
    {
        if (ok!=nullptr) *ok=true;
        Output.address = dlg->editAddress->text();
        Output.port = dlg->editPort->text().toInt();
    } else *ok=false;
    delete dlg;
    return Output;
}

HostInfo QHostsDialog::getHost(HostInfo host, bool *ok, QWidget *parent)
{
    HostInfo Output;
    QHostsDialog *dlg = new QHostsDialog(host, parent);
    dlg->setModal(true);
    dlg->setWindowTitle(tr("Введите новый хост"));
    int ret = dlg->exec();
    if (ret == QDialog::Accepted)
    {
        if (ok!=nullptr) *ok=true;
        Output.address = dlg->editAddress->text();
        Output.port = dlg->editPort->text().toInt();
    } else *ok=false;
    delete dlg;
    return Output;
}

HostInfo QHostsDialog::editHost(HostInfo host, bool *ok, QWidget *parent)
{
    HostInfo Output;
    QHostsDialog *dlg = new QHostsDialog(host,parent);
    dlg->setModal(true);
    dlg->setWindowTitle(tr("Изменить хост"));
    int ret = dlg->exec();
    if (ret == QDialog::Accepted)
    {
        if (ok != nullptr) *ok=true;
        Output.address = dlg->editAddress->text();
        Output.port = dlg->editPort->text().toInt();
    } else *ok=false;
    delete dlg;
    return Output;
}
