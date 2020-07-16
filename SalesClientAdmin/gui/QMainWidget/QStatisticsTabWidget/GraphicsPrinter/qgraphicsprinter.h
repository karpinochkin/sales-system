#ifndef QGRAPHICSPRINTER_H
#define QGRAPHICSPRINTER_H

#include <QObject>
#include "../commonFiles/SalesSystem/QStatistics/qstatistics.h"
#include <QtCharts>
#include "../qsaleschartview.h"

class QGraphicsPrinter : public QObject
{
public:
    explicit QGraphicsPrinter(QObject *parent = nullptr);
    ~QGraphicsPrinter() = default;

    void Print(const QVector<QStatistics> &statistics,
               double maxValue,
               QString title,
               QString asixYTitle,
               QSalesChartView *chartView);
private:
    void removeEmptyChart(QBarSeries *);
    int find(const QVector<QBarSet*>&sets, QString key);
};

#endif // QGRAPHICSPRINTER_H
