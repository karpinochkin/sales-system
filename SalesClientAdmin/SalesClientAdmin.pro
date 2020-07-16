QT       += core gui sql network charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

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
    ../commonClientFiles/QDatabaseManager/qdatabasemanager.cpp \
    ../commonClientFiles/QNetManager/QClientCommandsToServer/QCategoryCommandsToServer/qcategorycommandstoserver.cpp \
    ../commonClientFiles/QNetManager/QClientCommandsToServer/QPictureCommandsToServer/qpicturecommandstoserver.cpp \
    ../commonClientFiles/QNetManager/QClientCommandsToServer/QPointSaleCommandsToServer/qpointsalecommandstoserver.cpp \
    ../commonClientFiles/QNetManager/QClientCommandsToServer/QPriceCommandsToServer/qpricecommandstoserver.cpp \
    ../commonClientFiles/QNetManager/QClientCommandsToServer/QProductCommandsToServer/qproductcommandstoserver.cpp \
    ../commonClientFiles/QNetManager/QClientCommandsToServer/QReceiptCommandsToServer/qreceiptcommandstoserver.cpp \
    ../commonClientFiles/QNetManager/QClientCommandsToServer/QShiftCommandsToServer/qshiftcommandstoserver.cpp \
    ../commonClientFiles/QNetManager/QClientCommandsToServer/QSoldPositionCommandsToServer/qsoldpositioncommandstoserver.cpp \
    ../commonClientFiles/QNetManager/QClientCommandsToServer/QStatisticsCommandsToServer/qstatisticscommandstoserver.cpp \
    ../commonClientFiles/QNetManager/QClientCommandsToServer/QTypeCommandsToServer/qtypecommandstoserver.cpp \
    ../commonClientFiles/QNetManager/QClientCommandsToServer/QUserCommandsToServer/qusercommandstoserver.cpp \
    ../commonClientFiles/QNetManager/QClientCommandsToServer/QVolumeCommandsToServer/qvolumecommandstoserver.cpp \
    ../commonClientFiles/QNetManager/QClientCommandsToServer/qclientcommandstoserver.cpp \
    ../commonClientFiles/QNetManager/QSynchronization/qsynchronization.cpp \
    ../commonClientFiles/QNetManager/qnetmanager.cpp \
    ../commonFiles/QDataBaseSettings/qdatabasesettings.cpp \
    ../commonFiles/QDatabaseControl/DatabaseCommands/QParentDatabaseCommands/qparentdatabasecommands.cpp \
    ../commonFiles/QDatabaseControl/DatabaseCommands/QPaymentTypeCommands/QPaymentTypeQueries/qpaymenttypequeries.cpp \
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
    gui/QMainWidget/QDatabaseTabWidget/QAbstractTab/qabstracttabletab.cpp \
    gui/QMainWidget/QDatabaseTabWidget/QCategoryTab/qcategoryeditdialog.cpp \
    gui/QMainWidget/QDatabaseTabWidget/QCategoryTab/qcategorytab.cpp \
    gui/QMainWidget/QDatabaseTabWidget/QCategoryTab/qcategorywidgetlistitem.cpp \
    gui/QMainWidget/QDatabaseTabWidget/QPictureTab/QPictureEditDialog/qpictureeditdialog.cpp \
    gui/QMainWidget/QDatabaseTabWidget/QPointSaleTab/qpointsaleeditdialog.cpp \
    gui/QMainWidget/QDatabaseTabWidget/QPointSaleTab/qpointsaletab.cpp \
    gui/QMainWidget/QDatabaseTabWidget/QPointSaleTab/qpointsaletabletab.cpp \
    gui/QMainWidget/QDatabaseTabWidget/QPointSaleTab/qpointsalewidgetlistitem.cpp \
    gui/QMainWidget/QDatabaseTabWidget/QPricesTab/qpriceseditdialog.cpp \
    gui/QMainWidget/QDatabaseTabWidget/QPricesTab/qpriceseditforproductdialog.cpp \
    gui/QMainWidget/QDatabaseTabWidget/QPricesTab/qpricestab.cpp \
    gui/QMainWidget/QDatabaseTabWidget/QPricesTab/qpricestabletab.cpp \
    gui/QMainWidget/QDatabaseTabWidget/QPricesTab/qpriceswidgetlistitem.cpp \
    gui/QMainWidget/QDatabaseTabWidget/QProductsTab/qproductseditdialog.cpp \
    gui/QMainWidget/QDatabaseTabWidget/QProductsTab/qproductstab.cpp \
    gui/QMainWidget/QDatabaseTabWidget/QProductsTab/qproductswidgetlistitem.cpp \
    gui/QMainWidget/QDatabaseTabWidget/QTypeTab/QTypeEditDialog/qtypeeditdialog.cpp \
    gui/QMainWidget/QDatabaseTabWidget/QTypeTab/QTypeWidgetListItem/qtypewidgetlistitem.cpp \
    gui/QMainWidget/QDatabaseTabWidget/QTypeTab/qtypetab.cpp \
    gui/QMainWidget/QDatabaseTabWidget/QTypeTab/qtypetabletab.cpp \
    gui/QMainWidget/QDatabaseTabWidget/QUserTab/qusereditdialog.cpp \
    gui/QMainWidget/QDatabaseTabWidget/QUserTab/qusertab.cpp \
    gui/QMainWidget/QDatabaseTabWidget/QUserTab/qusertabletab.cpp \
    gui/QMainWidget/QDatabaseTabWidget/QUserTab/quserwidgetlistitem.cpp \
    gui/QMainWidget/QDatabaseTabWidget/QVolumeTab/qvolumeeditdialog.cpp \
    gui/QMainWidget/QDatabaseTabWidget/QVolumeTab/qvolumetab.cpp \
    gui/QMainWidget/QDatabaseTabWidget/QVolumeTab/qvolumetabletab.cpp \
    gui/QMainWidget/QDatabaseTabWidget/QVolumeTab/qvolumewidgetlistitem.cpp \
    gui/QMainWidget/QInformationTabWidget/qinformationtabwidget.cpp \
    gui/QMainWidget/QStatisticsTabWidget/GraphicsPrinter/qgraphicsprinter.cpp \
    gui/QMainWidget/QStatisticsTabWidget/qsaleschartview.cpp \
    gui/QMainWidget/QStatisticsTabWidget/qstatisticschoicedialog.cpp \
    gui/QMainWidget/QStatisticsTabWidget/qstatisticstabwidget.cpp \
    gui/QMainWidget/widgets/QColorWidget/qcolorwidget.cpp \
    gui/QMainWidget/widgets/QDoubleNumberEdit/qdoublenumberedit.cpp \
    gui/QMainWidget/widgets/QEdit/qedit.cpp \
    gui/QMainWidget/widgets/QMultipleChoiceBox/QMultipleChoiceBoxItem/qmultiplechoiceboxitem.cpp \
    gui/QMainWidget/widgets/QMultipleChoiceBox/qmultiplechoicebox.cpp \
    gui/QMainWidget/widgets/QNumberEdit/qnumberedit.cpp \
    gui/QMainWidget/widgets/QPictureWidget/QPictureDialog/qpicturedialog.cpp \
    gui/QMainWidget/widgets/QPictureWidget/QPictureDialog/qpicturewidgetitem.cpp \
    gui/QMainWidget/widgets/QPictureWidget/qpicturewidget.cpp \
    gui/QMainWidget/widgets/QPopUpMessage/qpopupmessage.cpp \
    gui/QMainWidget/widgets/QSalesCalendarInterval/qsalescalendarinterval.cpp \
    gui/QMainWidget/widgets/QSalesComboBox/qsalescombobox.cpp \
    gui/QMainWidget/widgets/QSalesDateTimeEdit/qsalesdatetimeedit.cpp \
    gui/QMainWidget/widgets/QSingleChoiceBox/qsinglechoicebox.cpp \
    gui/QMainWidget/widgets/QSingleChoiceBox/qsinglechoiceboxitem.cpp \
    gui/QMainWidget/widgets/QStepperComboBox/qsteppercombobox.cpp \
    gui/loader/QAccountDialog/qaccountdialog.cpp \
    gui/loader/QDateRangeDialog/qdaterangedialog.cpp \
    gui/loader/QHostsDialog/qhostsdialog.cpp \
    gui/loader/QLoaderScreen/qloaderscreen.cpp \
    gui/QMainWidget/QDatabaseTabWidget/QAbstractTab/qabstracttab.cpp \
    gui/QMainWidget/QDatabaseTabWidget/QPictureTab/qpicturetab.cpp \
    gui/QMainWidget/QDatabaseTabWidget/QPictureTab/qpicturewidgetlistitem.cpp \
    gui/QMainWidget/QDatabaseTabWidget/qdatabasetabwidget.cpp \
    gui/QMainWidget/QHTabWidget/QHTabBar/qhtabbar.cpp \
    gui/QMainWidget/QHTabWidget/qhtabwidget.cpp \
    gui/QMainWidget/qmainwidget.cpp \
    gui/loader/QSalesSplashScreen/qsalessplashscreen.cpp \
    include/QClientLoader/qclientloader.cpp \
