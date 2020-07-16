#include "qpointsaleeditdialog.h"

using namespace Gui::DatabaseTabs;

QPointSale QPointSaleEditDialog::show(QDatabaseConrol *control,
                                      bool *result,
                                      QWidget *parent)
{
    QPointSale output;
    QPointSaleEditDialog dlg(control, parent);
    int answer = dlg.exec();
    if ( answer == QDialog::Accepted) {
        output.id = dlg.pointSale.id;
        output.name = dlg.pointSale.name;
        output.idProducts = dlg.pointSale.idProducts;
        output.idCategories = dlg.pointSale.idCategories;
        qDebug() << dlg.pointSale.toString();
        qDebug() << output.toString();
        dlg.pointSale.clear();

        *result = true;
    }
    else {
        *result = false;
    }
    return output;
}

QPointSale QPointSaleEditDialog::show(const QPointSale &pointSale,
                                      QDatabaseConrol *control,
                                      bool *result,
                                      QWidget *parent)
{
    QPointSale output;
    QPointSaleEditDialog dlg(pointSale, control, parent);
    int answer = dlg.exec();
    if ( answer == QDialog::Accepted) {
        output.id = dlg.pointSale.id;
        output.name = dlg.pointSale.name;
        output.idProducts = dlg.pointSale.idProducts;
        output.idCategories = dlg.pointSale.idCategories;
        qDebug() << dlg.pointSale.toString();
        qDebug() << output.toString();
        dlg.pointSale.clear();

        *result = true;
    }
    else {
        *result = false;
    }
    return output;
}

QPointSaleEditDialog::QPointSaleEditDialog(QDatabaseConrol *control,
                                           QWidget *parent)
    : AbstractTab::QAbstractEditDialog(control, parent)
{
    pointSale.clear();
    this->setWindowTitle(tr("Добавление точки продаж"));
    this->setGui();
}

QPointSaleEditDialog::QPointSaleEditDialog(const QPointSale &pointSale,
                                           QDatabaseConrol *control,
                                           QWidget *parent)
    : AbstractTab::QAbstractEditDialog(control, parent),
    pointSale(pointSale)
{
    this->setWindowTitle(tr("Изменение точки продаж"));
    this->setGui();
    this->fillForm();
}

void QPointSaleEditDialog::setGui()
{
    categoryWidget = new QMultipleChoiceBox(this);
    categoryWidget->setTitle(tr("Категории: "));
    categoryWidget->setHeight(300, 500);
    categoryWidget->setItems(this->getCategoriesForWidget());
    AbstractTab::QAbstractEditDialog::addWidget(categoryWidget);

    productWidget = new QMultipleChoiceBox(this);
    productWidget->setTitle(tr("Товары: "));
    productWidget->setHeight(300, 500);
    productWidget->setItems(this->getProductsForWidget());
    AbstractTab::QAbstractEditDialog::addWidget(productWidget);
}

void QPointSaleEditDialog::fillForm()
{
    nameWidget->setEditText(pointSale.name);
}

void QPointSaleEditDialog::acceptDialog()
{
    if (nameWidget->getEditText().isEmpty()) {
        QMessageBox::critical(this, tr("Ошибка"), tr("Вы не ввели название"));
    }
    else {
        this->accept();
    }
}

void QPointSaleEditDialog::updateInformation()
{
    pointSale.name = nameWidget->getEditText();

    pointSale.idCategories.clear();
    QVector<MultipleChoiceBox::ItemInformation> selectedCategories = categoryWidget->getSelectedItems();
    for (int i = 0; i < selectedCategories.size(); i++) {
            pointSale.idCategories.push_back(selectedCategories.at(i).id);
    }

    pointSale.idProducts.clear();
    QVector<MultipleChoiceBox::ItemInformation> selectedProducts = productWidget->getSelectedItems();
    for (int i = 0; i < selectedProducts.size(); i++) {
        pointSale.idProducts.push_back(selectedProducts.at(i).id);
    }
}

QVector<MultipleChoiceBox::ItemInformation> QPointSaleEditDialog::getCategoriesForWidget()
{
    QVector<MultipleChoiceBox::ItemInformation> output;
    QVector<QSalesCategory> categories = db->category->getCategories();
    QVector<QSalesCategory> selectedCategories;

    if (pointSale.id > 0) {
        selectedCategories = db->category->getCategories(pointSale.id);
    }

    for (int i = 0; i < categories.size(); i++) {
        MultipleChoiceBox::ItemInformation info;

        for (int j = 0; j < selectedCategories.size(); j++) {
            if (selectedCategories.at(j).id == categories.at(i).id) {
                info.status = true;
                break;
            }
            else {
                info.status = false;
            }
        }

        info.id = categories.at(i).id;
        info.name = categories.at(i).name;
        info.isWasChanged = false;
        output.push_back(info);
    }
    return output;
}

QVector<MultipleChoiceBox::ItemInformation> QPointSaleEditDialog::getProductsForWidget()
{
    QVector<MultipleChoiceBox::ItemInformation> output;
    QVector<QProduct> products = db->product->getProducts();
    QVector<int> idSelectedProducts;

    if (pointSale.id > 0) {
        idSelectedProducts = db->pointSale->getProductsId(pointSale.id);
    }

    for (int i = 0; i < products.size(); i++) {
        MultipleChoiceBox::ItemInformation info;
        for (int j = 0; j < idSelectedProducts.size(); j++) {
            if (idSelectedProducts.at(j) == products.at(i).id) {
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

void QPointSaleEditDialog::slotSaveChanges()
{
    this->updateInformation();
    this->acceptDialog();
}

