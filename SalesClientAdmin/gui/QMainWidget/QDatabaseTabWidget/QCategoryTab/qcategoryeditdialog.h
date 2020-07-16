#ifndef QCATEGORYEDITDIALOG_H
#define QCATEGORYEDITDIALOG_H

#include "../commonFiles/SalesSystem/QSalesСategory/qsalescategory.h"
#include "../QAbstractTab/qabstracteditdialog.h"
#include "../../widgets/QColorWidget/qcolorwidget.h"
#include "../../widgets/QMultipleChoiceBox/qmultiplechoicebox.h"
#include <QMessageBox>

namespace Gui::DatabaseTabs {

class QCategoryEditDialog : public AbstractTab::QAbstractEditDialog
{
    Q_OBJECT
public:
    ~QCategoryEditDialog() override = default;

    static QSalesCategory show(QDatabaseConrol *control,
                                bool *result,
                                QWidget *parent);
    static QSalesCategory show(const QSalesCategory &category,
                                QDatabaseConrol *control,
                                bool *result,
                                QWidget *parent);

private:
    QCategoryEditDialog(QDatabaseConrol *control,
                    QWidget *parent = nullptr);
    QCategoryEditDialog(const QSalesCategory &category,
                    QDatabaseConrol *control,
                    QWidget *parent = nullptr);
    void setGui();
    void fillForm();
    void acceptDialog();
    void updateInformation();
    QVector<MultipleChoiceBox::ItemInformation> getPointSalesForWidget();

    QSalesCategory category;
    QEdit *descriptionWidget = nullptr;
    QLabel *colorLabel = nullptr;
    SalesWidgets::QColorWidget *colorWidget = nullptr;
    QMultipleChoiceBox *pointSalesWidget = nullptr;

private slots:
    void slotSaveChanges() override;
};

}

#endif // QCATEGORYEDITDIALOG_H
