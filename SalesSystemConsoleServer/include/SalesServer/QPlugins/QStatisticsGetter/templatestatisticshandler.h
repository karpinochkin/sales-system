#ifndef TEMPLATESTATISTICSHANDLER_H
#define TEMPLATESTATISTICSHANDLER_H


#include "../commonFiles/QDatabaseControl/qdatabaseconrol.h"
#include "../commonFiles/SalesSystem/QStatistics/qstatistics.h"

namespace Statistics {

class QTemplateStatisticsHandler
{
public:
    virtual ~QTemplateStatisticsHandler() = default;
    StatisticsOutput get(StatisticsInput info);

protected:
    QTemplateStatisticsHandler() =  default;
    virtual void hook(const StatisticsInput &info);
    virtual QVector<QVariant> getFirstVector() = 0;
    virtual QString getKey(QVariant&) = 0;
    virtual QVector<QVariant> getSecondVector(QVariant &,
                                              QDateTime startDate,
                                              QDateTime endDate) = 0;
    virtual QDateTime getItemDateTime(QVariant &item) = 0;
    virtual bool checkHook(QVariant &item);
    virtual void updateResult(double* result,
                              QVariant &item) = 0;

    template< typename T >
    T unpack( const QVariant& var, const T& defVal = T() ) {
        if( var.isValid() && var.canConvert< T >() ) {
            return var.value< T >();
        }
        return defVal;
    }
private:
    QDateTime startDate(StatisticsInput &info) const;
    QDateTime endDate(StatisticsInput &info) const;
    double getResult(const StatisticsInput &info,
                     const QVector<QVariant> &vector,
                     const QDateTime currentDateTime);
    double proccesing(const StatisticsInput&,
                      double result,
                      QVariant &value,
                      QDateTime receiptDateTime,
                      QDateTime desiredData);
    bool isDateInRange(const StatisticsInput&,
                   QDateTime firstDate,
                   QDateTime secondDate);
    void fillOutput(StatisticsOutput& output,
                    const StatisticsInput& info,
                    double result,
                    const QString &key,
                    QDateTime periodDateTime);
    QString periodText(const StatisticsInput& info,
                       QDateTime startPeriodDatetime);
    void stepper(const StatisticsInput& info,
                 QDateTime &dateTime);
    void setTimeForHourTypeStep(StatisticsInput &info);

    /// Returns the current dateTime incremented by the desired step.
    QDateTime hoursStep(const StatisticsInput& info,
                        QDateTime currentDateTime);
    QDateTime daysStep(const StatisticsInput& info,
                       QDateTime currentDateTime);
    QDateTime weeksStep(const StatisticsInput& info,
                        QDateTime currentDateTime);
    QDateTime monthsStep(const StatisticsInput& info,
                         QDateTime currentDateTime);
    QDateTime yearsStep(const StatisticsInput& info,
                        QDateTime currentDateTime);
};

}
#endif // TEMPLATESTATISTICSHANDLER_H
