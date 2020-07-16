#include "qsalesfrombytearray.h"

QSalesFromByteArray::QSalesFromByteArray()
{

}

void QSalesFromByteArray::intFromByteArray(int &valueToWrite,
                                           QByteArray *data)
{
    quint8 *ptr = reinterpret_cast<quint8*>(&valueToWrite);
    int size = (*data).at(0);
    QByteArray buf = (*data).mid(1, size);
    (*data).remove(0, size + 1);
    for (int i = 0; i < size; i++) {
        *(ptr+i) = static_cast<quint8>(buf.at(i));
    }
}

void QSalesFromByteArray::stringFromByteArray(QString &stringToWrite,
                                              QByteArray *data)
{
    int size = (*data).at(0);
    QByteArray buf = (*data).mid(1, size);
    (*data).remove(0, size + 1);
    stringToWrite = QString(buf);

}

void QSalesFromByteArray::vectorIntFromByteArray(QVector<int> &vectorToWrite,
                                                 QByteArray *data)
{
    vectorToWrite.clear();
    quint8 currentCount = static_cast<quint8>((*data).at(0));
    int currentValue;
    quint8 *ptr = reinterpret_cast<quint8*>(&currentValue);
    (*data).remove(0,1);
    for (int i=0;i<currentCount;i++) {
        *(ptr) = static_cast<quint8>((*data).at(4*i));
        *(ptr+1) = static_cast<quint8>((*data).at(4*i+1));
        *(ptr+2) = static_cast<quint8>((*data).at(4*i+2));
        *(ptr+3) = static_cast<quint8>((*data).at(4*i+3));

        vectorToWrite.push_back(currentValue);
    }
    (*data).remove(0,sizeof(currentValue)*currentCount);
}

