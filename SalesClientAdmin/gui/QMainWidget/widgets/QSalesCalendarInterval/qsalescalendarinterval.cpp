#include "qsalescalendarinterval.h"

using namespace SalesWidgets;

QSalesCalendarInterval::QSalesCalendarInterval(QWidget *parent)
    : QWidget(parent)
{
    this->createWidgets();
    this->setGui();
    this->connects();
    this->addToLayout();
}

qint64 QSalesCalendarInterval::getInterval()
{
    qint64 daysCount = startDateEdit->date().daysTo(endDateEdit->date());
    if (daysCount < 0) {
        return -1;
    }
    return daysCount;
}

QDate QSalesCalendarInterval::getStartDate()
{
    return startDateEdit->date();
}

QDate QSalesCalendarInterval::getEndDate()
{
    return endDateEdit->date();
}

bool QSalesCalendarInterval::isDateValid()
{
    if (getInterval() < 0) {
        return false;
    }
    return true;
}

void QSalesCalendarInterval::setStartDate(const QDate &startDate)
{
    startDateEdit->setDate(startDate);
}

void QSalesCalendarInterval::setEndDate(const QDate &endDate)
{
    endDateEdit->setDate(endDate);
}

void QSalesCalendarInterval::createWidgets()
{
    mainLayout = new QVBoxLayout;
    groupBox = new QGroupBox(this);
    dateLayout = new QHBoxLayout(groupBox);
    startLabel = new QLabel(tr("С: "));
    endLabel = new QLabel(tr("По: "));
    startDateEdit = new QDateEdit(this);
    endDateEdit = new QDateEdit(this);
}

void QSalesCalendarInterval::setGui()
{
    startDateEdit->setCalendarPopup(true);
    startDateEdit->setDate(QDate::currentDate());
    endDateEdit->setCalendarPopup(true);
    endDateEdit->setDate(QDate::currentDate());
    groupBox->setAlignment(Qt::AlignTop);
    mainLayout->setAlignment(Qt::AlignTop);
    mainLayout->setMargin(0);
}

void QSalesCalendarInterval::connects()
{
    connect(startDateEdit, &QDateEdit::dateChanged,
            this, &QSalesCalendarInterval::startDateChanged);
    connect(endDateEdit, &QDateEdit::dateChanged,
            this, &QSalesCalendarInterval::endDateChanged);
}

void QSalesCalendarInterval::addToLayout()
{
    this->setLayout(mainLayout);
    mainLayout->addWidget(groupBox);
    groupBox->setLayout(dateLayout);
    dateLayout->addWidget(startLabel);
    dateLayout->addWidget(startDateEdit);
    dateLayout->addSpacing(20);
    dateLayout->addWidget(endLabel);
    dateLayout->addWidget(endDateEdit);
}
