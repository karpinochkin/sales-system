#include "qmoneyforusersgraphicsprinter.h"

using namespace GraphicsPrinter;

QMoneyForUsersGraphicsPrinter::QMoneyForUsersGraphicsPrinter(QNetManager *manager,
                                                             QWidget *parent)
    : GraphicsPrinterTemplate(parent),
      netManager(manager)
{
    connect(netManager, &QNetManager::signalReceiptsLoaded,
            this, &QMoneyForUsersGraphicsPrinter::receiptsLoaded);
    connect(netManager, &QNetManager::signalSoldPositionsLoaded,
            this, &QMoneyForUsersGraphicsPrinter::soldPositionsLoaded);
//    connect(netManager, &QNetManager::signalReceiptsLoaded,
//            this, &QMoneyForUsersGraphicsPrinter::dataReceived);
}

QVector<QVariant> QMoneyForUsersGraphicsPrinter::getFirstVector()
{
    QVector<QUser> users = netManager->DatabaseCommands()
            ->user->getUsers();

    QVector<QVariant> output;
    for(auto user : users) {
        output.push_back(QVariant::fromValue(user));
    }
    return output;
}

QBarSet *QMoneyForUsersGraphicsPrinter::getBarSet(QVariant &val)
{
    return new QBarSet(unpack<QUser>(val).surname, this);
}

void QMoneyForUsersGraphicsPrinter::querySecondVectorFromServer(QDate startDate, QDate endDate)
{
    netManager->CommandsToServer()->receipt->load(startDate, endDate.addDays(1));
    netManager->CommandsToServer()->soldPosition->load(startDate, endDate.addDays(1));
}

QVector<QVariant> QMoneyForUsersGraphicsPrinter::getSecondVector(QVariant &val, QDate startDate, QDate endDate)
{
    QVector<QSoldPosition> s = netManager->DatabaseCommands()->soldPosition->getSoldPositions();
    QUser user = unpack<QUser>(val);
    QVector<QSoldPosition> soldPositions = netManager->DatabaseCommands()
            ->soldPosition->getSoldPositionsForUser(user.id,
                                                    startDate,
                                                    endDate);

    QVector<QVariant> output;
    for (auto soldPosition : soldPositions) {
        output.push_back(QVariant::fromValue(soldPosition));
    }
    return output;
}

void QMoneyForUsersGraphicsPrinter::processing(double *result,
                                               QVariant &val,
                                               QDate date)
{
    QSoldPosition soldPosition = unpack<QSoldPosition>(val);

    QHash<int, QReceipt>::iterator i = receiptsHash.find(soldPosition.idReceipt);
    if ((*i).dateTime.date() == date) {
        *result = (*i).sum;
    }
}

void QMoneyForUsersGraphicsPrinter::received()
{
    ++loadFlag;
    if (loadFlag == 2) {
        this->dataReceived();
    }
}

void QMoneyForUsersGraphicsPrinter::receiptsLoaded()
{
    receiptsHash = netManager->DatabaseCommands()
            ->receipt->getReceiptsHash();
    received();
}

void QMoneyForUsersGraphicsPrinter::soldPositionsLoaded()
{
    received();
}
