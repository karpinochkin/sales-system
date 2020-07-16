#ifndef QSTATISTICSCHOICEDIALOG_H
#define QSTATISTICSCHOICEDIALOG_H

#include <QDialog>
#include "../widgets/QSalesComboBox/qsalescombobox.h"


class QStatisticsChoiceDialog : public QDialog
{
    Q_OBJECT
public:
    QStatisticsChoiceDialog() = delete;
    ~QStatisticsChoiceDialog() override = default;

    static SalesComboBox::ItemInformation show(const QString &title,
                                               QVector<SalesComboBox::ItemInformation> &items,
                                               bool *result,
                                               QWidget *parent);


private:
    QVBoxLayout *mainLayout = nullptr;
    SalesComboBox::QSalesComboBox *comboBox = nullptr;
    SalesComboBox::ItemInformation information;

    explicit QStatisticsChoiceDialog(const QString &title,
                                     QVector<SalesComboBox::ItemInformation> &items,
                                     QWidget *parent = nullptr);
    void setGui();
    void setTitle(const QString &title);
    void setItems(QVector<SalesComboBox::ItemInformation> &items);

};





#endif // QSTATISTICSCHOICEDIALOG_H
