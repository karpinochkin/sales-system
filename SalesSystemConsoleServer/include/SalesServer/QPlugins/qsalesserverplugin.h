#ifndef QSALESSERVERPLUGIN_H
#define QSALESSERVERPLUGIN_H

#include "qserverplugin.h"
#include "../commonFiles/QDatabaseControl/qdatabaseconrol.h"
#include "../commonFiles/DatabaseEnumCommands/DatabaseEnumCommands.h"
#include "../commonFiles/SalesSystem/QStatistics/qstatistics.h"
#include "QStatisticsGetter/qstatisticsgetter.h"

namespace Plugins {

class QSalesServerPlugin : public QServerPlugin
{
public:
    explicit QSalesServerPlugin(QUnNetProtokolServer *server,
                                quint16 business,
                                QObject *parent = nullptr);
    ~QSalesServerPlugin();

private:
    QDatabaseConrol *databaseControl = nullptr;

    void processCommand(quint8 command,QByteArray data, QUnClientHandler *client);
    void dataBaseIsInit();

    void command0xA1_handshake(QByteArray &data, QUnClientHandler *client);
    void command0x01_sendPointSale(QByteArray &data, QUnClientHandler *client);
    void command0x02_sendCategories(QByteArray &data, QUnClientHandler *client); // Запрос информации о категориях
    void command0x03_sendProducts(QByteArray &data, QUnClientHandler *client); // Запрос списка напитков
    void command0x04_sendVolumes(QByteArray &data, QUnClientHandler *client); // Запрос списка объемов напитков
    void command0x05_sendTypes(QByteArray &data, QUnClientHandler *client); // Запрос списка типов напитков
    void command0x06_sendPrices(QByteArray &data, QUnClientHandler *client); // Запрос цен
    void command0x07_sendUser(QByteArray &data, QUnClientHandler *client); // Запрос информации о пользователе
    void command0x08_openShift(QByteArray &data, QUnClientHandler *client); // Открыть смену
    void command0x09_closeShift(QByteArray &data, QUnClientHandler *client); // Закрыть смену
    void command0x0A_sendReceipts(QByteArray &data, QUnClientHandler *client); // Запрос чеков для смены
    void command0x0B_sendSoldPositions(QByteArray &data, QUnClientHandler *client); // Запрос проданных позиций
    void command0x0C_getSale(QByteArray &data, QUnClientHandler *client); // Получение продажи
    void command0x0D_uploadPicture(QByteArray &data, QUnClientHandler *client); // Выгрузка картинки
    void command0x0E_sendPicture(QByteArray &data, QUnClientHandler *client); // Запрос информации о картинке
    void command0x0F_sendIdAllPointSales(QByteArray &data, QUnClientHandler *client); // Запрос id всех точек продаж
    void command0x10_sendPointSale(QByteArray &data, QUnClientHandler *client); // Запрос точки продаж (?)
    void command0x11_sendAllCategories(QByteArray &data, QUnClientHandler *client); // Запрос всех категорий
    void command0x12_sendAllProducts(QByteArray &data, QUnClientHandler *client); // Запрос всех напитков
    void command0x13_sendAllPrices(QByteArray &data, QUnClientHandler *client); // Запрос всех цен
    void command0x14_sendAllShifts(QByteArray &data, QUnClientHandler *client); // Запрос всех смен
    void command0x15_sendAllReceipts(QByteArray &data, QUnClientHandler *client); // Запрос всех чеков
    void command0x16_sendAllSoldPositions(QByteArray &data, QUnClientHandler *client); // Запрос всех проданых позиций

    void command0xA0_getProduct(QByteArray &data, QUnClientHandler *client); // Получение информации о напитке
    void command0xA2_endSynchronization(QByteArray &data, QUnClientHandler *client);
    void command0xB0_sendPointSales(QByteArray &data, QUnClientHandler *client);
    void command0xB1_sendAllPictures(QByteArray &data, QUnClientHandler *client);
    void command0xB2_removePicture(QByteArray &data, QUnClientHandler *client);
    void command0xB3_removeType(QByteArray &data, QUnClientHandler *client);
    void command0xB4_getType(QByteArray &data, QUnClientHandler *client);
    void command0xB5_removeVolume(QByteArray &data, QUnClientHandler *client);
    void command0xB6_getVolume(QByteArray &data, QUnClientHandler *client);
    void command0xB7_removeUser(QByteArray &data, QUnClientHandler *client);
    void command0XB8_getUser(QByteArray &data, QUnClientHandler *client);
    void command0xB9_sendAllUsers(QByteArray &data, QUnClientHandler *client);
    void command0xC1_getPointSale(QByteArray &data, QUnClientHandler *client);
    void command0xC2_removePointSale(QByteArray &data, QUnClientHandler *client);
    void command0xC3_getCategory(QByteArray &data, QUnClientHandler *client);
    void command0xC4_removeCategory(QByteArray &data, QUnClientHandler *client);
    void command0xC5_getPrice(QByteArray &data, QUnClientHandler *client);

    void command0xC6_sendReceiptsByDateRange(QByteArray &data, QUnClientHandler *client);
    void command0xC7_sendSoldPositionsByDateRange(QByteArray &data, QUnClientHandler *client);
    void command0xC8_sendStatistics(QByteArray &data, QUnClientHandler *client);

    void initPluginInformation();
    QByteArray getCorrectPointSaleOutput(QByteArray &data, QUnClientHandler *client);

    template<typename T>
    QByteArray templateSendAll(const QVector<T> &vector, QByteArray &data);
    template<typename T>
    QByteArray templateSendAllByDateRange(const QVector<T> &vector);
    template<typename T>
    QByteArray templateRemove(T *command, QByteArray &data);
    template<typename TCommand, typename TValue>
    QByteArray templateGet(TCommand *command, TValue &value, QByteArray &data);

    void testStatisticsGetter();
};

}
#endif // QSALESSERVERPLUGIN_H
