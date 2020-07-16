#include "templatestatisticshandler.h"

using namespace Statistics;

StatisticsOutput QTemplateStatisticsHandler::get(StatisticsInput info)
{
    StatisticsOutput output;
    setTimeForHourTypeStep(info);

    hook(info);
    QVector<QVariant> firstVector = getFirstVector();
    for (auto item : firstVector) {
        QDateTime currentDateTime = startDate(info);
        QString key = getKey(item);

        QVector<QVariant> secondVector = getSecondVector(
                    item, startDate(info), endDate(info).addDays(1)
                    );

        while (isDateInRange(info, currentDateTime, endDate(info))) {
            double result = getResult(info, secondVector, currentDateTime);

            fillOutput(output, info, result, key, currentDateTime);
            stepper(info, currentDateTime);
        }
    }
    return output;
}

void QTemplateStatisticsHandler::hook(const StatisticsInput &info)
{
    Q_UNUSED(info)
}

void QTemplateStatisticsHandler::setTimeForHourTypeStep(StatisticsInput &info)
{
    if (info.step == StatisticsStep::Hour) {
        if (info.endDate.time() == QTime(0,0)) {
            info.endDate.setTime(QTime(23, 59));
        }
    }
}

QDateTime QTemplateStatisticsHandler::startDate(StatisticsInput &info) const
{
    return info.startDate;
}

QDateTime QTemplateStatisticsHandler::endDate(StatisticsInput &info) const
{
    return info.endDate;
}

bool QTemplateStatisticsHandler::isDateInRange(const StatisticsInput &info,
                                               QDateTime firstDate,
                                               QDateTime secondDate)
{
    if (info.step == StatisticsStep::Hour) {
        const int hour = 3600;
        return firstDate < secondDate.addSecs(hour);
    }
    return firstDate < secondDate.addDays(1);
}

///If you also need to check the item values;
bool QTemplateStatisticsHandler::checkHook(QVariant &item)
{
    Q_UNUSED(item)
    return true;
}

double QTemplateStatisticsHandler::getResult(const StatisticsInput &info,
                                             const QVector<QVariant> &vector,
                                             const QDateTime currentDateTime)
{
    double result = 0;
    for (auto val : vector) {
        QDateTime itemDateTime = getItemDateTime(val);
        bool ok = checkHook(val);
        if (ok) {
            result = proccesing(info, result, val, itemDateTime, currentDateTime);
        }
    }
    return result;
}

double QTemplateStatisticsHandler::proccesing(const StatisticsInput& info,
                                              double result,
                                              QVariant &value,
                                              QDateTime receiptDateTime,
                                              QDateTime desiredData)
{
    if (info.step == StatisticsStep::Hour) {
        if (receiptDateTime.date() >= desiredData.date() &&
                receiptDateTime.date() <= hoursStep(info, desiredData).date()) {
            if( receiptDateTime >= desiredData &&
                    receiptDateTime <= hoursStep(info, desiredData).addSecs(3600)) {
                updateResult(&result, value);
            }
        }
    }
    else if (info.step == StatisticsStep::Day) {
        if (receiptDateTime.date() >= desiredData.date() &&
                receiptDateTime.date() <= daysStep(info, desiredData).date()) {
            updateResult(&result, value);
        }
    }
    else if (info.step == StatisticsStep::Week) {
        if (receiptDateTime.date() >= desiredData.date() &&
                receiptDateTime.date() <= weeksStep(info, desiredData).date()) {
            updateResult(&result, value);
        }
    }
    else if(info.step == StatisticsStep::Month) {
        if (receiptDateTime.date() >= desiredData.date() &&
                receiptDateTime.date() <= monthsStep(info, desiredData).date()) {
            updateResult(&result, value);
        }

    }
    else if (info.step == StatisticsStep::Year) {
        if (receiptDateTime.date() >= desiredData.date() &&
                receiptDateTime.date() <= yearsStep(info, desiredData).date()) {
            updateResult(&result, value);
        }
    }

    return result;
}

QDateTime QTemplateStatisticsHandler::hoursStep(const StatisticsInput& info, QDateTime currentDateTime)
{
    const int dayMultiplier = 3600;

    if (currentDateTime.addSecs(static_cast<qint64>(info.stepValue * dayMultiplier - dayMultiplier)) < info.endDate) {
        return currentDateTime.addSecs(static_cast<qint64>(info.stepValue * dayMultiplier - dayMultiplier));
    }

    qint64 interval = currentDateTime.secsTo(info.endDate);
    if (interval == 0) {
        return currentDateTime.addSecs(static_cast<qint64>(info.stepValue * dayMultiplier - dayMultiplier));
    }
    return currentDateTime.addSecs(interval);
}

