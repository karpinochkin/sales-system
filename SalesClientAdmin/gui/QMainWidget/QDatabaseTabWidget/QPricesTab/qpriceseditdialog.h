#ifndef QPRICESEDITDIALOG_H
#define QPRICESEDITDIALOG_H

#include <QMessageBox>
#include <QFileDialog>
#include "../commonFiles/SalesSystem/QPrice/qprice.h"
#include "../QAbstractTab/qabstracteditdialog.h"
#include "../../widgets/QSingleChoiceBox/qsinglechoicebox.h"
#include "../../widgets/QMultipleChoiceBox/qmultiplechoicebox.h"
#include "../../widgets/QDoubleNumberEdit/qdoublenumberedit.h"
#include "../../widgets/QSalesDateTimeEdit/qsalesdatetimeedit.h"

namespace Gui::DatabaseTabs {

class QPricesEditDialog : public AbstractTab::QAbstractEditDialog
{
    Q_OBJECT
public:
    ~QPricesEditDialog() override = default;

    static QPrice show(QDatabaseConrol *control,
                       bool *result,
                       QWidget *parent);
    static QPrice show(const QPrice &price,
                       QDatabaseConrol *control,
                       bool *result,
                       QWidget *parent);

private:
    QPricesEditDialog(QDatabaseConrol *control,
                      QWidget *parent = nullptr);
    QPricesEditDialog(const QPrice &price,
                      QDatabaseConrol *control,
                      QWidget *parent = nullptr);
    void setGui();
    void fillForm();
    void acceptDialog();
    void updateInformation();
    QVector<SingleChoiceBox::ItemInformation> getVolumesForWidget();
    QVector<SingleChoiceBox::ItemInformation> getCategoriesForWidget();
    QVector<SingleChoiceBox::ItemInformation> getProductsForWidget();
    QVector<MultipleChoiceBox::ItemInformation> getPointSalesForWidget();

    QPrice price;
    QEdit *descriptionWidget = nullptr;
    QDoubleNumberEdit *valueWidget = nullptr;
    QSalesDateTimeEdit *dateTimeWidget = nullptr;
    QSingleChoiceBox *volumeWidget = nullptr;
    QSingleChoiceBox *categoryWidget = nullptr;
    QSingleChoiceBox *productWidget = nullptr;
    QMultipleChoiceBox *pointSaleWidget = nullptr;

private slots:
    void slotSaveChanges() override;
};

}

#endif // QPRICESEDITDIALOG_H
