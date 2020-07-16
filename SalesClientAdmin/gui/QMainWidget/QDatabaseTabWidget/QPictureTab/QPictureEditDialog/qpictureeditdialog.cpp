#include "qpictureeditdialog.h"

using namespace Gui::DatabaseTabs;

QProductPicture QPictureEditDialog::show(QDatabaseConrol *control, bool *result, QWidget *parent)
{
    QProductPicture output;
    QPictureEditDialog dlg(control, parent);
    int answer = dlg.exec();
    if ( answer == QDialog::Accepted) {
        output.id = dlg.picture.id;
        output.name = dlg.picture.name;
        output.data = dlg.picture.data;

        *result = true;
    }
    else {
        *result = false;
    }
    return output;
}

QProductPicture QPictureEditDialog::show(const QProductPicture &picture, QDatabaseConrol *control, bool *result, QWidget *parent)
{
    QProductPicture output;
    QPictureEditDialog dlg(picture, control, parent);
    int answer = dlg.exec();
    if ( answer == QDialog::Accepted) {
        output.id = dlg.picture.id;
        output.name = dlg.picture.name;
        output.data = dlg.picture.data;

        *result = true;
    }
    else {
        *result = false;
    }
    return output;
}

QPictureEditDialog::QPictureEditDialog(QDatabaseConrol *control, QWidget *parent)
    : AbstractTab::QAbstractEditDialog(control, parent)
{
    picture.id = -1;
    this->setWindowTitle(tr("Добавление изображения"));
    this->createWidgets();
    this->setGui();
    this->addToMainLayout();
    this->connects();
}

QPictureEditDialog::QPictureEditDialog(const QProductPicture &picture, QDatabaseConrol *control, QWidget *parent)
    : AbstractTab::QAbstractEditDialog(control, parent),
      picture(picture)
{
    this->setWindowTitle(tr("Изменение изображения"));
    this->createWidgets();
    this->setGui();
    this->addToMainLayout();
    this->connects();
    this->fillForm();
}

void QPictureEditDialog::createWidgets()
{
    addPictureButton = new QPushButton(tr("Выбрать картинку"), this);
}

void QPictureEditDialog::setGui()
{
    addPictureButton->setEnabled(true);
}

void QPictureEditDialog::connects()
{
    connect(addPictureButton, &QPushButton::clicked,
            this, &QPictureEditDialog::slotAddPicture);
}

void QPictureEditDialog::addToMainLayout()
{
    AbstractTab::QAbstractEditDialog::addWidget(addPictureButton);
}

void QPictureEditDialog::fillForm()
{
    nameWidget->setEditText(picture.name);
    addPictureButton->setEnabled(false);
}

bool QPictureEditDialog::isPictureNameEmpty()
{
    if (picture.name == ""
            || picture.name == nullptr) {
        return true;
    } else {
        return false;
    }
}

bool QPictureEditDialog::isPictureDataEmpty()
{
    if (picture.data == ""
            || picture.data == nullptr) {
        return true;
    }
    else {
        return false;
    }
}

void QPictureEditDialog::updatePictureInformation()
{
    picture.name = nameWidget->getEditText();
}

void QPictureEditDialog::acceptDialog()
{
    if (isPictureNameEmpty()) {
        QMessageBox::critical(this, tr("Ошибка"), tr("Вы не ввели название изображения"));
    }
    else if (isPictureDataEmpty()) {
        QMessageBox::critical(this, tr("Ошибка"), tr("Вы не выбрали изображение"));
    }
    else {
        this->accept();
    }
}

void QPictureEditDialog::slotSaveChanges()
{
    this->updatePictureInformation();
    this->acceptDialog();
}

void QPictureEditDialog::slotAddPicture()
{
    QString picturePath = QFileDialog::getOpenFileName(this,
                                                       tr("Выбрать изображение"),
                                                       "",
                                                       "*.png");
    if (picturePath.isEmpty()) {
        QMessageBox::critical(this,tr("Ошибка"),tr("Вы не выбрали изображение"));
    }
    else {
        QFile file(picturePath);
        file.open(QIODevice::ReadOnly);
        picture.data = file.readAll();
        file.close();
    }
}
