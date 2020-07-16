#include "qdaterangedialog.h"

using namespace Gui::Loader;

DateRange QDateRangeDialog::getDateRange(bool *result , const QString& title, QWidget *parent)
{
    DateRange output;
    QDateRangeDialog dlg(title, parent);
    int answer = dlg.exec();

    if (answer == QDialog::Accepted) {
        output = {dlg.dateRange.startDate,
                  dlg.dateRange.endDate,
                  dlg.dateRange.allDates};

        *result = true;
    }
    else {
        *result = false;
    }
    return output;
}

QDateRangeDialog::QDateRangeDialog(const QString &title,
                                   QWidget *parent)
    : QDialog(parent)
{
    this->setModal(true);
    this->setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint);
    this->setWindowTitle(title);
    this->setDateRange();
    this->setGui();
}

void QDateRangeDialog::setGui()
{
    mainLayout = new QVBoxLayout(this);
    dateRangeWidget = new SalesWidgets::QSalesCalendarInterval(this);
    allDatesCheckBox = new QCheckBox(tr("Все даты"), this);
    button = new QPushButton(tr("Далее"), this);

    dateRangeWidget->setStartDate(dateRange.startDate);
    dateRangeWidget->setEndDate(dateRange.endDate);

    connect(allDatesCheckBox, &QCheckBox::clicked,
            this, [=](){
        if (allDatesCheckBox->isChecked()) {
            allDatesCheckBox->setChecked(true);
            dateRangeWidget->setEnabled(false);
        }
        else {
            allDatesCheckBox->setChecked(false);
            dateRangeWidget->setEnabled(true);
        }
    });

    connect(button, &QPushButton::clicked,
            this, [=](){
        dateRange.startDate = dateRangeWidget->getStartDate();
        dateRange.endDate = dateRangeWidget->getEndDate().addDays(1);
        dateRange.allDates = allDatesCheckBox->checkState();
        this->accept();
    });

    mainLayout->addWidget(dateRangeWidget);
    mainLayout->addWidget(allDatesCheckBox);
    mainLayout->addWidget(button);
}

void QDateRangeDialog::setDateRange()
{
    dateRange.endDate = QDate::currentDate();
    dateRange.startDate.setDate(dateRange.endDate.year(),
                                dateRange.endDate.month() - 6,
                                dateRange.endDate.day());
}
