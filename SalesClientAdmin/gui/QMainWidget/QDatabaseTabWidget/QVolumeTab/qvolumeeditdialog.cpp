#include "qvolumeeditdialog.h"

using namespace Gui::DatabaseTabs;

QVolumeProduct QVolumeEditDialog::show(QDatabaseConrol *control,
                                       bool *result,
                                       QWidget *parent)
{
    QVolumeProduct output;
    QVolumeEditDialog dlg(control, parent);
    int answer = dlg.exec();
    if (answer == QDialog::Accepted) {
        output.id = dlg.volume.id;
        output.name = dlg.volume.name;
        output.description = dlg.volume.description;
        output.units = dlg.volume.units;
        output.volume = dlg.volume.volume;
        output.idProducts = dlg.volume.idProducts;

        *result = true;
    }
    else {
        *result = false;
    }
    return output;
}

QVolumeProduct QVolumeEditDialog::show(const QVolumeProduct &volume,
                                       QDatabaseConrol *control,
                                       bool *result,
                                       QWidget *parent)
{
    QVolumeProduct output;
    QVolumeEditDialog dlg(volume, control, parent);
    int answer = dlg.exec();
    if (answer == QDialog::Accepted) {
        output.id = dlg.volume.id;
        output.name = dlg.volume.name;
        output.description = dlg.volume.description;
        output.units = dlg.volume.units;
        output.volume = dlg.volume.volume;
        output.idProducts = dlg.volume.idProducts;

        *result = true;
    }
    else {
        *result = false;
    }
    return output;
}

QVolumeEditDialog::QVolumeEditDialog(QDatabaseConrol *control,
                                     QWidget *parent)
    : AbstractTab::QAbstractEditDialog(control, parent)
{
    volume.id = -1;
    this->setWindowTitle(tr("Добавление величины"));
    this->setGui();
}

QVolumeEditDialog::QVolumeEditDialog(const QVolumeProduct &volume,
                                     QDatabaseConrol *control,
                                     QWidget *parent)
    : AbstractTab::QAbstractEditDialog(control, parent),
      volume(volume)
{
    this->setWindowTitle(tr("Изменение величины"));
    this->setGui();
    this->fillForm();
}

void QVolumeEditDialog::setGui()
{
    volumeWidget = new QNumberEdit(this);
    volumeWidget->setTitle(tr("Введите значение величины"));
    AbstractTab::QAbstractEditDialog::addWidget(volumeWidget);

    descriptionWidget = new QEdit(this);
    descriptionWidget->setTitle(tr("Описание"));
    AbstractTab::QAbstractEditDialog::addWidget(descriptionWidget);

    unitsWidget = new QEdit(this);
    unitsWidget->setTitle(tr("Величина"));
    AbstractTab::QAbstractEditDialog::addWidget(unitsWidget);

    productsWidget = new QMultipleChoiceBox(this);
    productsWidget->setTitle(tr("Товары"));
    productsWidget->setHeight(300, 500);
    productsWidget->setItems(this->getProductsForWidget());
    AbstractTab::QAbstractEditDialog::addWidget(productsWidget);
}

void QVolumeEditDialog::fillForm()
{
    nameWidget->setEditText(volume.name);
    volumeWidget->setNumber(volume.volume);
    descriptionWidget->setEditText(volume.description);
    unitsWidget->setEditText(volume.units);
}

void QVolumeEditDialog::acceptDialog()
{
    if (nameWidget->getEditText().isEmpty()) {
        QMessageBox::critical(this,
                              tr("Ошибка"), tr("Вы не ввели название"));
    }
    else if (descriptionWidget->getEditText().isEmpty()) {
        QMessageBox::critical(this,
                              tr("Ошибка"), tr("Вы не ввели описание"));
    }
    else if (volumeWidget->getNumber() <= 0) {
        QMessageBox::critical(this,
                              tr("Ошибка"), tr("Проверьте значение"));
    }
    else if (unitsWidget->getEditText().isEmpty()) {
        QMessageBox::critical(this,
                              tr("Ошибка"), tr("Вы не ввели величину"));
    }
    else if (unitsWidget->getEditText().size() > 16) {
        QMessageBox::critical(this,
                              tr("Ошибка"), tr("Величина не должна превышать 16 символов"));
    }
    else {
        this->accept();
    }
}

void QVolumeEditDialog::updateInformation()
{
    volume.name = nameWidget->getEditText();
    volume.volume = volumeWidget->getNumber();
    volume.description = descriptionWidget->getEditText();
    volume.units = unitsWidget->getEditText();

    volume.idProducts.clear();
    QVector<MultipleChoiceBox::ItemInformation> selectedProducts = productsWidget->getSelectedItems();
    for (int i = 0; i < selectedProducts.size(); i++) {
        volume.idProducts.push_back(selectedProducts.at(i).id);
    }
}

QVector<MultipleChoiceBox::ItemInformation> QVolumeEditDialog::getProductsForWidget()
{
    QVector<MultipleChoiceBox::ItemInformation> output;
    QVector<QProduct> products = db->product->getProducts();

    for (int i = 0; i < products.size(); i++) {
        MultipleChoiceBox::ItemInformation info;
        for (int j = 0; j < volume.idProducts.size(); j++) {
            if (volume.idProducts.at(j) == products.at(i).id) {
                info.status = true;
                break;
            }
            else {
                info.status = false;
            }
        }
        info.id = products.at(i).id;
        info.name = products.at(i).name;
        info.isWasChanged = false;
        output.push_back(info);
    }
    return output;
}

void QVolumeEditDialog::slotSaveChanges()
{
    this->updateInformation();
    this->acceptDialog();
}
