#include "qtypeeditdialog.h"

using namespace Gui::DatabaseTabs;

QPaymentType QTypeEditDialog::show(QDatabaseConrol *control, bool *result, QWidget *parent)
{
    QPaymentType output;
    QTypeEditDialog dlg(control, parent);
    int answer = dlg.exec();
    if ( answer == QDialog::Accepted) {
        output.id = dlg.type.id;
        output.name = dlg.type.name;
        output.description = dlg.type.description;

        *result = true;
    }
    else {
        *result = false;
    }
    return output;
}

QPaymentType QTypeEditDialog::show(const QPaymentType &type, QDatabaseConrol *control, bool *result, QWidget *parent)
{
    QPaymentType output;
    QTypeEditDialog dlg(type, control, parent);
    int answer = dlg.exec();
    if (answer == QDialog::Accepted) {
        output.id = dlg.type.id;
        output.name = dlg.type.name;
        output.description = dlg.type.description;

        *result = true;
    }
    else {
        *result = false;
    }
    return output;
}

QTypeEditDialog::QTypeEditDialog(QDatabaseConrol *control, QWidget *parent)
    : AbstractTab::QAbstractEditDialog(control, parent)
{
    type.id = -1;
    this->setWindowTitle(tr("Добавление типа оплаты"));
    this->setGui();
}

QTypeEditDialog::QTypeEditDialog(const QPaymentType &type, QDatabaseConrol *control, QWidget *parent)
    : AbstractTab::QAbstractEditDialog(control, parent),
    type(type)
{
    this->setWindowTitle(tr("Изменение типа оплаты"));
    this->setGui();
    this->fillForm();
}

void QTypeEditDialog::setGui()
{
    descriptionWidget = new QEdit(this);
    descriptionWidget->setTitle(tr("Описание"));
    AbstractTab::QAbstractEditDialog::addWidget(descriptionWidget);
}

void QTypeEditDialog::fillForm()
{
    nameWidget->setEditText(type.name);
    descriptionWidget->setEditText(type.description);
}

void QTypeEditDialog::acceptDialog()
{
    if (nameWidget->getEditText().isEmpty()) {
        QMessageBox::critical(this, tr("Ошибка"), tr("Вы не ввели название"));
    }
    else if (descriptionWidget->getEditText().isEmpty()) {
        QMessageBox::critical(this, tr("Ошибка"), tr("Вы не ввели описание"));
    }
    else {
        this->accept();
    }
}

void QTypeEditDialog::updateInformation()
{
    type.name = nameWidget->getEditText();
    type.description = descriptionWidget->getEditText();
}

void QTypeEditDialog::slotSaveChanges()
{
    this->updateInformation();
    this->acceptDialog();
}
