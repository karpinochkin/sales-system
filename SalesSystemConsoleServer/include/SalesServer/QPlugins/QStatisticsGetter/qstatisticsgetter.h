#ifndef QSTATISTICSGETTER_H
#define QSTATISTICSGETTER_H

#include "statisticshandlers.h"

namespace Plugins {

using namespace Statistics;

class QStatisticsGetter
{
public:
    QStatisticsGetter(QDatabaseConrol *db, const StatisticsInput& info);
    ~QStatisticsGetter();

    QVector<QStatistics> get();
    double getMaxValue();

private:
    QDatabaseConrol *db = nullptr;
    QVector<QStatistics> statistics;
    StatisticsInput getterInfo;
    unsigned long maxValue = 0;

    void selectCorrectStat();
    void moneyStat();
    void countForUserStat();
    void countForUsersStat();
    void moneyUsersStat();
    void numberSoldProductStat();
    void numberSoldProductsForPointSale();

    double proccesing(double result, const QReceipt &receipt, QDateTime receiptDateTime, QDateTime desiredData);
    void updateResult(double *result, const QReceipt &receipt);
};

}


#endif // QSTATISTICSGETTER_H
