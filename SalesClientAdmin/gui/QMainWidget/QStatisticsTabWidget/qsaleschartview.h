#ifndef QSALESCHARTVIEW_H
#define QSALESCHARTVIEW_H

#include <QtCharts>
#include <QChartView>
#include "../widgets/QPopUpMessage/qpopupmessage.h"

class QSalesChartView : public QChartView
{
    Q_OBJECT
public:
    QSalesChartView(QWidget *parent = nullptr);
    ~QSalesChartView() override = default;
    void updateChart(QChart *chart);

protected:
    void mouseMoveEvent(QMouseEvent *event) override;

private:
    QPopUpMessage *m_tooltip = nullptr;
    QPointF localMousePos;

public slots:
    void slotBarClicked(int index);
};

#endif // QSALESCHARTVIEW_H
