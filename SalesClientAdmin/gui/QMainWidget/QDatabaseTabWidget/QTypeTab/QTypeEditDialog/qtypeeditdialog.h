#ifndef QTYPEEDITDIALOG_H
#define QTYPEEDITDIALOG_H

#include <QMessageBox>
#include <QFileDialog>
#include "../commonFiles/SalesSystem/QPaymentType/qpaymenttype.h"
#include "../../QAbstractTab/qabstracteditdialog.h"

namespace Gui::DatabaseTabs {

class QTypeEditDialog : public AbstractTab::QAbstractEditDialog
{
    Q_OBJECT
public:
    ~QTypeEditDialog() override = default;

    static QPaymentType show(QDatabaseConrol *control,
                                bool *result,
                                QWidget *parent);
    static QPaymentType show(const QPaymentType &type,
                                QDatabaseConrol *control,
                                bool *result,
                                QWidget *parent);

private:
    QTypeEditDialog(QDatabaseConrol *control,
                    QWidget *parent = nullptr);
    QTypeEditDialog(const QPaymentType &type,
                    QDatabaseConrol *control,
                    QWidget *parent = nullptr);
    void setGui();
    void fillForm();
    void acceptDialog();
    void updateInformation();

    QPaymentType type;
    QEdit *descriptionWidget = nullptr;

private slots:
    void slotSaveChanges() override;
};

}

#endif // QTYPEEDITDIALOG_H

