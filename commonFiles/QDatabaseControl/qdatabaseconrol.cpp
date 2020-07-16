#include "qdatabaseconrol.h"

QDatabaseConrol::QDatabaseConrol(QSqlDatabase *database, QObject *parent)
    : QObject(parent)
{
    pointSale = new DatabaseCommands::QPointSaleCommands(database, this);
    category = new DatabaseCommands::QSalesCategoryCommands(database, this);
    user = new DatabaseCommands::QUserCommands(database, this);
    type = new DatabaseCommands::QPaymentTypeCommands(database, this);
    volume = new DatabaseCommands::QVolumeProductCommands(database, this);
    product = new DatabaseCommands::QProductCommands(database, this);
    price = new DatabaseCommands::QPriceCommands(database, this);
    receipt = new DatabaseCommands::QReceiptCommands(database, this);
    soldPosition = new DatabaseCommands::QSoldPositionCommands(database, this);
    shift = new DatabaseCommands::QShiftCommands(database, this);
    picture = new DatabaseCommands::QProductPictureCommands(database, this);
}

QDatabaseConrol::~QDatabaseConrol()
{

}

void QDatabaseConrol::setPictureDatabase(QSqlDatabase *database)
{
    delete picture;
    picture = new DatabaseCommands::QProductPictureCommands(database, this);
}
