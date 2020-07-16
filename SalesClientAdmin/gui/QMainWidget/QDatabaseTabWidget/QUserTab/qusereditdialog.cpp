#include "qusereditdialog.h"

using namespace Gui::DatabaseTabs;

QUser QUserEditDialog::show(QDatabaseConrol *control, bool *result, QWidget *parent)
{
    QUser output;
    QUserEditDialog dlg(control, parent);
    int answer = dlg.exec();
    if ( answer == QDialog::Accepted) {
        output.id = dlg.user.id;
        output.name = dlg.user.name;
        output.login = dlg.user.login;
        output.surname = dlg.user.surname;
        output.password = dlg.user.password;
        output.patronymic = dlg.user.patronymic;

        *result = true;
    }
    else {
        *result = false;
    }
    return output;
}

QUser QUserEditDialog::show(const QUser &user, QDatabaseConrol *control, bool *result, QWidget *parent)
{
    QUser output;
    QUserEditDialog dlg(user, control, parent);
    int answer = dlg.exec();
    if ( answer == QDialog::Accepted) {
        output.id = dlg.user.id;
        output.name = dlg.user.name;
        output.login = dlg.user.login;
        output.surname = dlg.user.surname;
        output.password = dlg.user.password;
        output.patronymic = dlg.user.patronymic;

        *result = true;
    }
    else {
        *result = false;
    }
    return output;
}

QUserEditDialog::QUserEditDialog(QDatabaseConrol *control,
                                 QWidget *parent)
    : AbstractTab::QAbstractEditDialog(control, parent)
{
    user.id = -1;
    this->setWindowTitle(tr("Добавление пользователя"));
    this->setGui();
}

QUserEditDialog::QUserEditDialog(const QUser &user,
                                 QDatabaseConrol *control,
                                 QWidget *parent)
    : AbstractTab::QAbstractEditDialog(control, parent),
      user(user)
{
    this->setWindowTitle(tr("Изменение информации о пользователе"));
    this->setGui();
    this->fillForm();
}

void QUserEditDialog::setGui()
{
    nameWidget->setTitle(tr("Логин"));

    firstNameWidget = new QEdit(this);
    firstNameWidget->setTitle(tr("Имя"));
    AbstractTab::QAbstractEditDialog::addWidget(firstNameWidget);

    surnameWidget = new QEdit(this);
    surnameWidget->setTitle("Фамилия");
    AbstractTab::QAbstractEditDialog::addWidget(surnameWidget);

    patronymicWidget = new QEdit(this);
    patronymicWidget->setTitle(tr("Отчество"));
    AbstractTab::QAbstractEditDialog::addWidget(patronymicWidget);

    passwordWidget = new QEdit(this);
    passwordWidget->setTitle("Пароль");
    AbstractTab::QAbstractEditDialog::addWidget(passwordWidget);

}

void QUserEditDialog::fillForm()
{
    nameWidget->setEditText(user.login);
    firstNameWidget->setEditText(user.name);
    patronymicWidget->setEditText(user.patronymic);
    surnameWidget->setEditText(user.surname);
    passwordWidget->setEditText(user.password);
    nameWidget->setEnabled(false);
    passwordWidget->setEnabled(false);
}

void QUserEditDialog::acceptDialog()
{
    if (nameWidget->getEditText().isEmpty()) {
        QMessageBox::critical(this, tr("Ошибка"),
                              tr("Вы не ввели логин"));
    }
    else {
        this->accept();
    }
}

void QUserEditDialog::updateInformation()
{
    user.name = firstNameWidget->getEditText();
    user.surname = surnameWidget->getEditText();
    user.patronymic = patronymicWidget->getEditText();
    user.login = nameWidget->getEditText();
    user.password = passwordWidget->getEditText();
}

void QUserEditDialog::slotSaveChanges()
{
    this->updateInformation();
    this->acceptDialog();
}
