#ifndef QPRODUCTSEDITDIALOG_H
#define QPRODUCTSEDITDIALOG_H

#include <QMessageBox>
#include <QFileDialog>
#include "../commonFiles/SalesSystem/QProduct/qproduct.h"
#include "../QAbstractTab/qabstracteditdialog.h"
#include "../../widgets/QEdit/qedit.h"
#include "../../widgets/QColorWidget/qcolorwidget.h"
#include "../../widgets/QPictureWidget/qpicturewidget.h"
#include "../../widgets/QMultipleChoiceBox/qmultiplechoicebox.h"
#include "../../widgets/QSalesComboBox/qsalescombobox.h"

namespace Gui::DatabaseTabs {

class QProductsEditDialog : public AbstractTab::QAbstractEditDialog
{
    Q_OBJECT
public:
    ~QProductsEditDialog() override = default;

    static QProduct show(QDatabaseConrol *control,
                         bool *result,
                         QWidget *parent);
    static QProduct show(const QProduct &product,
                         QDatabaseConrol *control,
                         bool *result, bool *isShawPriceWindow,
                         QWidget *parent);
private:
    QProductsEditDialog(QDatabaseConrol *control,
                        QWidget *parent = nullptr);
    QProductsEditDialog(const QProduct &product,
                        QDatabaseConrol *control,
                        QWidget *parent = nullptr);

    void setGui();
    void fillForm();
    void acceptDialog();
    void updateInformation();
    QVector<MultipleChoiceBox::ItemInformation> getCategoriesForWidget();
    QVector<SalesComboBox::ItemInformation> getPricesForWidget();

    QProduct product;
    bool isShowPriceWindow = false;

    QEdit *descriptionWidget = nullptr;
    QLabel *colorTitle = nullptr;
    SalesWidgets::QColorWidget *colorWidget = nullptr;
    QLabel *pictureLabel = nullptr;
    SalesWidgets::QPictureWidget *pictureWidget = nullptr;
    QMultipleChoiceBox *categoryWidget = nullptr;
    QPushButton *priceButton = nullptr;
private slots:
    void slotSaveChanges() override;
    void slotChangePrice();
};

}
#endif // QPRODUCTSEDITDIALOG_H
