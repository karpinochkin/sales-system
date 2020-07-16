#include "qproductseditdialog.h"

using namespace Gui::DatabaseTabs;

QProduct QProductsEditDialog::show(QDatabaseConrol *control,
                                   bool *result,
                                   QWidget *parent)
{
    QProduct output;
    QProductsEditDialog dlg(control, parent);
    int answer = dlg.exec();
    if ( answer == QDialog::Accepted) {
        output.id = dlg.product.id;
        output.name = dlg.product.name;
        output.color.setRed(dlg.product.color.red());
        output.color.setGreen(dlg.product.color.green());
        output.color.setBlue(dlg.product.color.blue());
        output.idPicture = dlg.product.idPicture;
        output.description = dlg.product.description;
        output.pictureHash = dlg.product.pictureHash;
        output.idCategories = dlg.product.idCategories;

        *result = true;
    }
    else {
        *result = false;
    }
    return output;
}

QProduct QProductsEditDialog::show(const QProduct &product,
                                   QDatabaseConrol *control,
                                   bool *result,
                                   bool *isShawPriceWindow,
                                   QWidget *parent)
{
    QProduct output;
    QProductsEditDialog dlg(product, control, parent);
    int answer = dlg.exec();
    if ( answer == QDialog::Accepted) {
        output.id = dlg.product.id;
        output.name = dlg.product.name;
        output.color.setRed(dlg.product.color.red());
        output.color.setGreen(dlg.product.color.green());
        output.color.setBlue(dlg.product.color.blue());
        output.idPicture = dlg.product.idPicture;
        output.description = dlg.product.description;
        output.pictureHash = dlg.product.pictureHash;
        output.idCategories = dlg.product.idCategories;

        *isShawPriceWindow = dlg.isShowPriceWindow;
        *result = true;
    }
    else {
        *result = false;
    }
    return output;
}

QProductsEditDialog::QProductsEditDialog(QDatabaseConrol *control,
                                         QWidget *parent)
    : AbstractTab::QAbstractEditDialog(control, parent)
{
    product.clear();
    this->setWindowTitle(tr("Добавление товара"));
    this->setGui();
}

QProductsEditDialog::QProductsEditDialog(const QProduct &product,
                                         QDatabaseConrol *control,
                                         QWidget *parent)
    : AbstractTab::QAbstractEditDialog(control, parent),
      product(product)
{
    this->setWindowTitle(tr("Изменение товара"));
    this->setGui();
    this->fillForm();
}

void QProductsEditDialog::setGui()
{
    descriptionWidget = new QEdit(this);
    descriptionWidget->setTitle(tr("Описание"));
    AbstractTab::QAbstractEditDialog::addWidget(descriptionWidget, 1, 0, 1, 1);

    colorTitle = new QLabel(tr("Цвет фона:"));
    colorWidget = new SalesWidgets::QColorWidget(this);
    AbstractTab::QAbstractEditDialog::addWidget(colorTitle, 2, 0, 1, 1);
    AbstractTab::QAbstractEditDialog::addWidget(colorWidget, 3, 0, 1, 1);

    pictureWidget = new SalesWidgets::QPictureWidget(db->picture->get(product.idPicture),
                                                     db->picture->getPictures(),
                                                     this);
    AbstractTab::QAbstractEditDialog::addWidget(pictureWidget, 0, 1, 3, 1);

    categoryWidget = new QMultipleChoiceBox(this);
    categoryWidget->setTitle(tr("Категории:"));
    categoryWidget->setHeight(300, 500);
    categoryWidget->setItems(this->getCategoriesForWidget());
    AbstractTab::QAbstractEditDialog::addWidget(categoryWidget, 4, 0, 1, 2);

    priceButton = new QPushButton(tr("Изменить цены"), this);
    connect(priceButton, &QPushButton::clicked,
            this, &QProductsEditDialog::slotChangePrice);
    AbstractTab::QAbstractEditDialog::addWidget(priceButton, 5, 0, 1, 2);
    priceButton->hide();
}

void QProductsEditDialog::fillForm()
{
    nameWidget->setEditText(product.name);
    descriptionWidget->setEditText(product.description);
    QColor color(product.color.red(), product.color.green(), product.color.blue());
    colorWidget->setColor(color);
    priceButton->show();
}

void QProductsEditDialog::acceptDialog()
{
    if (nameWidget->getEditText().isEmpty()) {
        QMessageBox::critical(this, tr("Ошибка"), tr("Вы не ввели название"));
    }
    else if (descriptionWidget->getEditText().isEmpty()) {
        QMessageBox::critical(this, tr("Ошибка"), tr("Вы не ввели описание"));
    }
//    else if (product.idPicture <= 0) {
//        QMessageBox::critical(this, tr("Ошибка"), tr("Вы не выбрали изображение"));
//    }
    else {
        this->accept();
    }
}

void QProductsEditDialog::updateInformation()
{
    product.name = nameWidget->getEditText();
    product.description = descriptionWidget->getEditText();
    product.color.setRed(colorWidget->getColor().red());
    product.color.setGreen(colorWidget->getColor().green());
    product.color.setBlue(colorWidget->getColor().blue());
    product.idPicture = pictureWidget->getInfoAboutNewPicture().id;

    product.idCategories.clear();
    QVector<MultipleChoiceBox::ItemInformation> selectedCategories = categoryWidget->getSelectedItems();
    for (int i = 0; i < selectedCategories.size(); i++) {
        product.idCategories.push_back(selectedCategories.at(i).id);
    }
}

QVector<MultipleChoiceBox::ItemInformation> QProductsEditDialog::getCategoriesForWidget()
{
    QVector<MultipleChoiceBox::ItemInformation> output;
    QVector<QSalesCategory> categories = db->category->getCategories();
    QVector<int> idSelectedCategories;

    if (product.id > 0) {
        idSelectedCategories = db->product->getIdCategories(product.id);
    }

    for (int i = 0; i < categories.size(); i++) {
        MultipleChoiceBox::ItemInformation info;

        for (int j = 0; j < idSelectedCategories.size(); j++) {
            if (idSelectedCategories.at(j) == categories.at(i).id) {
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

QVector<SalesComboBox::ItemInformation> QProductsEditDialog::getPricesForWidget()
{
    QVector<SalesComboBox::ItemInformation> output;
    QVector<QPointSale> pointSales = db->pointSale->getPointSales();

    QVector<int> idProductsForPointSale;

    for (int i = 0; i < pointSales.size(); i++) {
        SalesComboBox::ItemInformation info;
        idProductsForPointSale = pointSales.at(i).idProducts;

        for (int j = 0; j < idProductsForPointSale.size(); j++) {
            if (idProductsForPointSale.at(j) == product.id) {
                info.id = pointSales.at(i).id;
                info.name = pointSales.at(i).name;
                output.push_back(info);
            }
        }
    }
    return output;
}

void QProductsEditDialog::slotSaveChanges()
{
    this->updateInformation();
    this->acceptDialog();
}

void QProductsEditDialog::slotChangePrice()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this,
                                  tr("Предупреждение"),
                                  tr("Если вы продолжите, то текущее окно будет закрыто и изменения сохранены."),
                                  QMessageBox::Yes|QMessageBox::No);

    if (reply == QMessageBox::Yes)
    {
        isShowPriceWindow = true;
        this->slotSaveChanges();
    }
}
