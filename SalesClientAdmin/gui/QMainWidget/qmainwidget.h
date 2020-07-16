#ifndef QMAINWIDGET_H
#define QMAINWIDGET_H

#include <QWidget>
#include <QCloseEvent>
#include <QMessageBox>
#include <QVBoxLayout>

#include "../commonClientFiles/QNetManager/qnetmanager.h"
#include "QHTabWidget/qhtabwidget.h"
#include "QDatabaseTabWidget/qdatabasetabwidget.h"
#include "QStatisticsTabWidget/qstatisticstabwidget.h"
#include "QInformationTabWidget/qinformationtabwidget.h"

using namespace Gui::DatabaseTabs;

namespace Gui {

class QMainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit QMainWidget(QWidget *parent = nullptr) = delete;
    explicit QMainWidget(QSettings *settings,
                         QNetManager *networkManager,
                         QWidget *parent = nullptr);
    ~QMainWidget();

private:
    QSettings *settings = nullptr;
    QNetManager *networkManager = nullptr;

    QVBoxLayout *mainLayout = nullptr;
    QHTabWidget *tabWidget = nullptr;
    QDatabaseTabsWidget *databaseWidget = nullptr;
    QStatisticsTabWidget *statisticsWidget = nullptr;
    QInformationTabWidget *infoWidget = nullptr;

    void loadSettings();
    void saveSettings();
    void setGui();
    void closeEvent (QCloseEvent *event);

signals:
    void signalCloseProgram();
};

}

#endif // QMAINWIDGET_H
