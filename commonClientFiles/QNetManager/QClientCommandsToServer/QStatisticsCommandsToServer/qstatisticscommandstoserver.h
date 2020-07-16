#ifndef QSTATISTICSCOMMANDSTOSERVER_H
#define QSTATISTICSCOMMANDSTOSERVER_H

#include "../QParentCommandsToServer/qparentcommandstoserver.h"
#include "../commonFiles/SalesSystem/QStatistics/qstatistics.h"

class QStatisticsCommandsToServer : public CommandsToServer::QParentCommandsToServer
{
    Q_OBJECT
public:
    explicit QStatisticsCommandsToServer(QObject *parent = nullptr);
    ~QStatisticsCommandsToServer() override = default;

    void load(StatisticsInput &);
};

#endif // QSTATISTICSCOMMANDSTOSERVER_H
