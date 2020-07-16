#include "qsalestobytearray.h"

QSalesToByteArray::QSalesToByteArray()
{

}


void QSalesToByteArray::intToByteArray(int &value, QByteArray *arrayToWrite)
{
    quint8 *ptr;
    (*arrayToWrite).push_back(static_cast<quint8>(sizeof (value)));
    ptr = reinterpret_cast<quint8*>(&value);

    for (quint8 i = 0; i < sizeof(value); i++) {
        (*arrayToWrite).push_back(static_cast<char>(*(ptr + i)));
    }
}

void QSalesToByteArray::string45ToByteArray(QString &string,
                                            QByteArray *arrayToWrite)
{
    if(string.size() > 45) {
        string = string.mid(0, 45);
    }
    (*arrayToWrite).push_back(static_cast<char>(static_cast<quint8>(string.toUtf8().size())));
    (*arrayToWrite).push_back(string.toUtf8());
}

void QSalesToByteArray::string256ToByteArray(QString &string,
                                             QByteArray *arrayToWrite)
{
    if (string.size() > 256) {
        string = string.mid(0,256);
    }
    (*arrayToWrite).push_back(static_cast<char>(static_cast<quint8>(string.toUtf8().size())));
    (*arrayToWrite).push_back(string.toUtf8());
}

void QSalesToByteArray::vectorIntToByteArray(QVector<int> &vector,
                                             QByteArray *arrayToWrite)
{
    int currentValue;
    (*arrayToWrite).push_back(static_cast<char>(static_cast<quint8>(vector.size())));
    quint8 *ptr = reinterpret_cast<quint8*>(&currentValue);

    for (int i = 0; i < vector.size(); i++) {
        currentValue = vector.at(i);
        (*arrayToWrite).push_back(static_cast<char>(*(ptr)));
        (*arrayToWrite).push_back(static_cast<char>(*(ptr+1)));
        (*arrayToWrite).push_back(static_cast<char>(*(ptr+2)));
        (*arrayToWrite).push_back(static_cast<char>(*(ptr+3)));
    }
}


