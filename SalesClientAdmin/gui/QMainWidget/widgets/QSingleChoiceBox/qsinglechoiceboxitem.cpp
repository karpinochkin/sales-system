#include "qsinglechoiceboxitem.h"

using namespace SalesWidgets::SingleChoiceBox;

QSingleChoiceBoxItem::QSingleChoiceBoxItem(const SingleChoiceBox::ItemInformation &item,
                                           QWidget *parent)
    : QWidget(parent),
      item(item)
{
    this->setGui();
}

ItemInformation QSingleChoiceBoxItem::getInformation()
{
    return item;
}

void QSingleChoiceBoxItem::setSelected()
{
    this->select();
}

void QSingleChoiceBoxItem::setUnselected()
{
    item.status = false;
    itemRadioButton->setChecked(false);
}

void QSingleChoiceBoxItem::mouseReleaseEvent(QMouseEvent *)
{
    this->select();
}

void QSingleChoiceBoxItem::setGui()
{
    mainLayout = new QHBoxLayout(this);
    itemRadioButton = new QRadioButton(this);
    connect(itemRadioButton, &QRadioButton::clicked,
            this, &QSingleChoiceBoxItem::select);
    mainLayout->addWidget(itemRadioButton);

    itemName = new QLabel(this);
    mainLayout->addWidget(itemName, 1);

    itemRadioButton->setChecked(item.status);
    itemName->setText(item.name);
}

void QSingleChoiceBoxItem::select()
{
    itemRadioButton->setChecked(true);
    item.status = itemRadioButton->isChecked();

    emit (this->signalItemWasSelected(item));
}
