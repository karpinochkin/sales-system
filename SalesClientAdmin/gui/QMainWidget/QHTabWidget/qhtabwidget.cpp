#include "qhtabwidget.h"

QHTabWidget::QHTabWidget(QWidget *parent) : QTabWidget(parent)
{
    tabBar = new QHTabBar(this);
    this->setTabBar(tabBar);
}

QHTabWidget::~QHTabWidget()
{

}

void QHTabWidget::paintEvent(QPaintEvent *event)
{
    QTabWidget::paintEvent(event);
}

int QHTabWidget::insertTab(int index, QWidget *widget, const QIcon &icon, const QString &label)
{
    int output = QTabWidget::insertTab(index, widget, icon, label);
    return output;
}


