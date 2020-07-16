#include "qgraphicsprinter.h"

QGraphicsPrinter::QGraphicsPrinter(QObject *parent)
    : QObject(parent)
{

}

void QGraphicsPrinter::Print(const QVector<QStatistics> &statistics, double maxValue, QString title, QString asixYTitle, QSalesChartView *chartView)
{
    QBarSeries *series = new QBarSeries(this);

    QVector<QBarSet*> sets;
    for (auto stat : statistics) {
        if (sets.isEmpty()) {
            QBarSet *set = new QBarSet(stat.periodResult.first);
            connect(set, &QBarSet::clicked, chartView, &QSalesChartView::slotBarClicked);
            *set << stat.periodResult.second;
            sets.push_back(set);
            series->append(set);
        }
        else {
            int index = find(sets, stat.periodResult.first);
            if (index >= 0) {
                *(sets[index]) << stat.periodResult.second;
                series->append(sets[index]);
            }
            else {
                QBarSet *set = new QBarSet(stat.periodResult.first);
                connect(set, &QBarSet::clicked, chartView, &QSalesChartView::slotBarClicked);
                *set << stat.periodResult.second;
                sets.push_back(set);
                series->append(set);
            }
        }
    }
    removeEmptyChart(series);
    QChart *chart = new QChart;
    chart->addSeries(series);

    chart->setTitle(title);
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QStringList dates;
    for (auto stat : statistics) {
        dates.push_back(stat.periodText);
    }
    QBarCategoryAxis *axisX = new QBarCategoryAxis(series);

    axisX->append(dates);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis(series);
    axisY->setTitleText(asixYTitle);
    axisY->setRange(0, maxValue + 5);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    chartView->updateChart(chart);
}

void QGraphicsPrinter::removeEmptyChart(QBarSeries* series)
{
    auto sets = series->barSets();

    for (auto val : sets) {
        if (val->sum() == 0.0) {
            series->remove(val);
        }
    }
}

int QGraphicsPrinter::find(const QVector<QBarSet*>& sets, QString key)
{
    int index = -1;
    for (int i = 0; i < sets.length(); i++) {
        if (sets.at(i)->label() == key) {
            index = i;
            break;
        }
    }
    return index;
}
