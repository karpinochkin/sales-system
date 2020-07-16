#ifndef QSALESTOBYTEARRAY_H
#define QSALESTOBYTEARRAY_H

#include <QVector>
#include <QString>
#include <QByteArray>

class QSalesToByteArray
{
public:
    void intToByteArray(int &value, QByteArray *arrayToWrite);
    void string45ToByteArray(QString &string, QByteArray *arrayToWrite);
    void string256ToByteArray(QString &string, QByteArray *arrayToWrite);
    void vectorIntToByteArray(QVector<int> &vector, QByteArray *arrayToWrite);

protected:
    QSalesToByteArray();

};

#endif // QSALESTOBYTEARRAY_H
