#include "qpriceseditforproductdialog.h"

using namespace Gui::DatabaseTabs::PricesTab;
using namespace Gui::DatabaseTabs;

QPrice QPricesEditForProductDialog::show(QDatabaseConrol *control,
                                         const PricesTab::Product &product,
                                         bool *result,
                                         QWidget *parent)
{
    QPrice output;
    QPricesEditForProductDialog dlg(control, product, parent);
    int answer = dlg.exec();
    if ( answer == QDialog::Accepted) {
        output.id = dlg.price.id;
        output.value = dlg.price.value;
        output.idVolume = dlg.price.idVolume;
        output.idProduct = dlg.price.idProduct;
        output.startDate.setDate(dlg.price.startDate.date());
        output.startDate.setTime(dlg.price.startDate.time());
        output.description = dlg.price.description;
        output.idProductCategory = dlg.price.idProductCategory;

        output.idPointSales = dlg.price.idPointSales;
        dlg.price.clear();

        *result = true;
    }
    else {
        *result = false;
    }
    return output;
}

QPrice QPricesEditForProductDialog::show(const QPrice &price,
                                         QDatabaseConrol *control,
                                         const PricesTab::Product &product,
                                         bool *result,
                                         QWidget *parent)
{
    QPrice output;
    QPricesEditForProductDialog dlg(price, control, product, parent);
    int answer = dlg.exec();
    if ( answer == QDialog::Accepted) {
        output.id = dlg.price.id;
        output.value = dlg.price.value;
        output.idVolume = dlg.price.idVolume;
        output.idProduct = dlg.price.idProduct;
        output.startDate.setDate(dlg.price.startDate.date());
        output.startDate.setTime(dlg.price.startDate.time());
        output.description = dlg.price.description;
        output.idProductCategory = dlg.price.idProductCategory;

        output.idPointSales = dlg.price.idPointSales;
        dlg.price.clear();

        *result = true;
    }
    else {
        *result = false;
    }
    return output;
}

QPricesEditForProductDialog::QPricesEditForProductDialog(QDatabaseConrol *control,
                                                         const PricesTab::Product &product, QWidget *parent)
    : AbstractTab::QAbstractEditDialog(control, parent),
      product(product)
{
    price.clear();
    this->setWindowTitle(tr("Добавление цены"));
    this->setGui();
}

QPricesEditForProductDialog::QPricesEditForProductDialog(const QPrice &price,
                                                         QDatabaseConrol *control,
                                                         const PricesTab::Product &product,
                                                         QWidget *parent)
    : AbstractTab::QAbstractEditDialog(control, parent),
      price(price),
      product(product)
{
    this->setWindowTitle(tr("Изменение цены"));
    this->setGui();
    this->fillForm();
}

void QPricesEditForProductDialog::setGui()
{
    nameWidget->hide();

    productWidget = new QEdit(this);
    productWidget->setTitle(tr("Товар"));
    productWidget->setEditText(product.name);
    AbstractTab::QAbstractEditDialog::addWidget(productWidget);
    productWidget->setEnabled(false);

    descriptionWidget = new QEdit(this);
    descriptionWidget->setTitle(tr("Описание"));
    AbstractTab::QAbstractEditDialog::addWidget(descriptionWidget);

    valueWidget = new QDoubleNumberEdit(this);
    valueWidget->setTitle(tr("Значение величины"));
    AbstractTab::QAbstractEditDialog::addWidget(valueWidget);

    dateTimeWidget = new QSalesDateTimeEdit(this);
    dateTimeWidget->setTitle(tr("Дата и время"));
    AbstractTab::QAbstractEditDialog::addWidget(dateTimeWidget);

    volumeWidget = new QSingleChoiceBox(this);
    volumeWidget->setTitle(tr("Величина"));
    volumeWidget->setHeight(300, 500);
    volumeWidget->setItems(this->getVolumesForWidget());
    AbstractTab::QAbstractEditDialog::addWidget(volumeWidget);

    categoryWidget = new QSingleChoiceBox(this);
    categoryWidget->setTitle(tr("Категория"));
    categoryWidget->setHeight(300, 500);
    categoryWidget->setItems(this->getCategoriesForWidget());
    AbstractTab::QAbstractEditDialog::addWidget(categoryWidget);

    pointSalesWidget = new QMultipleChoiceBox(this);
    pointSalesWidget->setTitle(tr("Точки продаж"));
    pointSalesWidget->setHeight(300, 500);
    pointSalesWidget->setItems(this->getPointSalesForWidget());
    AbstractTab::QAbstractEditDialog::addWidget(pointSalesWidget);
}

