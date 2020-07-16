#ifndef GRAPHICSPRINTERTEMPLATE_H
#define GRAPHICSPRINTERTEMPLATE_H

#include <QWidget>
#include <QDate>
#include <QtCharts>
#include "../qsaleschartview.h"

namespace GraphicsPrinter {

struct GraphicsPrinterInformation
{
    QDate startDate;
    QDate endDate;
    qint64 inteval;

    QString title;
    QString asixYTitle;
};

class GraphicsPrinterTemplate : public QWidget
{
    Q_OBJECT
public:
    virtual ~GraphicsPrinterTemplate();
    GraphicsPrinterTemplate(QWidget *parent = nullptr);

    void Print(const GraphicsPrinterInformation &information,
               QSalesChartView *chartView);

protected:
    virtual QVector<QVariant> getFirstVector() = 0;
    virtual QBarSet* getBarSet(QVariant&) = 0;
    virtual void querySecondVectorFromServer(QDate startDate, QDate endDate) = 0;
    virtual QVector<QVariant> getSecondVector(QVariant &, QDate startDate, QDate endDate) = 0;
    virtual void processing(double *result, QVariant&, QDate date) = 0;

    template< typename T >
    T unpack( const QVariant& var, const T& defVal = T() ) {
        if( var.isValid() && var.canConvert< T >() ) {
            return var.value< T >();
        }
        return defVal;
    }

private:
    GraphicsPrinterInformation information;
    QSalesChartView *chartView = nullptr;
    void removeEmptyChart(QBarSeries *);

protected slots:
    void dataReceived();

};

}

#endif // GRAPHICSPRINTERTEMPLATE_H
