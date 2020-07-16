#ifndef QUSEREDITDIALOG_H
#define QUSEREDITDIALOG_H

#include "../QAbstractTab/qabstracteditdialog.h"
#include "../commonFiles/SalesSystem/QUser/quser.h"

namespace Gui::DatabaseTabs {

class QUserEditDialog : public AbstractTab::QAbstractEditDialog
{
    Q_OBJECT
public:
    ~QUserEditDialog() override = default;

    static QUser show(QDatabaseConrol *control,
                                bool *result,
                                QWidget *parent);
    static QUser show(const QUser &user,
                                QDatabaseConrol *control,
                                bool *result,
                                QWidget *parent);

private:
    QUserEditDialog(QDatabaseConrol *control,
                    QWidget *parent = nullptr);
    QUserEditDialog(const QUser &user,
                    QDatabaseConrol *control,
                    QWidget *parent = nullptr);
    void setGui();
    void fillForm();
    void acceptDialog();
    void updateInformation();

    QUser user;
    QEdit *firstNameWidget = nullptr;
    QEdit *patronymicWidget = nullptr;
    QEdit *surnameWidget = nullptr;
    QEdit *passwordWidget = nullptr;

private slots:
    void slotSaveChanges() override;
};

}

#endif // QUSEREDITDIALOG_H
