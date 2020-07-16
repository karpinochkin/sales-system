#ifndef QSALESBYTEARRAY_H
#define QSALESBYTEARRAY_H

#include "QSalesToByteArray/qsalestobytearray.h"
#include "QSalesFromByteArray/qsalesfrombytearray.h"

class QSalesByteArray : public QSalesToByteArray, public QSalesFromByteArray
{
public:
    QSalesByteArray();
};

#endif // QSALESBYTEARRAY_H
