#include "qstatistics.h"

void QStatistics::operator <<(QDataStream &stream)
{
    clear();
    stream >> periodText;
    stream >> periodDateTime;
    stream >> periodResult;
}

void QStatistics::operator >>(QDataStream &stream)
{
    stream << periodText;
    stream << periodDateTime;
    stream << periodResult;
}

void QStatistics::clear()
{
    periodText.clear();
    periodDateTime.setTime_t(0);
    periodResult.first = "";
    periodResult.second = 0;
//    periodResult.clear();
}

QString QStatistics::toString()
{
    QString output ="Datetime : " + periodDateTime.toString()
            + "legend text : " + periodText
            + "; ";
    output.append(periodResult.first + " : " + QString::number(periodResult.second));
//    for (auto key : periodResult.keys()) {
//        output.append(key + " : " + QString::number(static_cast<double>(periodResult[key])) + "; ");
//    }
    return output;
}

void StatisticsInput::operator <<(QDataStream &stream)
{
    clear();
    stream >> startDate;
    stream >> endDate;
    qint32 type_;
    stream >> type_;
    type = static_cast<StatisticsType>(type_);
    qint32 step_;
    stream >> step_;
    step = static_cast<StatisticsStep>(step_);
    stream >> stepValue;
    stream >> id;
}

void StatisticsInput::operator >>(QDataStream &stream)
{
    stream << startDate;
    stream << endDate;
    stream << static_cast<qint32>(type);
    stream << static_cast<qint32>(step);
    stream << stepValue;
    stream << id;
}

void StatisticsInput::clear()
{
    startDate.setTime_t(0);
    endDate.setTime_t(0);
    type = StatisticsType::NoneType;
    step = StatisticsStep::NoneStep;
    stepValue = -1;
    id = -1;
}
