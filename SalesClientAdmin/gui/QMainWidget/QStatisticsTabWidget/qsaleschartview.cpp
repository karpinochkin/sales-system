#include "qsaleschartview.h"

QSalesChartView::QSalesChartView(QWidget *parent)
    : QChartView(parent)
{

}

void QSalesChartView::updateChart(QChart *chart)
{
    QChart *old = nullptr;
    old = this->chart();
    QPopUpMessage *oldToolTip = nullptr;
    oldToolTip = m_tooltip;
    m_tooltip = nullptr;

    this->setChart(chart);

    if (old != nullptr) {
        if (oldToolTip != nullptr) {
            delete oldToolTip;
        }
        old->removeAllSeries();
        delete old;
    }
}

void QSalesChartView::mouseMoveEvent(QMouseEvent *event)
{
    this->localMousePos = event->localPos();
    auto const widgetPos = localMousePos; //event->localPos();
    auto const scenePos = mapToScene(QPoint(static_cast<int>(widgetPos.x()), static_cast<int>(widgetPos.y())));
    auto const chartItemPos = chart()->mapFromScene(scenePos);
    auto const valueGivenSeries = chart()->mapToValue(chartItemPos);
    localMousePos = valueGivenSeries;
    QChartView::mouseMoveEvent(event);
}

void QSalesChartView::slotBarClicked(int index)
{
    auto sets = dynamic_cast<const QBarSeries*>(this->chart()->series().at(0))->barSets();
    QString text = "";

    for (auto val : sets) {
        double res = val->at(index);
        QString name = val->label();

        if (res != 0.0) {
            text.append(name + " : " + QString::number(res) + "\n");
        }
    }

    if (m_tooltip == nullptr)
        m_tooltip = new QPopUpMessage(this->chart());

    m_tooltip->setText(text);
    m_tooltip->setAnchor(localMousePos);
    m_tooltip->setZValue(11);
    m_tooltip->updateGeometry();
    m_tooltip->show();
    text.clear();
}
