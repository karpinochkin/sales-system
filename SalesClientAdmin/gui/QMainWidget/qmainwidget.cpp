#include "qmainwidget.h"
#include <QDebug>

using namespace Gui;

QMainWidget::QMainWidget(QSettings *settings, QNetManager *networkManager, QWidget *parent)
    : QWidget(parent),
      settings(settings),
      networkManager(networkManager)
{
    setWindowIcon(QIcon(":/images/icons/other/iconA.png"));
    loadSettings();
    setGui();
}
QMainWidget::~QMainWidget()
{
    qDebug() << "~QMainWidget()";
}

void QMainWidget::setGui()
{
    this->setMinimumSize(640,480);
    mainLayout = new QVBoxLayout(this);
    mainLayout->setMargin(0);

    tabWidget = new QHTabWidget(this);
    tabWidget->setTabPosition(QHTabWidget :: West);
    tabWidget->setIconSize(QSize(48, 48));
    mainLayout->addWidget(tabWidget);

    statisticsWidget = new QStatisticsTabWidget(settings, networkManager, this);
    databaseWidget = new QDatabaseTabsWidget(networkManager, this);
    infoWidget = new QInformationTabWidget(networkManager, this);

    tabWidget->addTab(databaseWidget, QIcon(":/images/icons/mainTabs/Database.png"),
                      tr("База данных"));
    tabWidget->addTab(statisticsWidget, QIcon(":/images/icons/mainTabs/Statistic.png"),
                      tr("Статистика"));
    tabWidget->addTab(infoWidget, QIcon(":/images/icons/mainTabs/info.png"),
                      tr("Информация"));
}

void QMainWidget::loadSettings()
{
    int width= settings->value("/MainForm/FormWidth").toInt();
    int height= settings->value("/MainForm/FormHeight").toInt();
    if ((width > 0) && (height > 0))
    {
        this->resize(width, height);
    }

    int X = settings->value("/MainForm/FormX").toInt();
    int Y = settings->value("/MainForm/Formy").toInt();

    if ((X > 0) && (Y > 0))
    {
        QPoint center = QPoint(X, Y);
        this->move(center);
    }
}

void QMainWidget::saveSettings()
{
    if ((!this->isMaximized())
            && (this->width() > 0)
            && (this->height() > 0)
            && (this->x() > 0)
            && (this->y() > 0))
    {
        settings->setValue("/MainForm/FormWidth",this->width());
        settings->setValue("/MainForm/FormHeight",this->height());
        settings->setValue("/MainForm/FormX",this->x());
        settings->setValue("/MainForm/Formy",this->y());
    }
}

void QMainWidget::closeEvent (QCloseEvent *event)
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this,
                                  tr("Выход"),
                                  tr("Вы уверены что хотите закрыть программу?"),
                                  QMessageBox::Yes|QMessageBox::No);

    if (reply == QMessageBox::Yes)
    {
        emit signalCloseProgram();
        networkManager->Disconnect();
        this->saveSettings();
       event->accept();
    } else event->ignore();
}
