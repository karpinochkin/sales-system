#include "qpriceseditdialog.h"

using namespace Gui::DatabaseTabs;

QPrice QPricesEditDialog::show(QDatabaseConrol *control,
                               bool *result,
                               QWidget *parent)
{
    QPrice output;
    QPricesEditDialog dlg(control, parent);
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

QPrice QPricesEditDialog::show(const QPrice &price, QDatabaseConrol *control, bool *result, QWidget *parent)
{
    QPrice output;
    QPricesEditDialog dlg(price, control, parent);
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

QPricesEditDialog::QPricesEditDialog(QDatabaseConrol *control, QWidget *parent)
    : AbstractTab::QAbstractEditDialog(control, parent)
{
    price.clear();
    this->setWindowTitle(tr("Добавление цены"));
    this->setGui();
}

QPricesEditDialog::QPricesEditDialog(const QPrice &price,
                                     QDatabaseConrol *control,
                                     QWidget *parent)
    : AbstractTab::QAbstractEditDialog(control, parent),
    price(price)
{
    this->setWindowTitle(tr("Изменение цены"));
    this->setGui();
    this->fillForm();
}

void QPricesEditDialog::setGui()
{
    nameWidget->hide();

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

    productWidget = new QSingleChoiceBox(this);
    productWidget->setTitle(tr("Товар"));
    productWidget->setHeight(300, 500);
    productWidget->setItems(this->getProductsForWidget());
    AbstractTab::QAbstractEditDialog::addWidget(productWidget);

    pointSaleWidget = new QMultipleChoiceBox(this);
    pointSaleWidget->setTitle(tr("Точки продаж"));
    pointSaleWidget->setHeight(300, 500);
    pointSaleWidget->setItems(this->getPointSalesForWidget());
    AbstractTab::QAbstractEditDialog::addWidget(pointSaleWidget);
}

void QPricesEditDialog::fillForm()
{
    descriptionWidget->setEditText(price.description);
    valueWidget->setNumber(price.value);
    dateTimeWidget->setDateTime(price.startDate);
}

void QPricesEditDialog::acceptDialog()
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
    else if (productWidget->getSelectedItem().id == -1) {
        QMessageBox::critical(this, tr("Ошибка"), tr("Вы не выбрали товар"));
    }
    else {
        this->accept();
    }
}

void QPricesEditDialog::updateInformation()
{
    price.value = valueWidget->getNumber();
    price.idVolume = volumeWidget->getSelectedItem().id;
    price.idProduct = productWidget->getSelectedItem().id;
    price.startDate.setDate(dateTimeWidget->getDateTime().date());
    price.startDate.setTime(dateTimeWidget->getDateTime().time());
    price.description = descriptionWidget->getEditText();
    price.idProductCategory = categoryWidget->getSelectedItem().id;

    price.idPointSales.clear();
    for (int i = 0; i < pointSaleWidget->getSelectedItems().size(); i++) {
        price.idPointSales.push_back(pointSaleWidget->getSelectedItems().at(i).id);
    }
}

QVector<SingleChoiceBox::ItemInformation> QPricesEditDialog::getVolumesForWidget()
{
    QVector<SingleChoiceBox::ItemInformation> output;
    QVector<QVolumeProduct> volumes = db->volume->getVolumes();

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

QVector<SingleChoiceBox::ItemInformation> QPricesEditDialog::getCategoriesForWidget()
{
    QVector<SingleChoiceBox::ItemInformation> output;
    QVector<QSalesCategory> categories = db->category->getCategories();

    for (int i = 0; i < categories.size(); i++) {
        SingleChoiceBox::ItemInformation info;
        info.id = categories.at(i).id;
        info.name = categories.at(i).name;

        if (price.idProductCategory == categories.at(i).id) {
            info.status = true;
        }
        else {
            info.status = false;
        }
        output.push_back(info);
    }
    return output;
}

QVector<SingleChoiceBox::ItemInformation> QPricesEditDialog::getProductsForWidget()
{
    QVector<SingleChoiceBox::ItemInformation> output;
    QVector<QProduct> products = db->product->getProducts();

    for (int i = 0; i < products.size(); i++) {
        SingleChoiceBox::ItemInformation info;
        info.id = products.at(i).id;
        info.name = products.at(i).name;

        if (price.idProduct == products.at(i).id) {
            info.status = true;
        }
        else {
            info.status = false;
        }
        output.push_back(info);
    }
    return output;
}

QVector<MultipleChoiceBox::ItemInformation> QPricesEditDialog::getPointSalesForWidget()
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

void QPricesEditDialog::slotSaveChanges()
{
    this->updateInformation();
    this->acceptDialog();
}
