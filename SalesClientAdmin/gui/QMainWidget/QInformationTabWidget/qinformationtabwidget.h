#ifndef QInformationTabWidget_H
#define QInformationTabWidget_H

#include <QWidget>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QIntValidator>
#include "../commonClientFiles/QNetManager/qnetmanager.h"


class QInformationTabWidget : public QWidget
{
    Q_OBJECT
public:
    QInformationTabWidget() = delete;
    explicit QInformationTabWidget(QNetManager *netManager,
                                QWidget *parent = nullptr);
    ~QInformationTabWidget();

private:
    QNetManager *networkManager = nullptr;
    QTimer *update = nullptr;

    QVBoxLayout *mainLayout = nullptr;
    QVBoxLayout *mainGroupBoxLayout = nullptr;
    QGridLayout *statusLayout = nullptr;
    QGridLayout *userLayout = nullptr;

    QGroupBox *mainGroupBox = nullptr;
    QGroupBox *statusGroupBox = nullptr;
    QGroupBox *userGroupBox = nullptr;

    QLabel *statusConnectLabel = nullptr;
    QLabel *statusHostLabel = nullptr;
    QLabel *statusPortLabel = nullptr;
    QLabel *userLoginLabel = nullptr;
    QLabel *userNameLabel = nullptr;
    QLabel *userSurnameLabel = nullptr;
    QLabel *userPatronymicLabel = nullptr;

    QLineEdit *statusConnectEdit = nullptr;
    QLineEdit *statusHostEdit = nullptr;
    QLineEdit *statusPortEdit = nullptr;
    QLineEdit *userLoginEdit = nullptr;
    QLineEdit *userNameEdit = nullptr;
    QLineEdit *userSurnameEdit = nullptr;
    QLineEdit *userPatronymicEdit = nullptr;

    void createWidgets();
    void setGui();
    void fillWidgetsInformation();
    void addToLayout();
    void startUpdateTimer();
    QString boolToQString(bool);

private slots:
};

#endif // QInformationTabWidget_H