void QPricesEditForProductDialog::fillForm()
{
    descriptionWidget->setEditText(price.description);
    valueWidget->setNumber(price.value);
    dateTimeWidget->setDateTime(price.startDate);
}

void QPricesEditForProductDialog::acceptDialog()
{
    if (descriptionWidget->getEditText().isEmpty()) {
        QMessageBox::critical(this, tr("Ошибка"), tr("Вы не ввели описание"));
    }
    else if (valueWidget->getNumber() < 0) {
        QMessageBox::critical(this, tr("Ошибка"), tr("Цена не может быть отрицательной"));
    }
    else if (volumeWidget->getSelectedItem().id == -1) {
        QMessageBox::critical(this, tr("Ошибка"), tr("Вы не выбрали величину"));
    }
    else if (categoryWidget->getSelectedItem().id == -1) {
        QMessageBox::critical(this, tr("Ошибка"), tr("Вы не выбрали категорию"));
    }
    else {
        this->accept();
    }
}

void QPricesEditForProductDialog::updateInformation()
{
    price.value = valueWidget->getNumber();
    price.idVolume = volumeWidget->getSelectedItem().id;
    price.idProduct = product.id;
    price.startDate.setDate(dateTimeWidget->getDateTime().date());
    price.startDate.setTime(dateTimeWidget->getDateTime().time());
    price.description = descriptionWidget->getEditText();
    price.idProductCategory = categoryWidget->getSelectedItem().id;
    price.idPointSales.clear();
    for (int i = 0; i < pointSalesWidget->getSelectedItems().size(); i++) {
        price.idPointSales.push_back(pointSalesWidget->getSelectedItems().at(i).id);
    }


}

QVector<SingleChoiceBox::ItemInformation> QPricesEditForProductDialog::getVolumesForWidget()
{
    QVector<SingleChoiceBox::ItemInformation> output;
    QVector<QVolumeProduct> volumes = db->volume->getVolumes(product.id);

    for (int i = 0; i < volumes.size(); i++) {
        SingleChoiceBox::ItemInformation info;
        info.id = volumes.at(i).id;
        info.name = volumes.at(i).description;

        if (price.idVolume == volumes.at(i).id) {
            info.status = true;
        }
        else {
            info.status = false;
        }
        output.push_back(info);
    }
    return output;
}

QVector<SingleChoiceBox::ItemInformation> QPricesEditForProductDialog::getCategoriesForWidget()
{
    QVector<SingleChoiceBox::ItemInformation> output;
    QVector<QSalesCategory> categories = db->category->getCategories();
    QVector<int> idSelectedCategories;

    if (product.id > 0) {
        idSelectedCategories = db->product->getIdCategories(product.id);
    }

    for (int i = 0; i < categories.size(); i++) {
        for (int j = 0; j < idSelectedCategories.size(); j++) {
            if (categories.at(i).id == idSelectedCategories.at(j)) {
                SingleChoiceBox::ItemInformation info;
                info.id = categories.at(i).id;
                info.name = categories.at(i).name;

                if (categories.at(i).id == price.idProductCategory) {
                    info.status = true;
                }
                else {
                    info.status = false;
                }
                output.push_back(info);
            }
        }
    }

    return output;
}

QVector<MultipleChoiceBox::ItemInformation> QPricesEditForProductDialog::getPointSalesForWidget()
{
    QVector<MultipleChoiceBox::ItemInformation> output;
    QVector<QPointSale> pointSales = db->pointSale->getPointSales();
    QVector<int> idSelectedPointSales;

    if (price.id > 0) {
        idSelectedPointSales = db->price->getIdPointSales(price.id);
    }

    for (int i = 0; i < pointSales.size(); i++) {
        MultipleChoiceBox::ItemInformation info;
        for (int j = 0; j < idSelectedPointSales.size(); j++) {
            if (idSelectedPointSales.at(j) == pointSales.at(i).id) {
                info.status = true;
                break;
            }
            else {
                info.status = false;
            }
        }
        info.id = pointSales.at(i).id;
        info.name = pointSales.at(i).name;
        info.isWasChanged = false;
        output.push_back(info);
    }
    return output;
}

void QPricesEditForProductDialog::slotSaveChanges()
{
    this->updateInformation();
    this->acceptDialog();
}
