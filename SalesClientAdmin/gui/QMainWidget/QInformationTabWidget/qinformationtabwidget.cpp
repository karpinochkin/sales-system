#include "qinformationtabwidget.h"

QInformationTabWidget::QInformationTabWidget(QNetManager *netManager,
                                       QWidget *parent)
    : QWidget(parent),
      networkManager(netManager)
{
    this->createWidgets();
    this->setGui();
    this->startUpdateTimer();
    this->fillWidgetsInformation();
    this->addToLayout();
}

QInformationTabWidget::~QInformationTabWidget()
{

}

void QInformationTabWidget::createWidgets()
{
    mainLayout = new QVBoxLayout(this);

    statusGroupBox = new QGroupBox(this);
    mainGroupBox = new QGroupBox(this);
    mainGroupBoxLayout = new QVBoxLayout;
    statusLayout = new QGridLayout;
    statusConnectLabel = new QLabel(tr("Статус: "), this);
    statusConnectEdit = new QLineEdit(this);
    statusHostLabel = new QLabel(tr("Хост: "), this);
    statusHostEdit = new QLineEdit(this);
    statusPortLabel = new QLabel(tr("Порт:"), this);
    statusPortEdit = new QLineEdit(this);

    userGroupBox = new QGroupBox(this);
    userLayout = new QGridLayout;
    userLoginEdit = new QLineEdit(this);
    userLoginLabel = new QLabel(tr("Логин: "), this);
    userSurnameEdit = new QLineEdit(this);
    userNameEdit = new QLineEdit(this);
    userSurnameLabel = new QLabel(tr("Фамилия: "), this);
    userNameLabel = new QLabel(tr("Имя: "), this);
    userPatronymicEdit = new QLineEdit(this);
    userPatronymicLabel = new QLabel(tr("Отчество: "), this);
}

void QInformationTabWidget::setGui()
{
    mainLayout->setAlignment(Qt::AlignTop);

    mainGroupBoxLayout->setAlignment(Qt::AlignTop);
    statusLayout->setAlignment(Qt::AlignTop);
    statusConnectEdit->setEnabled(false);
    statusHostEdit->setEnabled(false);
    statusPortEdit->setEnabled(false);

    userLayout->setAlignment(Qt::AlignTop);
    userLoginEdit->setEnabled(false);
    userSurnameEdit->setEnabled(false);
    userNameEdit->setEnabled(false);
    userPatronymicEdit->setEnabled(false);
}

void QInformationTabWidget::fillWidgetsInformation()
{
    mainGroupBox->setTitle(tr("Информация"));
    statusGroupBox->setTitle(tr("Сервер"));
    statusHostEdit->setText(networkManager->host());
    statusPortEdit->setText(QString::number(networkManager->port()));

    userGroupBox->setTitle(tr("Пользователь"));

    QUser user = networkManager->getCurrentUser();
    userLoginEdit->setText(user.login);
    userNameEdit->setText(user.name);
    userSurnameEdit->setText(user.surname);
    userPatronymicEdit->setText(user.patronymic);
}

void QInformationTabWidget::addToLayout()
{
    mainLayout->addWidget(mainGroupBox);
    mainGroupBox->setLayout(mainGroupBoxLayout);
    mainGroupBoxLayout->addWidget(statusGroupBox);

    statusGroupBox->setLayout(statusLayout);
    statusLayout->addWidget(statusConnectLabel, 0, 0, 1, 1);
    statusLayout->addWidget(statusConnectEdit, 0, 1, 1, 1);
    statusLayout->addWidget(statusHostLabel, 1, 0, 1, 1);
    statusLayout->addWidget(statusHostEdit, 1, 1, 1, 1);
    statusLayout->addWidget(statusPortLabel, 2, 0, 1, 1);
    statusLayout->addWidget(statusPortEdit, 2, 1, 1, 1);

    mainGroupBoxLayout->addWidget(userGroupBox);
    userGroupBox->setLayout(userLayout);
    userLayout->addWidget(userLoginLabel, 0, 0, 1, 1);
    userLayout->addWidget(userLoginEdit, 0, 1, 1, 1);
    userLayout->addWidget(userNameLabel, 1, 0, 1, 1);
    userLayout->addWidget(userNameEdit, 1, 1, 1, 1);
    userLayout->addWidget(userSurnameLabel, 2, 0, 1, 1);
    userLayout->addWidget(userSurnameEdit, 2, 1, 1, 1);
    userLayout->addWidget(userPatronymicLabel, 3, 0, 1, 1);
    userLayout->addWidget(userPatronymicEdit, 3, 1, 1, 1);
}

void QInformationTabWidget::startUpdateTimer()
{
    update = new QTimer(this);

    connect(update, &QTimer::timeout,
            this, [=](){
        QString result = boolToQString(networkManager->isAuthorized());
        statusConnectEdit->setText(result);
    });

    update->start(1000);
}

QString QInformationTabWidget::boolToQString(bool val)
{
    if (val) {
        return tr("Подключен");
    }
    return tr("Не подключен");
}