#    include/QDatabaseManager/qdatabasemanager.cpp \
    main.cpp

HEADERS += \
    ../commonClientFiles/QDatabaseManager/qdatabasemanager.h \
    ../commonClientFiles/QNetManager/QClientCommandsToServer/QCategoryCommandsToServer/qcategorycommandstoserver.h \
    ../commonClientFiles/QNetManager/QClientCommandsToServer/QParentCommandsToServer/qparentcommandstoserver.h \
    ../commonClientFiles/QNetManager/QClientCommandsToServer/QPictureCommandsToServer/qpicturecommandstoserver.h \
    ../commonClientFiles/QNetManager/QClientCommandsToServer/QPointSaleCommandsToServer/qpointsalecommandstoserver.h \
    ../commonClientFiles/QNetManager/QClientCommandsToServer/QPriceCommandsToServer/qpricecommandstoserver.h \
    ../commonClientFiles/QNetManager/QClientCommandsToServer/QProductCommandsToServer/qproductcommandstoserver.h \
    ../commonClientFiles/QNetManager/QClientCommandsToServer/QReceiptCommandsToServer/qreceiptcommandstoserver.h \
    ../commonClientFiles/QNetManager/QClientCommandsToServer/QShiftCommandsToServer/qshiftcommandstoserver.h \
    ../commonClientFiles/QNetManager/QClientCommandsToServer/QSoldPositionCommandsToServer/qsoldpositioncommandstoserver.h \
    ../commonClientFiles/QNetManager/QClientCommandsToServer/QStatisticsCommandsToServer/qstatisticscommandstoserver.h \
    ../commonClientFiles/QNetManager/QClientCommandsToServer/QTypeCommandsToServer/qtypecommandstoserver.h \
    ../commonClientFiles/QNetManager/QClientCommandsToServer/QUserCommandsToServer/qusercommandstoserver.h \
    ../commonClientFiles/QNetManager/QClientCommandsToServer/QVolumeCommandsToServer/qvolumecommandstoserver.h \
    ../commonClientFiles/QNetManager/QClientCommandsToServer/qclientcommandstoserver.h \
    ../commonClientFiles/QNetManager/QSynchronization/qsynchronization.h \
    ../commonClientFiles/QNetManager/qnetmanager.h \
    ../commonFiles/QDataBaseSettings/qdatabasesettings.h \
    ../commonFiles/QDatabaseControl/DatabaseCommands/QParentDatabaseCommands/qparentdatabasecommands.h \
    ../commonFiles/QDatabaseControl/DatabaseCommands/QPaymentTypeCommands/QPaymentTypeQueries/qpaymenttypequeries.h \
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
    ../commonFiles/SalesSystem/QSalesObjects/qsalesobjects.h \
    ../commonFiles/SalesSystem/QSalesСategory/qsalescategory.h \
    ../commonFiles/SalesSystem/QShift/qshift.h \
    ../commonFiles/SalesSystem/QSoldPosition/qsoldposition.h \
    ../commonFiles/SalesSystem/QPaymentType/qpaymenttype.h \
    ../commonFiles/SalesSystem/QStatistics/qstatistics.h \
    ../commonFiles/SalesSystem/QUser/quser.h \
    ../commonFiles/SalesSystem/QVolumeProduct/qvolumeproduct.h \
    gui/QMainWidget/QDatabaseTabWidget/QAbstractTab/QAbstractWidgetListItem.h \
    gui/QMainWidget/QDatabaseTabWidget/QAbstractTab/qabstracteditdialog.h \
    gui/QMainWidget/QDatabaseTabWidget/QAbstractTab/qabstracttabletab.h \
    gui/QMainWidget/QDatabaseTabWidget/QCategoryTab/qcategoryeditdialog.h \
    gui/QMainWidget/QDatabaseTabWidget/QCategoryTab/qcategorytab.h \
    gui/QMainWidget/QDatabaseTabWidget/QCategoryTab/qcategorywidgetlistitem.h \
    gui/QMainWidget/QDatabaseTabWidget/QPictureTab/QPictureEditDialog/qpictureeditdialog.h \
    gui/QMainWidget/QDatabaseTabWidget/QPointSaleTab/qpointsaleeditdialog.h \
    gui/QMainWidget/QDatabaseTabWidget/QPointSaleTab/qpointsaletab.h \
    gui/QMainWidget/QDatabaseTabWidget/QPointSaleTab/qpointsaletabletab.h \
    gui/QMainWidget/QDatabaseTabWidget/QPointSaleTab/qpointsalewidgetlistitem.h \
    gui/QMainWidget/QDatabaseTabWidget/QPricesTab/qpriceseditdialog.h \
    gui/QMainWidget/QDatabaseTabWidget/QPricesTab/qpriceseditforproductdialog.h \
    gui/QMainWidget/QDatabaseTabWidget/QPricesTab/qpricestab.h \
    gui/QMainWidget/QDatabaseTabWidget/QPricesTab/qpricestabletab.h \
    gui/QMainWidget/QDatabaseTabWidget/QPricesTab/qpriceswidgetlistitem.h \
    gui/QMainWidget/QDatabaseTabWidget/QProductsTab/qproductseditdialog.h \
    gui/QMainWidget/QDatabaseTabWidget/QProductsTab/qproductstab.h \
    gui/QMainWidget/QDatabaseTabWidget/QProductsTab/qproductswidgetlistitem.h \
    gui/QMainWidget/QDatabaseTabWidget/QTypeTab/QTypeEditDialog/qtypeeditdialog.h \
    gui/QMainWidget/QDatabaseTabWidget/QTypeTab/QTypeWidgetListItem/qtypewidgetlistitem.h \
    gui/QMainWidget/QDatabaseTabWidget/QTypeTab/qtypetab.h \
    gui/QMainWidget/QDatabaseTabWidget/QTypeTab/qtypetabletab.h \
    gui/QMainWidget/QDatabaseTabWidget/QUserTab/qusereditdialog.h \
    gui/QMainWidget/QDatabaseTabWidget/QUserTab/qusertab.h \
    gui/QMainWidget/QDatabaseTabWidget/QUserTab/qusertabletab.h \
    gui/QMainWidget/QDatabaseTabWidget/QUserTab/quserwidgetlistitem.h \
    gui/QMainWidget/QDatabaseTabWidget/QVolumeTab/qvolumeeditdialog.h \
    gui/QMainWidget/QDatabaseTabWidget/QVolumeTab/qvolumetab.h \
    gui/QMainWidget/QDatabaseTabWidget/QVolumeTab/qvolumetabletab.h \
    gui/QMainWidget/QDatabaseTabWidget/QVolumeTab/qvolumewidgetlistitem.h \
    gui/QMainWidget/QInformationTabWidget/qinformationtabwidget.h \
    gui/QMainWidget/QStatisticsTabWidget/GraphicsPrinter/qgraphicsprinter.h \
    gui/QMainWidget/QStatisticsTabWidget/qsaleschartview.h \
    gui/QMainWidget/QStatisticsTabWidget/qstatisticschoicedialog.h \
    gui/QMainWidget/QStatisticsTabWidget/qstatisticstabwidget.h \
    gui/QMainWidget/widgets/QColorWidget/qcolorwidget.h \
    gui/QMainWidget/widgets/QDoubleNumberEdit/qdoublenumberedit.h \
    gui/QMainWidget/widgets/QEdit/qedit.h \
    gui/QMainWidget/widgets/QMultipleChoiceBox/QMultipleChoiceBoxItem/qmultiplechoiceboxitem.h \
    gui/QMainWidget/widgets/QMultipleChoiceBox/qmultiplechoicebox.h \
    gui/QMainWidget/widgets/QNumberEdit/qnumberedit.h \
    gui/QMainWidget/widgets/QPictureWidget/QPictureDialog/qpicturedialog.h \
    gui/QMainWidget/widgets/QPictureWidget/QPictureDialog/qpicturewidgetitem.h \
    gui/QMainWidget/widgets/QPictureWidget/qpicturewidget.h \
    gui/QMainWidget/widgets/QPopUpMessage/qpopupmessage.h \
    gui/QMainWidget/widgets/QSalesCalendarInterval/qsalescalendarinterval.h \
    gui/QMainWidget/widgets/QSalesComboBox/qsalescombobox.h \
    gui/QMainWidget/widgets/QSalesDateTimeEdit/qsalesdatetimeedit.h \
    gui/QMainWidget/widgets/QSingleChoiceBox/qsinglechoicebox.h \
    gui/QMainWidget/widgets/QSingleChoiceBox/qsinglechoiceboxitem.h \
    gui/QMainWidget/widgets/QStepperComboBox/qsteppercombobox.h \
    gui/loader/QAccountDialog/qaccountdialog.h \
    gui/loader/QDateRangeDialog/qdaterangedialog.h \
    gui/loader/QHostsDialog/qhostsdialog.h \
    gui/loader/QLoaderScreen/qloaderscreen.h \
    gui/QMainWidget/QDatabaseTabWidget/QAbstractTab/qabstracttab.h \
    gui/QMainWidget/QDatabaseTabWidget/QPictureTab/qpicturetab.h \
    gui/QMainWidget/QDatabaseTabWidget/QPictureTab/qpicturewidgetlistitem.h \
    gui/QMainWidget/QDatabaseTabWidget/qdatabasetabwidget.h \
    gui/QMainWidget/QHTabWidget/QHTabBar/qhtabbar.h \
    gui/QMainWidget/QHTabWidget/qhtabwidget.h \
    gui/QMainWidget/qmainwidget.h \
    gui/loader/QSalesSplashScreen/qsalessplashscreen.h \
    include/QClientLoader/qclientloader.h \
#    include/QDatabaseManager/qdatabasemanager.h \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    icons.qrc \
    images.qrc

DISTFILES += \
    images/SplashScreen.jpg
