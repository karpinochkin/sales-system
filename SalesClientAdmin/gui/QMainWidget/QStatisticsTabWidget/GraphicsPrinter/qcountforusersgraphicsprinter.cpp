#include "qcountforusersgraphicsprinter.h"

using namespace GraphicsPrinter;

QCountForUsersGraphicsPrinter::QCountForUsersGraphicsPrinter(QNetManager *manager,
                                                             QWidget *parent):
    GraphicsPrinterTemplate(parent),
    netManager(manager)
{
    connect(netManager, &QNetManager::signalSoldPositionsLoaded,
            this, &QCountForUsersGraphicsPrinter::dataReceived);
}

QVector<QVariant> QCountForUsersGraphicsPrinter::getFirstVector()
{
    QVector<QUser> users = netManager->DatabaseCommands()
            ->user->getUsers();

    QVector<QVariant> output;
    for(auto user : users) {
        output.push_back(QVariant::fromValue(user));
    }
    return output;
}

QBarSet *QCountForUsersGraphicsPrinter::getBarSet(QVariant &val)
{
    return new QBarSet(unpack<QUser>(val).surname, this);
}

void QCountForUsersGraphicsPrinter::querySecondVectorFromServer(QDate startDate, QDate endDate)
{
    netManager->CommandsToServer()->soldPosition->load(startDate, endDate.addDays(1));
}

QVector<QVariant> QCountForUsersGraphicsPrinter::getSecondVector(QVariant &val,
                                                                 QDate startDate,
                                                                 QDate endDate)
{
    QUser user = unpack<QUser>(val);
    QVector<QSoldPosition> soldPositions = netManager->DatabaseCommands()
            ->soldPosition->getSoldPositionsForUser(user.id, startDate, endDate);

    QVector<QVariant> output;
    for (auto soldPosition : soldPositions) {
        output.push_back(QVariant::fromValue(soldPosition));
    }
    return output;
}

void QCountForUsersGraphicsPrinter::processing(double *result,
                                               QVariant &val,
                                               QDate date)
{
    QSoldPosition soldPosition = unpack<QSoldPosition>(val);
    if (soldPosition.date.date() == date) {
        *result += soldPosition.count;
    }
}
