#ifndef QDATERANGEDIALOG_H
#define QDATERANGEDIALOG_H

#include <QDialog>
#include <QVBoxLayout>
#include <QDate>
#include <QCheckBox>
#include <QPushButton>
#include "../../QMainWidget/widgets/QSalesCalendarInterval/qsalescalendarinterval.h"

namespace Gui::Loader {

struct DateRange
{
    QDate startDate;
    QDate endDate;
    bool allDates = false;
};

class QDateRangeDialog : public QDialog
{
    Q_OBJECT
public:
    ~QDateRangeDialog() = default;
    static DateRange getDateRange(bool *result,
                                  const QString &title,
                                  QWidget *parent = nullptr);

private:
    DateRange dateRange;
    SalesWidgets::QSalesCalendarInterval *dateRangeWidget = nullptr;
    QVBoxLayout *mainLayout = nullptr;
    QCheckBox *allDatesCheckBox = nullptr;
    QPushButton *button = nullptr;

    explicit QDateRangeDialog(const QString &title,
                              QWidget *parent = nullptr);
    void setGui();
    void setDateRange();
};

}

#endif // QDATERANGEDIALOG_H
