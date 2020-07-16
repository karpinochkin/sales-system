#include "qaccountdialog.h"

using namespace Gui::Loader;

QAccountDialog::QAccountDialog(QWidget *parent) : QDialog(parent)
{
    createForm();
    connects();
    addToWidget();
}

void QAccountDialog::createForm()
{
    mainLayout = new QGridLayout(this);
    labelLogin = new QLabel(tr("Логин"),this);
    editLogin = new QLineEdit(this);
    labelPassword = new QLabel(tr("Пароль"),this);
    editPassword = new QLineEdit(this);
    editPassword->setEchoMode(QLineEdit::Password);
    checkSaveLogin = new QCheckBox(tr("Сохранить"),this);
    layoutButtons = new QHBoxLayout;
    buttonOk = new QPushButton(tr("Далее"),this);
    buttonCancel = new QPushButton(tr("Отмена"),this);
    setWindowFlag(Qt::WindowStaysOnTopHint);
}

void QAccountDialog::connects()
{
    connect(buttonOk,SIGNAL(pressed()),this,SLOT(accept()));
    connect(buttonCancel,SIGNAL(pressed()),this,SLOT(reject()));
}

void QAccountDialog::addToWidget()
{
    mainLayout->addWidget(labelLogin,0,0,1,1);
    mainLayout->addWidget(editLogin,0,1,1,1);
    mainLayout->addWidget(labelPassword,1,0,1,1);
    mainLayout->addWidget(editPassword,1,1,1,1);
    mainLayout->addWidget(checkSaveLogin,2,1,1,1);
    mainLayout->addLayout(layoutButtons,3,0,1,2);
    layoutButtons->addWidget(buttonOk);
    layoutButtons->addWidget(buttonCancel);

}

UserAccount QAccountDialog::getAccount(bool *result, QWidget *parent)
{
    UserAccount Output;
    QAccountDialog *dlg = new QAccountDialog(parent);
    dlg->setModal(true);
    dlg->setWindowTitle(tr("Enter login and password"));
    int ret = dlg->exec();

    if ((ret == QDialog::Accepted)&&
            (!dlg->editLogin->text().isEmpty())&&
            (!dlg->editPassword->text().isEmpty()))
    {
        if (result != nullptr) *result = true;
        Output.login = dlg->editLogin->text();
        Output.password = dlg->editPassword->text();
        Output.save = dlg->checkSaveLogin->isChecked();

    } else *result = false;

    delete dlg;
    return Output;
}

UserAccount QAccountDialog::getAccount(const UserAccount& account, bool *result, QWidget *parent)
{
    UserAccount Output;
    QAccountDialog *dlg = new QAccountDialog(parent);
    dlg->setModal(true);
    dlg->setWindowTitle(tr("Введите логин и пароль"));
    if (!account.login.isEmpty())
    {
        dlg->editLogin->setText(account.login);
        dlg->editPassword->setText(account.password);
        dlg->checkSaveLogin->setChecked(true);
    }

    int ret = dlg->exec();
    if ((ret == QDialog::Accepted)&&
            (!dlg->editLogin->text().isEmpty())&&
            (!dlg->editPassword->text().isEmpty()))
    {
        if (result != nullptr) *result = true;
        Output.login = dlg->editLogin->text();
        Output.password = dlg->editPassword->text();
        Output.save = dlg->checkSaveLogin->isChecked();

    } else *result = false;

    delete dlg;
    return Output;
}
