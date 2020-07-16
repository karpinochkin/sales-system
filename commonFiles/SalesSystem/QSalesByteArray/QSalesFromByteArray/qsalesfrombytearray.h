#ifndef QSALESFROMBYTEARRAY_H
#define QSALESFROMBYTEARRAY_H

#include <QString>
#include <QVector>
#include <QByteArray>

class QSalesFromByteArray
{
public:
    void intFromByteArray(int &valueToWrite, QByteArray *data);
    void stringFromByteArray(QString &stringToWrite, QByteArray *data);
    void vectorIntFromByteArray(QVector<int> &vectorToWrite, QByteArray *data);

protected:
    QSalesFromByteArray();
};

#endif // QSALESFROMBYTEARRAY_H
