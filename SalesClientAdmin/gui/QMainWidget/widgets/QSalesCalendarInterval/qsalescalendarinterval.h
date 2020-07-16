#ifndef QSALESDATEINTERVALWIDGET_H
#define QSALESDATEINTERVALWIDGET_H

#include <QWidget>
#include <QGroupBox>
#include <QDateEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>

namespace SalesWidgets {

class QSalesCalendarInterval : public QWidget
{
    Q_OBJECT
public:
    explicit QSalesCalendarInterval(QWidget *parent = nullptr);
    ~QSalesCalendarInterval() = default;

    qint64 getInterval();
    QDate getStartDate();
    QDate getEndDate();
    bool isDateValid();
    void setStartDate(const QDate &startDateEdit);
    void setEndDate(const QDate &endDateEdit);

private:
    QVBoxLayout *mainLayout = nullptr;
    QGroupBox *groupBox = nullptr;
    QHBoxLayout *dateLayout = nullptr;
    QLabel *startLabel = nullptr;
    QLabel *endLabel = nullptr;
    QDateEdit *startDateEdit = nullptr;
    QDateEdit *endDateEdit = nullptr;

    void createWidgets();
    void setGui();
    void connects();
    void addToLayout();

signals:
    void startDateChanged();
    void endDateChanged();
};

}

#endif // QSALESDATEINTERVALWIDGET_H
