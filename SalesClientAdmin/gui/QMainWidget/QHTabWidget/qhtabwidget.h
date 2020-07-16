#ifndef QHTABWIDGET_H
#define QHTABWIDGET_H

#include <QTabWidget>
#include <QPaintEvent>
#include <QDebug>
#include "QHTabBar/qhtabbar.h"

class QHTabWidget : public QTabWidget
{
public:
    explicit QHTabWidget(QWidget *parent = nullptr);
    ~QHTabWidget();

    int insertTab(int index, QWidget *widget, const QIcon &icon, const QString &label);

private:
    QHTabBar *tabBar = nullptr;
    void paintEvent(QPaintEvent *event);
};

#endif // QHTABWIDGET_H
