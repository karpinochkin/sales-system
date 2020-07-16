#include "qsalesdatetimeedit.h"

using namespace SalesWidgets;

QSalesDateTimeEdit::QSalesDateTimeEdit(QWidget *parent) : QWidget(parent)
{
    this->setGui();
}

void QSalesDateTimeEdit::setTitle(const QString &title)
{
    titleLabel->setText(title);
}

QString QSalesDateTimeEdit::getTitle()
{
    return titleLabel->text();
}

void QSalesDateTimeEdit::setDateTime(const QDateTime &dateTime)
{
    dateTimeEdit->setDateTime(dateTime);
}

QDateTime QSalesDateTimeEdit::getDateTime()
{
    if (currentTimeCheckBox->isChecked()) {
        return QDateTime::currentDateTime();
    }

    return dateTimeEdit->dateTime();
}

void QSalesDateTimeEdit::setGui()
{
    mainLayout = new QVBoxLayout(this);
    titleLabel = new QLabel(this);
    dateTimeEdit = new QDateTimeEdit(this);
    currentTimeCheckBox = new QCheckBox(tr("Текущая дата"), this);

    mainLayout->addWidget(titleLabel);
    mainLayout->addWidget(dateTimeEdit);
    mainLayout->addWidget(currentTimeCheckBox);
}
