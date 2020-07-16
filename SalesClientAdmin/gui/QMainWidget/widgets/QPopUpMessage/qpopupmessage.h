#ifndef QPOPUPMESSAGE_H
#define QPOPUPMESSAGE_H

#include <QWidget>
#include <QtCharts/QChartGlobal>
#include <QtWidgets/QGraphicsItem>
#include <QtGui/QFont>
#include <QtCharts>

class QPopUpMessage : public QGraphicsItem
{
public:
    QPopUpMessage(QChart *parent = nullptr);

    void setText(const QString &text);
    void setAnchor(QPointF point);
    void updateGeometry();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

private:
    QString m_text;
    QRectF m_textRect;
    QRectF m_rect;
    QPointF m_anchor;
    QFont m_font;
    QChart *m_chart = nullptr;
};

#endif // QPOPUPMESSAGE_H
