#ifndef QPOINTSALEEDITDIALOG_H
#define QPOINTSALEEDITDIALOG_H

#include <QMessageBox>
#include <QFileDialog>
#include "../commonFiles/SalesSystem/QPointSale/qpointsale.h"
#include "../QAbstractTab/qabstracteditdialog.h"
#include "../../widgets/QMultipleChoiceBox/qmultiplechoicebox.h"

namespace Gui::DatabaseTabs {

class QPointSaleEditDialog : public AbstractTab::QAbstractEditDialog
{
    Q_OBJECT
public:
    ~QPointSaleEditDialog() override = default;

    static QPointSale show(QDatabaseConrol *control,
                                bool *result,
                                QWidget *parent);
    static QPointSale show(const QPointSale &pointSale,
                                QDatabaseConrol *control,
                                bool *result,
                                QWidget *parent);

private:
    QPointSaleEditDialog(QDatabaseConrol *control,
                    QWidget *parent = nullptr);
    QPointSaleEditDialog(const QPointSale &pointSale,
                    QDatabaseConrol *control,
                    QWidget *parent = nullptr);
    void setGui();
    void fillForm();
    void acceptDialog();
    void updateInformation();

    QVector<MultipleChoiceBox::ItemInformation> getCategoriesForWidget();
    QVector<MultipleChoiceBox::ItemInformation> getProductsForWidget();

    QPointSale pointSale;
    QMultipleChoiceBox *categoryWidget = nullptr;
    QMultipleChoiceBox *productWidget = nullptr;

private slots:
    void slotSaveChanges() override;
};

}

#endif // QPOINTSALEEDITDIALOG_H
