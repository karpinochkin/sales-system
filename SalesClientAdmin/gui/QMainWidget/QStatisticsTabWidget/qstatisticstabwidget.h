#ifndef QSTATISTICSTABWIDGET_H
#define QSTATISTICSTABWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QtCharts>
#include <QSettings>
#include "../commonClientFiles/QNetManager/qnetmanager.h"
#include "../widgets/QSalesComboBox/qsalescombobox.h"
#include "../widgets/QSalesCalendarInterval/qsalescalendarinterval.h"
#include "GraphicsPrinter/qcountforpointsalegraphicsprinter.h"
#include "GraphicsPrinter/qcountforproductgraphicsprinter.h"
#include "GraphicsPrinter/qmoneygraphicsprinter.h"
#include "GraphicsPrinter/qcountforusergraphicsprinter.h"
#include "GraphicsPrinter/qcountforusersgraphicsprinter.h"
#include "GraphicsPrinter/qmoneyforusersgraphicsprinter.h"
#include "qstatisticschoicedialog.h"
#include "GraphicsPrinter/qgraphicsprinter.h"
#include "qsaleschartview.h"
#include "../widgets/QStepperComboBox/qsteppercombobox.h"

using namespace SalesWidgets;

class QStatisticsTabWidget : public QWidget
{
    Q_OBJECT
public:
    explicit QStatisticsTabWidget(QSettings *settings, QNetManager *netManager, QWidget *parent = nullptr);
    ~QStatisticsTabWidget();

private:
    QNetManager *networkManager = nullptr;

    QVBoxLayout *mainLayout = nullptr;
    QSalesChartView *chartView = nullptr;
    QSalesCalendarInterval *calendarWidget = nullptr;
    SalesComboBox::QSalesComboBox *graphComboBox = nullptr;
    QHBoxLayout *boxLayout = nullptr;
    QStepperComboBox *stepperComboBox = nullptr;
    QSettings *settings =nullptr;
    bool isNotFirstStart = true;

    const QString m_moneyStatistics;
    const QString m_numberSoldProductsForPointSale;
    const QString m_numberSoldProduct;
    const QString m_moneyStatisticsForUsers;
    QString graphTitle = "";
    QString graphAsixYTitle = "";
    QStringList comboBoxItems;

    void createWidgets();
    void fillChartList();
    void fillStepperComboBox();
    void refillStepperComboBox();
    void setGui();
    void connects();
    void addToLayout();
    void loadSettings();
    void saveSettings();
    void helpMessageBox();

//    void getHourInnerStepperBox(StepperComboBox::In *inner, qint64 interval);

    int getSelectedPointSaleId();
    int getSelectedProductId();
    int getSelectedUserId();

private slots:
    void getStatistics();
    void printStatistics(const QVector<QStatistics>&, double maxValue);
};

#endif // QSTATISTICSTABWIDGET_H
