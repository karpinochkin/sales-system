#include "qcategoryeditdialog.h"

using namespace Gui::DatabaseTabs;

QSalesCategory QCategoryEditDialog::show(QDatabaseConrol *control, bool *result, QWidget *parent)
{
    QSalesCategory output;
    QCategoryEditDialog dlg(control, parent);
    int answer = dlg.exec();
    if ( answer == QDialog::Accepted) {
        output.id = dlg.category.id;
        output.name = dlg.category.name;
        output.description = dlg.category.description;
        output.color.setRed(dlg.category.color.red());
        output.color.setGreen(dlg.category.color.green());
        output.color.setBlue(dlg.category.color.blue());
        output.idPointSale = dlg.category.idPointSale;
        dlg.category.clear();

        *result = true;
    }
    else {
        *result = false;
    }
    return output;
}

QSalesCategory QCategoryEditDialog::show(const QSalesCategory &category, QDatabaseConrol *control, bool *result, QWidget *parent)
{
    QSalesCategory output;
    QCategoryEditDialog dlg(category, control, parent);
    int answer = dlg.exec();
    if ( answer == QDialog::Accepted) {
        output.id = dlg.category.id;
        output.name = dlg.category.name;
        output.description = dlg.category.description;
        output.color.setRed(dlg.category.color.red());
        output.color.setGreen(dlg.category.color.green());
        output.color.setBlue(dlg.category.color.blue());
        output.idPointSale = dlg.category.idPointSale;
        dlg.category.clear();

        *result = true;
    }
    else {
        *result = false;
    }
    return output;
}

QCategoryEditDialog::QCategoryEditDialog(QDatabaseConrol *control, QWidget *parent)
: AbstractTab::QAbstractEditDialog(control, parent)
{
    category.clear();
    this->setWindowTitle(tr("Добавление категории"));
    this->setGui();
}

QCategoryEditDialog::QCategoryEditDialog(const QSalesCategory &category,
                                         QDatabaseConrol *control,
                                         QWidget *parent)
    : AbstractTab::QAbstractEditDialog(control, parent),
    category(category)
{
    this->setWindowTitle(tr("Изменение категории"));
    this->setGui();
    this->fillForm();
}

void QCategoryEditDialog::setGui()
{
    descriptionWidget = new QEdit(this);
    descriptionWidget->setTitle(tr("Описание"));
    AbstractTab::QAbstractEditDialog::addWidget(descriptionWidget);

    colorLabel = new QLabel(tr("Цвет фона:"));
    AbstractTab::QAbstractEditDialog::addWidget(colorLabel);

    colorWidget = new SalesWidgets::QColorWidget(this);
    AbstractTab::QAbstractEditDialog::addWidget(colorWidget);

    pointSalesWidget = new QMultipleChoiceBox(this);
    pointSalesWidget->setTitle(tr("Точки продаж: "));
    pointSalesWidget->setHeight(300, 500);
    pointSalesWidget->setItems(this->getPointSalesForWidget());
    AbstractTab::QAbstractEditDialog::addWidget(pointSalesWidget);
}

void QCategoryEditDialog::fillForm()
{
    nameWidget->setEditText(category.name);
    descriptionWidget->setEditText(category.description);
    QColor color(category.color.red(), category.color.green(), category.color.blue());
    colorWidget->setColor(color);
}

void QCategoryEditDialog::acceptDialog()
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

void QCategoryEditDialog::updateInformation()
{
    category.name = nameWidget->getEditText();
    category.description = descriptionWidget->getEditText();
    category.color.setRed(colorWidget->getColor().red());
    category.color.setGreen(colorWidget->getColor().green());
    category.color.setBlue(colorWidget->getColor().blue());
    category.idPointSale.clear();
    QVector<MultipleChoiceBox::ItemInformation> selectedPointSales = pointSalesWidget->getSelectedItems();
    for (int i = 0; i < selectedPointSales.size(); i++) {
            category.idPointSale.push_back(selectedPointSales.at(i).id);
    }
}

QVector<MultipleChoiceBox::ItemInformation> QCategoryEditDialog::getPointSalesForWidget()
{
    QVector<MultipleChoiceBox::ItemInformation> output;
    QVector<QPointSale> pointSales = db->pointSale->getPointSales();
    QVector<int> idSelectedPointSales;

    if (category.id > 0) {
        idSelectedPointSales = db->category->getIdPointSales(category.id);
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

void QCategoryEditDialog::slotSaveChanges()
{
    this->updateInformation();
    this->acceptDialog();
}
