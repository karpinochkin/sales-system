#include "qcolorwidget.h"

using namespace SalesWidgets;

QColorWidget::QColorWidget(QWidget *parent)
    : QWidget(parent),
      currentColor(QColor(0, 0, 0)),
      _colorWasChanged(false)
{
    mainLayout = new QVBoxLayout(this);
    this->setLayout(mainLayout);

    this->setGui();
    this->setCursor(Qt::PointingHandCursor);
    this->setMinimumSize(70,20);
    this->setMaximumSize(70,20);
}

QColorWidget::QColorWidget(QColor color,QWidget *parent)
    : QWidget(parent),
      currentColor(color),
      _colorWasChanged(false)
{
    this->setGui();
    this->setCursor(Qt::PointingHandCursor);
    this->setMinimumSize(70,20);
    this->setMaximumSize(70,20);
}

void QColorWidget::setColor(QColor color)
{
    currentColor = color;
}

QColor QColorWidget::getColor()
{
    return currentColor;
}

bool QColorWidget::colorWasChanged()
{
    return _colorWasChanged;
}

void QColorWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setBrush(QBrush(currentColor));
    painter.drawRect(0, 0, width(), height());
}

void QColorWidget::mouseReleaseEvent(QMouseEvent *)
{
    QColor col = QColorDialog::getColor(currentColor,this,tr("Color Dialog"));
    if (col.isValid())
    {
        currentColor = col;
        _colorWasChanged = true;

        this->repaint();
    }
}

void QColorWidget::setGui()
{
}

