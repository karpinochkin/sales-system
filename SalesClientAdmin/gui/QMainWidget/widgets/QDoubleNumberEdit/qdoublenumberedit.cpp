#include "qdoublenumberedit.h"

using namespace SalesWidgets;

QDoubleNumberEdit::QDoubleNumberEdit(QWidget *parent) : QWidget(parent)
{
    this->createWidgets();
    this->addToLayout();
}

void QDoubleNumberEdit::setTitle(const QString &text)
{
    titleLabel->setText(text);
}

void QDoubleNumberEdit::setNumber(const double value)
{
    this->number->setValue(value);
}

QString QDoubleNumberEdit::getTitle() const
{
    return titleLabel->text();
}

double QDoubleNumberEdit::getNumber() const
{
    return number->value();
}

void QDoubleNumberEdit::createWidgets()
{
    layout = new QVBoxLayout(this);
    titleLabel = new QLabel(this);
    number = new QDoubleSpinBox(this);
    number->setMaximum(1000000000);
}

void QDoubleNumberEdit::addToLayout()
{
    layout->addWidget(titleLabel);
    layout->addWidget(number);
}
