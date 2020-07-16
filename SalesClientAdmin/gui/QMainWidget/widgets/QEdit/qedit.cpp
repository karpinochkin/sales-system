#include "qedit.h"

using namespace SalesWidgets;

QEdit::QEdit(QWidget *parent)
    : QWidget(parent)
{
    this->createWidgets();
    this->addToLayout();
}

void QEdit::setTitle(const QString &text)
{
    titleLabel->setText(text);
}

void QEdit::setEditText(const QString &text)
{
    edit->setText(text);
}

QString QEdit::getTitle()
{
    return titleLabel->text();
}

QString QEdit::getEditText()
{
    return edit->text();
}

void QEdit::createWidgets()
{
    layout = new QVBoxLayout(this);
    titleLabel = new QLabel(this);
    edit = new QLineEdit(this);
}

void QEdit::addToLayout()
{
    layout->addWidget(titleLabel);
    layout->addWidget(edit);
}
