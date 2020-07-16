#include "qnumberedit.h"

using namespace SalesWidgets;

QNumberEdit::QNumberEdit(QWidget *parent)
    : QWidget(parent)
{
    this->createWidgets();
    this->addToLayout();
}

void QNumberEdit::setTitle(const QString &text)
{
    titleLabel->setText(text);
}

void QNumberEdit::setNumber(const int value)
{
    this->number->setValue(value);
}

QString QNumberEdit::getTitle() const
{
    return titleLabel->text();
}

int QNumberEdit::getNumber() const
{
    return number->value();
}

void QNumberEdit::createWidgets()
{
    layout = new QVBoxLayout(this);
    titleLabel = new QLabel(this);
    number = new QSpinBox(this);
    number->setMaximum(10000);
}

void QNumberEdit::addToLayout()
{
    layout->addWidget(titleLabel);
    layout->addWidget(number);
}
