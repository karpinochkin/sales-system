#ifndef QPRICESEDITFORPRODUCTDIALOG_H
#define QPRICESEDITFORPRODUCTDIALOG_H

#include <QMessageBox>
#include <QFileDialog>
#include "../commonFiles/SalesSystem/QPrice/qprice.h"
#include "../QAbstractTab/qabstracteditdialog.h"
#include "../../widgets/QDoubleNumberEdit/qdoublenumberedit.h"
#include "../../widgets/QSalesDateTimeEdit/qsalesdatetimeedit.h"
#include "../../widgets/QSingleChoiceBox/qsinglechoicebox.h"
#include "../../widgets/QMultipleChoiceBox/qmultiplechoicebox.h"

namespace Gui::DatabaseTabs::PricesTab {

struct PointSale {
    int id = -1;
    QString name = "";
};

struct Product {
    int id = -1;
    QString name = "";
};

}

namespace Gui::DatabaseTabs {

class QPricesEditForProductDialog : public AbstractTab::QAbstractEditDialog
{
    Q_OBJECT
public:
    ~QPricesEditForProductDialog() override = default;

    static QPrice show(QDatabaseConrol *control,
                       const PricesTab::Product &product,
                       bool *result,
                       QWidget *parent);
    static QPrice show(const QPrice &price,
                       QDatabaseConrol *control,
                       const PricesTab::Product &product,
                       bool *result,
                       QWidget *parent);

private:
    QPricesEditForProductDialog(QDatabaseConrol *control,
                      const PricesTab::Product &product,
                      QWidget *parent = nullptr);
    QPricesEditForProductDialog(const QPrice &price,
                      QDatabaseConrol *control,
                      const PricesTab::Product &product,
                      QWidget *parent = nullptr);
    void setGui();
    void fillForm();
    void acceptDialog();
    void updateInformation();
    QVector<SingleChoiceBox::ItemInformation> getVolumesForWidget();
    QVector<SingleChoiceBox::ItemInformation> getCategoriesForWidget();
    QVector<MultipleChoiceBox::ItemInformation> getPointSalesForWidget();

    QPrice price;
    PricesTab::Product product;

    QEdit *descriptionWidget = nullptr;
    QEdit *productWidget = nullptr;
    QDoubleNumberEdit *valueWidget = nullptr;
    QSalesDateTimeEdit *dateTimeWidget = nullptr;
    QSingleChoiceBox *volumeWidget = nullptr;
    QSingleChoiceBox *categoryWidget = nullptr;
    QMultipleChoiceBox *pointSalesWidget = nullptr;

private slots:
    void slotSaveChanges() override;
};

}

#endif // QPRICESEDITDIALOG_H
