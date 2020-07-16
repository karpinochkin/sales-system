#include "qmultiplechoiceboxitem.h"

MultipleChoiceBox::QMultipleChoiceItem::QMultipleChoiceItem(const MultipleChoiceBox::ItemInformation &item,
                                                            QWidget *parent)
    : QWidget(parent),
      item(item)
{
    this->setGui();
}

MultipleChoiceBox::ItemInformation MultipleChoiceBox::QMultipleChoiceItem::getInfrotmation()
{
    return item;
}

void MultipleChoiceBox::QMultipleChoiceItem::selectItem()
{
    itemCheckBox->setChecked(true);

    if (item.status != true) {
        item.status = true;
        item.isWasChanged = !item.isWasChanged;
    }
}

void MultipleChoiceBox::QMultipleChoiceItem::unselectItem()
{
    itemCheckBox->setChecked(false);

    if (item.status != false) {
        item.status = false;
        item.isWasChanged = !item.isWasChanged;
    }
}

void MultipleChoiceBox::QMultipleChoiceItem::mouseReleaseEvent(QMouseEvent *)
{
    this->changeStatus(!(itemCheckBox->isChecked()));
}

void MultipleChoiceBox::QMultipleChoiceItem::setGui()
{
    mainLayout = new QHBoxLayout(this);
    itemCheckBox = new QCheckBox(this);
    connect(itemCheckBox, &QCheckBox::clicked,
            this, &QMultipleChoiceItem::slotCheckBoxChanged);
    mainLayout->addWidget(itemCheckBox);

    itemName = new QLabel(this);
    mainLayout->addWidget(itemName, 1);

    itemCheckBox->setChecked(item.status);
    itemName->setText(item.name);
}

void MultipleChoiceBox::QMultipleChoiceItem::changeStatus(bool status)
{
    if (status != itemCheckBox->isChecked()) {
        itemCheckBox->setChecked(status);
        this->slotCheckBoxChanged();
    }
}

void MultipleChoiceBox::QMultipleChoiceItem::slotCheckBoxChanged()
{
    item.status = itemCheckBox->isChecked();
    item.isWasChanged = !item.isWasChanged;
}
