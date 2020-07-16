QT -= gui
QT += network
QT += sql

CONFIG += c++14 console
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        ../commonFiles/QDataBaseSettings/qdatabasesettings.cpp \
        ../commonFiles/QDatabaseControl/DatabaseCommands/QParentDatabaseCommands/qparentdatabasecommands.cpp \
        ../commonFiles/QDatabaseControl/DatabaseCommands/QPointSaleAndCategoryTableCommands/QPointSaleAndCategoryTableQueries/qpointsaleandcategorytablequeries.cpp \
        ../commonFiles/QDatabaseControl/DatabaseCommands/QPointSaleAndCategoryTableCommands/qpointsaleandcategorytablecommands.cpp \
        ../commonFiles/QDatabaseControl/DatabaseCommands/QPointSaleAndPriceTableCommands/QPointSaleAndPriceQueries/qpointsaleandpricequeries.cpp \
        ../commonFiles/QDatabaseControl/DatabaseCommands/QPointSaleAndPriceTableCommands/qpointsaleandpricetablecommands.cpp \
        ../commonFiles/QDatabaseControl/DatabaseCommands/QPointSaleCommands/QPointSaleQueries/qpointsalequeries.cpp \
        ../commonFiles/QDatabaseControl/DatabaseCommands/QPointSaleCommands/qpointsalecommands.cpp \
        ../commonFiles/QDatabaseControl/DatabaseCommands/QPriceCommands/QPriceQueries/qpricequeries.cpp \
        ../commonFiles/QDatabaseControl/DatabaseCommands/QPriceCommands/qpricecommands.cpp \
        ../commonFiles/QDatabaseControl/DatabaseCommands/QProductAndCategoryTableCommands/QProductAndCategoryQueries/qproductandcategoryqueries.cpp \
        ../commonFiles/QDatabaseControl/DatabaseCommands/QProductAndCategoryTableCommands/qproductandcategorytablecommands.cpp \
        ../commonFiles/QDatabaseControl/DatabaseCommands/QProductAndVolumeTableCommands/QProductAndVolumeTableQueries/qproductandvolumetablequeries.cpp \
        ../commonFiles/QDatabaseControl/DatabaseCommands/QProductAndVolumeTableCommands/qproductandvolumetablecommands.cpp \
        ../commonFiles/QDatabaseControl/DatabaseCommands/QProductCommands/QProductQueries/qproductqueries.cpp \
        ../commonFiles/QDatabaseControl/DatabaseCommands/QProductCommands/qproductcommands.cpp \
        ../commonFiles/QDatabaseControl/DatabaseCommands/QProductPictureCommands/QProductPictureQueries/qproductpicturequeries.cpp \
        ../commonFiles/QDatabaseControl/DatabaseCommands/QProductPictureCommands/qproductpicturecommands.cpp \
        ../commonFiles/QDatabaseControl/DatabaseCommands/QReceiptCommands/QReceiptQueries/qreceiptqueries.cpp \
        ../commonFiles/QDatabaseControl/DatabaseCommands/QReceiptCommands/qreceiptcommands.cpp \
        ../commonFiles/QDatabaseControl/DatabaseCommands/QSalesCategoryCommands/QSalesCategoryQueries/qsalescategoryqueries.cpp \
        ../commonFiles/QDatabaseControl/DatabaseCommands/QSalesCategoryCommands/qsalescategorycommands.cpp \
        ../commonFiles/QDatabaseControl/DatabaseCommands/QShiftCommands/QShiftQueries/qshiftqueries.cpp \
        ../commonFiles/QDatabaseControl/DatabaseCommands/QShiftCommands/qshiftcommands.cpp \
        ../commonFiles/QDatabaseControl/DatabaseCommands/QSoldPositionCommands/QSoldPositionQueries/qsoldpositionqueries.cpp \
        ../commonFiles/QDatabaseControl/DatabaseCommands/QSoldPositionCommands/qsoldpositioncommands.cpp \
        ../commonFiles/QDatabaseControl/DatabaseCommands/QPaymentTypeCommands/QPaymentTypeQueries/qpaymenttypequeries.cpp \
        ../commonFiles/QDatabaseControl/DatabaseCommands/QPaymentTypeCommands/qpaymenttypecommands.cpp \
        ../commonFiles/QDatabaseControl/DatabaseCommands/QUserCommands/QUserQueries/quserqueries.cpp \
        ../commonFiles/QDatabaseControl/DatabaseCommands/QUserCommands/qusercommands.cpp \
        ../commonFiles/QDatabaseControl/DatabaseCommands/QVolumeProductCommands/QVolumeQueries/qvolumequeries.cpp \
        ../commonFiles/QDatabaseControl/DatabaseCommands/QVolumeProductCommands/qvolumeproductcommands.cpp \
        ../commonFiles/QDatabaseControl/qdatabaseconrol.cpp \
        ../commonFiles/QUnNetProtokol/qcrc32.cpp \
        ../commonFiles/QUnNetProtokol/qunaccountinfo.cpp \
        ../commonFiles/QUnNetProtokol/qunaccountmanager.cpp \
        ../commonFiles/QUnNetProtokol/qunclienthandler.cpp \
        ../commonFiles/QUnNetProtokol/qundatabasesettings.cpp \
        ../commonFiles/QUnNetProtokol/qundbpacketmanager.cpp \
        ../commonFiles/QUnNetProtokol/qunnetprotokolclient.cpp \
        ../commonFiles/QUnNetProtokol/qunnetprotokolserver.cpp \
        ../commonFiles/QUnNetProtokol/qunpacketmanager.cpp \
        ../commonFiles/SalesSystem/QColorConsole/qcolorconsole.cpp \
        ../commonFiles/SalesSystem/QPointSale/qpointsale.cpp \
        ../commonFiles/SalesSystem/QPrice/qprice.cpp \
        ../commonFiles/SalesSystem/QProduct/qproduct.cpp \
        ../commonFiles/SalesSystem/QProductPicture/qproductpicture.cpp \
        ../commonFiles/SalesSystem/QReceipt/qreceipt.cpp \
        ../commonFiles/SalesSystem/QSalesByteArray/QSalesFromByteArray/qsalesfrombytearray.cpp \
        ../commonFiles/SalesSystem/QSalesByteArray/QSalesToByteArray/qsalestobytearray.cpp \
        ../commonFiles/SalesSystem/QSalesByteArray/qsalesbytearray.cpp \
        ../commonFiles/SalesSystem/QSalesСategory/qsalescategory.cpp \
        ../commonFiles/SalesSystem/QShift/qshift.cpp \
        ../commonFiles/SalesSystem/QSoldPosition/qsoldposition.cpp \
        ../commonFiles/SalesSystem/QPaymentType/qpaymenttype.cpp \
        ../commonFiles/SalesSystem/QStatistics/qstatistics.cpp \
        ../commonFiles/SalesSystem/QUser/quser.cpp \
        ../commonFiles/SalesSystem/QVolumeProduct/qvolumeproduct.cpp \
        include/SalesServer/QPlugins/QStatisticsGetter/qstatisticsgetter.cpp \
        include/SalesServer/QPlugins/QStatisticsGetter/statisticshandlers.cpp \
        include/SalesServer/QPlugins/QStatisticsGetter/templatestatisticshandler.cpp \
        include/SalesServer/QPlugins/qsalesserverplugin.cpp \
        include/SalesServer/QPlugins/qserverplugin.cpp \
        include/SalesServer/QServerLoader/qserverloader.cpp \
        main.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \ \
    ../commonFiles/DatabaseEnumCommands/DatabaseEnumCommands.h \
    ../commonFiles/QDataBaseSettings/qdatabasesettings.h \
    ../commonFiles/QDatabaseControl/DatabaseCommands/QParentDatabaseCommands/qparentdatabasecommands.h \
    ../commonFiles/QDatabaseControl/DatabaseCommands/QPointSaleAndCategoryTableCommands/QPointSaleAndCategoryTableQueries/qpointsaleandcategorytablequeries.h \
    ../commonFiles/QDatabaseControl/DatabaseCommands/QPointSaleAndCategoryTableCommands/qpointsaleandcategorytablecommands.h \
    ../commonFiles/QDatabaseControl/DatabaseCommands/QPointSaleAndPriceTableCommands/QPointSaleAndPriceQueries/qpointsaleandpricequeries.h \
    ../commonFiles/QDatabaseControl/DatabaseCommands/QPointSaleAndPriceTableCommands/qpointsaleandpricetablecommands.h \
    ../commonFiles/QDatabaseControl/DatabaseCommands/QPointSaleCommands/QPointSaleQueries/qpointsalequeries.h \
    ../commonFiles/QDatabaseControl/DatabaseCommands/QPointSaleCommands/qpointsalecommands.h \
    ../commonFiles/QDatabaseControl/DatabaseCommands/QPriceCommands/QPriceQueries/qpricequeries.h \
    ../commonFiles/QDatabaseControl/DatabaseCommands/QPriceCommands/qpricecommands.h \
    ../commonFiles/QDatabaseControl/DatabaseCommands/QProductAndCategoryTableCommands/QProductAndCategoryQueries/qproductandcategoryqueries.h \
    ../commonFiles/QDatabaseControl/DatabaseCommands/QProductAndCategoryTableCommands/qproductandcategorytablecommands.h \
    ../commonFiles/QDatabaseControl/DatabaseCommands/QProductAndVolumeTableCommands/QProductAndVolumeTableQueries/qproductandvolumetablequeries.h \
    ../commonFiles/QDatabaseControl/DatabaseCommands/QProductAndVolumeTableCommands/qproductandvolumetablecommands.h \
    ../commonFiles/QDatabaseControl/DatabaseCommands/QProductCommands/QProductQueries/qproductqueries.h \
    ../commonFiles/QDatabaseControl/DatabaseCommands/QProductCommands/qproductcommands.h \
    ../commonFiles/QDatabaseControl/DatabaseCommands/QProductPictureCommands/QProductPictureQueries/qproductpicturequeries.h \
    ../commonFiles/QDatabaseControl/DatabaseCommands/QProductPictureCommands/qproductpicturecommands.h \
    ../commonFiles/QDatabaseControl/DatabaseCommands/QReceiptCommands/QReceiptQueries/qreceiptqueries.h \
    ../commonFiles/QDatabaseControl/DatabaseCommands/QReceiptCommands/qreceiptcommands.h \
    ../commonFiles/QDatabaseControl/DatabaseCommands/QSalesCategoryCommands/QSalesCategoryQueries/qsalescategoryqueries.h \
    ../commonFiles/QDatabaseControl/DatabaseCommands/QSalesCategoryCommands/qsalescategorycommands.h \
    ../commonFiles/QDatabaseControl/DatabaseCommands/QShiftCommands/QShiftQueries/qshiftqueries.h \
    ../commonFiles/QDatabaseControl/DatabaseCommands/QShiftCommands/qshiftcommands.h \
    ../commonFiles/QDatabaseControl/DatabaseCommands/QSoldPositionCommands/QSoldPositionQueries/qsoldpositionqueries.h \
    ../commonFiles/QDatabaseControl/DatabaseCommands/QSoldPositionCommands/qsoldpositioncommands.h \
    ../commonFiles/QDatabaseControl/DatabaseCommands/QPaymentTypeCommands/QPaymentTypeQueries/qpaymenttypequeries.h \
    ../commonFiles/QDatabaseControl/DatabaseCommands/QPaymentTypeCommands/qpaymenttypecommands.h \
    ../commonFiles/QDatabaseControl/DatabaseCommands/QUserCommands/QUserQueries/quserqueries.h \
    ../commonFiles/QDatabaseControl/DatabaseCommands/QUserCommands/qusercommands.h \
    ../commonFiles/QDatabaseControl/DatabaseCommands/QVolumeProductCommands/QVolumeQueries/qvolumequeries.h \
    ../commonFiles/QDatabaseControl/DatabaseCommands/QVolumeProductCommands/qvolumeproductcommands.h \
    ../commonFiles/QDatabaseControl/qdatabaseconrol.h \
    ../commonFiles/QUnNetProtokol/commonunnetworktypes.h \
    ../commonFiles/QUnNetProtokol/qcrc32.h \
    ../commonFiles/QUnNetProtokol/qunaccountinfo.h \
    ../commonFiles/QUnNetProtokol/qunaccountmanager.h \
    ../commonFiles/QUnNetProtokol/qunclienthandler.h \
    ../commonFiles/QUnNetProtokol/qundatabasesettings.h \
    ../commonFiles/QUnNetProtokol/qundbpacketmanager.h \
    ../commonFiles/QUnNetProtokol/qunnetprotokolclient.h \
    ../commonFiles/QUnNetProtokol/qunnetprotokolserver.h \
    ../commonFiles/QUnNetProtokol/qunpacketmanager.h \
    ../commonFiles/SalesSystem/QColorConsole/qcolorconsole.h \
    ../commonFiles/SalesSystem/QPointSale/qpointsale.h \
    ../commonFiles/SalesSystem/QPrice/qprice.h \
    ../commonFiles/SalesSystem/QProduct/qproduct.h \
    ../commonFiles/SalesSystem/QProductPicture/qproductpicture.h \
    ../commonFiles/SalesSystem/QReceipt/qreceipt.h \
    ../commonFiles/SalesSystem/QSalesByteArray/QSalesFromByteArray/qsalesfrombytearray.h \
    ../commonFiles/SalesSystem/QSalesByteArray/QSalesToByteArray/qsalestobytearray.h \
    ../commonFiles/SalesSystem/QSalesByteArray/qsalesbytearray.h \
    ../commonFiles/SalesSystem/QSalesСategory/qsalescategory.h \
    ../commonFiles/SalesSystem/QShift/qshift.h \
    ../commonFiles/SalesSystem/QSoldPosition/qsoldposition.h \
    ../commonFiles/SalesSystem/QPaymentType/qpaymenttype.h \
    ../commonFiles/SalesSystem/QStatistics/qstatistics.h \
    ../commonFiles/SalesSystem/QUser/quser.h \
    ../commonFiles/SalesSystem/QVolumeProduct/qvolumeproduct.h \
    include/SalesServer/QPlugins/QStatisticsGetter/qstatisticsgetter.h \
    include/SalesServer/QPlugins/QStatisticsGetter/statisticshandlers.h \
    include/SalesServer/QPlugins/QStatisticsGetter/templatestatisticshandler.h \
    include/SalesServer/QPlugins/qsalesserverplugin.h \
    include/SalesServer/QPlugins/qserverplugin.h \
    include/SalesServer/QServerLoader/qserverloader.h

*linux-opiz-g++* {
    message ("armhf")
    target.path = /home/karpinochkin
    INSTALLS += target
}
