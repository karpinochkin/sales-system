#ifndef QSALESDATETIMEEDIT_H
#define QSALESDATETIMEEDIT_H

#include <QCheckBox>
#include <QVBoxLayout>
#include <QDateTimeEdit>
#include <QWidget>
#include <QLabel>

namespace SalesWidgets {

class QSalesDateTimeEdit : public QWidget
{
    Q_OBJECT
public:
    explicit QSalesDateTimeEdit(QWidget *parent = nullptr);
    ~QSalesDateTimeEdit() = default;

    void setTitle(const QString &title);
    QString getTitle();
    void setDateTime(const QDateTime &dateTime);
    QDateTime getDateTime();

private:
    QVBoxLayout *mainLayout = nullptr;
    QLabel *titleLabel = nullptr;
    QDateTimeEdit *dateTimeEdit = nullptr;
    QCheckBox *currentTimeCheckBox = nullptr;

    void setGui();

};

}
#endif // QSALESDATETIMEEDIT_H
