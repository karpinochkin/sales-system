#ifndef QUSERDIALOG_H
#define QUSERDIALOG_H

#include <QObject>
#include <QDialog>
#include <QWidget>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QCheckBox>

namespace Gui::Loader {

struct UserAccount
{
    QString login = "";
    QString password = "";
    bool save = false;
};

class QAccountDialog : public QDialog
{
    Q_OBJECT
public:
    static UserAccount getAccount(bool *result = nullptr,
                                  QWidget *parent = nullptr);
    static UserAccount getAccount(const UserAccount &account,
                                  bool *result = nullptr,
                                  QWidget *parent = nullptr);
    ~QAccountDialog() = default;

private:
    QAccountDialog(QWidget *parent = nullptr);
    void createForm();
    void connects();
    void addToWidget();

    QGridLayout *mainLayout = nullptr;
    QLabel *labelLogin = nullptr;
    QLineEdit *editLogin = nullptr;
    QLabel *labelPassword = nullptr;
    QLineEdit *editPassword = nullptr;

    QHBoxLayout *layoutButtons = nullptr;
    QPushButton *buttonOk = nullptr;
    QPushButton *buttonCancel = nullptr;
    QPushButton *buttonHosts = nullptr;

    QCheckBox *checkSaveLogin = nullptr;
};

}

#endif // QUSERDIALOG_H
