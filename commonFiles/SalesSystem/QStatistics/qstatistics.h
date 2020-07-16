#ifndef QSTATISTICS_H
#define QSTATISTICS_H

#include <QObject>
#include <QDateTime>
#include <QDataStream>
#include "../QSalesObjects/qsalesobjects.h"

class QStatistics;

enum StatisticsType {
    NoneType = 0,
    NumberSoldProductsForPointSale = 1,
    NumberSoldProduct = 2,
    CountForUser = 3,
    CountForUsers = 4,
    MoneyUsers = 5,
    Money = 6
};

enum StatisticsStep {
    NoneStep,
    Hour,
    Day,
    Week,
    Month,
    Year
};

class StatisticsInput {
public:
    StatisticsInput() = default;
    ~StatisticsInput() = default;

    QDateTime startDate;
    QDateTime endDate;
    StatisticsType type;
    StatisticsStep step;
    int stepValue;
    int id = -1;

    void operator <<(QDataStream &stream);
    void operator >>(QDataStream &stream);
    void clear();
};

struct StatisticsOutput {
    QVector<QStatistics> statistics;
    unsigned long maxValue = 0;
};

class QStatistics : public QSalesObjects
{
public:
    QStatistics() = default;
    ~QStatistics() = default;

    void operator <<(QDataStream &stream);
    void operator >>(QDataStream &stream);

    QDateTime periodDateTime;
//    QMap<QString, double> periodResult;
    QPair<QString, double> periodResult;
    QString periodText;

    void clear();
    QString toString();

private:
};

Q_DECLARE_METATYPE( QStatistics )
#endif // QSTATISTICS_H
