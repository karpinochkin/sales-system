#include "qsalescombobox.h"

SalesComboBox::QSalesComboBox::QSalesComboBox(QWidget *parent)
    : QWidget(parent)
{
    this->setGui();
}

void SalesComboBox::QSalesComboBox::setItems(const QVector<SalesComboBox::ItemInformation> &items)
{
    for (int i =0; i < items.size(); i++) {
        comboBox->addItem(items.at(i).name, QVariant::fromValue(items.at(i).id));
    }
}

QVector<SalesComboBox::ItemInformation> SalesComboBox::QSalesComboBox::getItems() const
{
    QVector<SalesComboBox::ItemInformation> output;
    for (int i = 0; i < comboBox->count(); i++) {
        ItemInformation item;

        item.id = comboBox->itemData(i).toInt();
        item.name = comboBox->itemText(i);
        output.push_back(item);
    }
    return output;
}

SalesComboBox::ItemInformation SalesComboBox::QSalesComboBox::getSelected() const
{
    ItemInformation output;

    output.id = comboBox->currentData().toInt();
    output.name = comboBox->currentText();

    return output;
}

void SalesComboBox::QSalesComboBox::setTitle(const QString &text)
{
    titleLabel->setText(text);
}

void SalesComboBox::QSalesComboBox::setButtonText(const QString &text)
{
    button->setText(text);
}

QString SalesComboBox::QSalesComboBox::getTitle() const
{
    return titleLabel->text();
}

void SalesComboBox::QSalesComboBox::hideTitle() const
{
    titleLabel->hide();
}

void SalesComboBox::QSalesComboBox::enableButton()
{
    button->setEnabled(true);
}

void SalesComboBox::QSalesComboBox::disableButton()
{
    button->setEnabled(false);
}

void SalesComboBox::QSalesComboBox::setGui()
{
    mainLayout = new QVBoxLayout(this);
    titleLabel = new QLabel(this);
    comboBox = new QComboBox(this);
    button = new QPushButton(tr("Изменить"));

    mainLayout->addWidget(titleLabel);
    mainLayout->addWidget(comboBox);
    mainLayout->addWidget(button);
    mainLayout->setAlignment(Qt::AlignTop);

    connect(button, &QPushButton::clicked,
            this, [=](){
        emit(this->clickedSendItem(getSelected()));
    });
    connect(button, &QPushButton::clicked,
            this, &QSalesComboBox::clicked);
}