QDateTime QTemplateStatisticsHandler::daysStep(const StatisticsInput& info, QDateTime currentDateTime)
{
    return currentDateTime.addDays(static_cast<qint64>(info.stepValue - 1));
}

QDateTime QTemplateStatisticsHandler::weeksStep(const StatisticsInput& info, QDateTime currentDateTime)
{
    const int weekMultiplier = 7;
    return currentDateTime.addDays(static_cast<qint64>(info.stepValue * weekMultiplier - 1));
}

QDateTime QTemplateStatisticsHandler::monthsStep(const StatisticsInput& info, QDateTime currentDateTime)
{
    return currentDateTime.addMonths(info.stepValue);
}

QDateTime QTemplateStatisticsHandler::yearsStep(const StatisticsInput& info, QDateTime currentDateTime)
{
    return currentDateTime.addYears(info.stepValue);
}

void QTemplateStatisticsHandler::fillOutput(StatisticsOutput& output, const StatisticsInput& info, double result, const QString &key, QDateTime periodDateTime)
{
    ///
    if (info.step == StatisticsStep::Hour) {
        if (periodDateTime.date() > info.endDate.date()) {
            return;
        }
    }
    ///

    QStatistics stat;
    if (output.maxValue < result) {
        output.maxValue = static_cast<unsigned long>(result);
    }

    stat.periodResult.first = key;
    stat.periodResult.second = result;
    stat.periodDateTime = periodDateTime;
    stat.periodText = periodText(info, periodDateTime);
    output.statistics.push_back(stat);
}

QString QTemplateStatisticsHandler::periodText(const StatisticsInput& info, QDateTime startPeriodDatetime)
{
    if (info.step == StatisticsStep::Hour) {
        return startPeriodDatetime.toString("dd.MM hh") + " - " + hoursStep(info, startPeriodDatetime).toString("dd.MM hh");
    }
    else if (info.step == StatisticsStep::Day) {
        if (daysStep(info, startPeriodDatetime).date() < info.endDate.date()) {
            return startPeriodDatetime.date().toString("dd.MM") + " - " + daysStep(info, startPeriodDatetime).toString("dd.MM");
        }
        return startPeriodDatetime.date().toString("dd.MM") + " - " + info.endDate.toString("dd.MM");
    }
    else if (info.step == StatisticsStep::Week) {
        if (weeksStep(info, startPeriodDatetime).date() < info.endDate.date()) {
            return startPeriodDatetime.date().toString("dd.MM") + " - " + weeksStep(info, startPeriodDatetime).toString("dd.MM");
        }
        return startPeriodDatetime.date().toString("dd.MM") + " - " + info.endDate.toString("dd.MM");
    }
    else if (info.step == StatisticsStep::Month) {
        if (monthsStep(info, startPeriodDatetime).date() < info.endDate.date()) {
            return startPeriodDatetime.date().toString("dd.MM") + " - " + monthsStep(info, startPeriodDatetime).toString("dd.MM");
        }
        return startPeriodDatetime.date().toString("dd.MM") + " - " + info.endDate.toString("dd.MM");
    }
    else if (info.step == StatisticsStep::Year) {
        if (yearsStep(info, startPeriodDatetime).date() < info.endDate.date()) {
            return startPeriodDatetime.date().toString("dd.MM.yyyy") + " - " + yearsStep(info, startPeriodDatetime).toString("dd.MM.yyyy");
        }
        return startPeriodDatetime.date().toString("dd.MM") + " - " + info.endDate.toString("dd.MM");
    }
    return "";
}


void QTemplateStatisticsHandler::stepper(const StatisticsInput& info, QDateTime &dateTime)
{
    if (info.step == StatisticsStep::Hour) {
        const int hour = 3600;
        dateTime = hoursStep(info, dateTime).addSecs(hour);
    }
    else if (info.step == StatisticsStep::Day) {
        dateTime = daysStep(info, dateTime).addDays(1);
    }
    else if (info.step == StatisticsStep::Week) {
        dateTime = weeksStep(info, dateTime).addDays(1);
    }
    else if (info.step == StatisticsStep::Month) {
        dateTime = monthsStep(info, dateTime).addDays(1);
    }
    else if (info.step == StatisticsStep::Year) {
        dateTime = yearsStep(info, dateTime).addDays(1);
    }
}
