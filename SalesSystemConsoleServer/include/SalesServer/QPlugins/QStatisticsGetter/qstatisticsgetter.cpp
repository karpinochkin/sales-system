#include "qstatisticsgetter.h"

using namespace Plugins;
using namespace Statistics;

Plugins::QStatisticsGetter::QStatisticsGetter(QDatabaseConrol *db, const StatisticsInput &info)
    : db(db), getterInfo(info)
{
    this->selectCorrectStat();
}

Plugins::QStatisticsGetter::~QStatisticsGetter()
{

}

QVector<QStatistics> Plugins::QStatisticsGetter::get()
{
    return statistics;
}

double Plugins::QStatisticsGetter::getMaxValue()
{
    return maxValue;
}

void Plugins::QStatisticsGetter::selectCorrectStat()
{
    statistics.clear();
    maxValue = 0;

    if (getterInfo.type == StatisticsType::Money) {
        this->moneyStat();
    }
    else if (getterInfo.type == StatisticsType::CountForUser) {
        this->countForUserStat();
    }
    else if (getterInfo.type == StatisticsType::CountForUsers) {
        this->countForUsersStat();
    }
    else if (getterInfo.type == StatisticsType::MoneyUsers) {
        this->moneyUsersStat();
    }
    else if (getterInfo.type == StatisticsType::NumberSoldProduct) {
        this->numberSoldProductStat();
    }
    else if (getterInfo.type == StatisticsType::NumberSoldProductsForPointSale) {
        this->numberSoldProductsForPointSale();
    }
}

void Plugins::QStatisticsGetter::moneyStat()
{
    qDebug() << "money statistics";
    QMoney moneyGetter(db);
    auto result = moneyGetter.get(getterInfo);
    statistics = result.statistics;
    maxValue = result.maxValue;
}

void Plugins::QStatisticsGetter::countForUserStat()
{

}

void Plugins::QStatisticsGetter::countForUsersStat()
{

}

void Plugins::QStatisticsGetter::moneyUsersStat()
{
    qDebug() << "money user statistics";
    QUsersMoney usersMoneyGetter(db);
    auto result = usersMoneyGetter.get(getterInfo);
    statistics = result.statistics;
    maxValue = result.maxValue;
}

void Plugins::QStatisticsGetter::numberSoldProductStat()
{
    QNumberSoldProduct numberProducts(db, getterInfo.id);
    auto result =numberProducts.get(getterInfo);
    statistics = result.statistics;
    maxValue = result.maxValue;
}

void Plugins::QStatisticsGetter::numberSoldProductsForPointSale()
{
    QNumberSoldProductsForPointSale numberProducts(db, getterInfo.id);
    auto result = numberProducts.get(getterInfo);
    statistics = result.statistics;
    maxValue = result.maxValue;
}


