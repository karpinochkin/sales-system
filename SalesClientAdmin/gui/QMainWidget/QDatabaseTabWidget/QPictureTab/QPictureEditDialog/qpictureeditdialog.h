#ifndef TESTPICTUREEDITDIALOG_H
#define TESTPICTUREEDITDIALOG_H

#include <QMessageBox>
#include <QFileDialog>
#include "../commonFiles/SalesSystem/QProductPicture/qproductpicture.h"
#include "../../QAbstractTab/qabstracteditdialog.h"

namespace Gui::DatabaseTabs {

class QPictureEditDialog : public AbstractTab::QAbstractEditDialog
{
    Q_OBJECT
public:
    ~QPictureEditDialog() override = default;

    static QProductPicture show(QDatabaseConrol *control,
                                bool *result,
                                QWidget *parent);
    static QProductPicture show(const QProductPicture &picture,
                                QDatabaseConrol *control,
                                bool *result,
                                QWidget *parent);
private:
    QPictureEditDialog(QDatabaseConrol *control,
                          QWidget *parent = nullptr);
    QPictureEditDialog(const QProductPicture &picture,
                          QDatabaseConrol *control,
                          QWidget *parent = nullptr);

    void createWidgets();
    void setGui();
    void connects();
    void addToMainLayout();
    void fillForm();

    bool isPictureNameEmpty();
    bool isPictureDataEmpty();
    void updatePictureInformation();
    void acceptDialog();

    QProductPicture picture;
    QPushButton *addPictureButton = nullptr;

private slots:
    void slotSaveChanges() override;
    void slotAddPicture();
};

}

#endif // TESTPICTUREEDITDIALOG_H
