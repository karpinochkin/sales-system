#include "graphicsprintertemplate.h"

using namespace GraphicsPrinter;

GraphicsPrinterTemplate::~GraphicsPrinterTemplate()
{
    qDebug() << "~GraphicsPrinterTemplate";
}

GraphicsPrinterTemplate::GraphicsPrinterTemplate(QWidget *parent)
    : QWidget(parent)
{
    qDebug() << "GraphicsPrinterTemplate";
}

void GraphicsPrinterTemplate::Print(const GraphicsPrinterInformation &information,
                                     QSalesChartView *chartView)
{
    this->information = information;
    this->chartView = chartView;
    this->querySecondVectorFromServer(information.startDate, information.endDate);
}

void GraphicsPrinterTemplate::dataReceived()
{
    qDebug() << "received";
    long maxValue = 0;
    QBarSeries *series = new QBarSeries(this);

    QDate startDate =  information.startDate;
    QDate endDate = information.endDate;

    QVector<QVariant> firstVector = getFirstVector();

    for (auto elem : firstVector) {

        QDate date = startDate;

        QBarSet *set = getBarSet(elem);
        connect(set, &QBarSet::clicked, chartView, &QSalesChartView::slotBarClicked);

        QVector<QVariant> objects = getSecondVector(elem, startDate, endDate.addDays(1));

        while (date < endDate.addDays(1)) {
            double result = 0;

            for (auto obj : objects) {
                processing(&result, obj, date);
            }

            if (maxValue < result) {
                maxValue = static_cast<long>(result);
            }

            *set << result;
            series->append(set);
            date = date.addDays(1);
        }
    }

    QChart *chart = new QChart;
    qint64 daysCount = information.inteval;

    removeEmptyChart(series);///

    chart->addSeries(series);

    chart->setTitle(information.title);
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QStringList dates;
    for (int i = 0; i < daysCount + 1; i++) {
        dates.push_back(startDate.addDays(i).toString(Qt::DefaultLocaleShortDate));
    }

    QBarCategoryAxis *axisX = new QBarCategoryAxis(series);

    axisX->append(dates);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis(series);
    axisY->setTitleText(information.asixYTitle);
    axisY->setRange(0, maxValue + 5);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    chartView->updateChart(chart);

    delete this;
}

void GraphicsPrinterTemplate::removeEmptyChart(QBarSeries* series)
{
    auto sets = series->barSets();

    for (auto val : sets) {
        if (val->sum() == 0.0) {
            series->remove(val);
        }
    }
}
