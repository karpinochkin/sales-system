#ifndef QVOLUMEEDITDIALOG_H
#define QVOLUMEEDITDIALOG_H

#include "../commonFiles/SalesSystem/QVolumeProduct/qvolumeproduct.h"
#include "../QAbstractTab/qabstracteditdialog.h"
#include "../../widgets/QNumberEdit/qnumberedit.h"
#include "../../widgets/QMultipleChoiceBox/qmultiplechoicebox.h"

namespace Gui::DatabaseTabs {

class QVolumeEditDialog : public AbstractTab::QAbstractEditDialog
{
    Q_OBJECT
public:
    ~QVolumeEditDialog() override = default;
    static QVolumeProduct show(QDatabaseConrol *control,
                               bool *result,
                               QWidget *parent);
    static QVolumeProduct show(const QVolumeProduct &volume,
                               QDatabaseConrol *control,
                               bool *result,
                               QWidget *parent);

private:
    QVolumeEditDialog(QDatabaseConrol *control,
                      QWidget *parent = nullptr);
    QVolumeEditDialog(const QVolumeProduct &volume,
                      QDatabaseConrol *control,
                      QWidget *parent = nullptr);
    void setGui();
    void fillForm();
    void acceptDialog();
    void updateInformation();
    QVector<MultipleChoiceBox::ItemInformation> getProductsForWidget();

    QVolumeProduct volume;
    QNumberEdit *volumeWidget = nullptr;
    QEdit *descriptionWidget = nullptr;
    QEdit *unitsWidget = nullptr;
    QMultipleChoiceBox *productsWidget = nullptr;

private slots:
    void slotSaveChanges() override;
};

}

#endif // QVOLUMEEDITDIALOG_H
