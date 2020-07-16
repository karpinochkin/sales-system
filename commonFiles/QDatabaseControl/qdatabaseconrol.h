#ifndef QDATABASECONROL_H
#define QDATABASECONROL_H

#include <QObject>
#include <QSqlDatabase>
#include "DatabaseCommands/QProductPictureCommands/qproductpicturecommands.h"
#include "DatabaseCommands/QPointSaleCommands/qpointsalecommands.h"
#include "DatabaseCommands/QUserCommands/qusercommands.h"
#include "DatabaseCommands/QSalesCategoryCommands/qsalescategorycommands.h"
#include "DatabaseCommands/QPaymentTypeCommands/qpaymenttypecommands.h"
#include "DatabaseCommands/QVolumeProductCommands/qvolumeproductcommands.h"
#include "DatabaseCommands/QProductCommands/qproductcommands.h"
#include "DatabaseCommands/QPriceCommands/qpricecommands.h"
#include "DatabaseCommands/QReceiptCommands/qreceiptcommands.h"
#include "DatabaseCommands/QSoldPositionCommands/qsoldpositioncommands.h"
#include "DatabaseCommands/QShiftCommands/qshiftcommands.h"

class QDatabaseConrol : public QObject
{
    Q_OBJECT
public:
    explicit QDatabaseConrol(QSqlDatabase *database, QObject *parent = nullptr);
    ~QDatabaseConrol();

    DatabaseCommands::QPointSaleCommands *pointSale = nullptr;
    DatabaseCommands::QSalesCategoryCommands *category = nullptr;
    DatabaseCommands::QUserCommands *user = nullptr;
    DatabaseCommands::QPaymentTypeCommands *type = nullptr;
    DatabaseCommands::QVolumeProductCommands *volume = nullptr;
    DatabaseCommands::QProductCommands *product = nullptr;
    DatabaseCommands::QProductPictureCommands *picture = nullptr;
    DatabaseCommands::QPriceCommands *price = nullptr;
    DatabaseCommands::QReceiptCommands *receipt = nullptr;
    DatabaseCommands::QShiftCommands *shift = nullptr;
    DatabaseCommands::QSoldPositionCommands *soldPosition = nullptr;

    void setPictureDatabase(QSqlDatabase *database);

};

#endif // QDATABASECONROL_H
