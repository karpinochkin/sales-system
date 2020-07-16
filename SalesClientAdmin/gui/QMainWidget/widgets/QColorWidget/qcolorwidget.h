#ifndef QCOLORWIDGET_H
#define QCOLORWIDGET_H

#include <QWidget>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QPainter>
#include <QDebug>
#include <QColorDialog>
#include <QVBoxLayout>
#include <QLabel>

namespace SalesWidgets {

class QColorWidget : public QWidget
{
public:
    explicit QColorWidget(QWidget *parent = nullptr);
    explicit QColorWidget(QColor color, QWidget *parent = nullptr);
    ~QColorWidget() = default;

    void setColor(QColor);
    QColor getColor();

    bool colorWasChanged();
protected:
    virtual void paintEvent(QPaintEvent*);
    virtual void mouseReleaseEvent(QMouseEvent*);

private:
    QColor currentColor;
    QVBoxLayout *mainLayout = nullptr;
    bool _colorWasChanged;

    void setGui();
};

}

#endif // QCOLORWIDGET_H
