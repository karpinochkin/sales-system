#ifndef QTYPEPRODUCTCOMMANDS_H
#define QTYPEPRODUCTCOMMANDS_H

#include <QObject>
#include "../QParentDatabaseCommands/qparentdatabasecommands.h"
#include "../../../SalesSystem/QPaymentType/qpaymenttype.h"
#include "QPaymentTypeQueries/qpaymenttypequeries.h"

namespace DatabaseCommands {

class QPaymentTypeCommands : public QParentDatabaseCommands
{
public:
    QPaymentTypeCommands() = delete;
    QPaymentTypeCommands(QObject *parent = nullptr) = delete;
    explicit QPaymentTypeCommands(QSqlDatabase *database,
                                  QObject *parent = nullptr);
    ~QPaymentTypeCommands() = default;

    bool createTable();
    bool clear();
    QVector<QPaymentType> getTypes();
    QPaymentType get(int idTypeProduct);
    int add(const QPaymentType &type);
    int add(int id, const QPaymentType &type);
    bool edit(const QPaymentType &type);
    int getId(const QPaymentType &type);
    bool remove(int id, const QString &name);

private:
    void commonGet(QSqlQuery *query, QPaymentType &type);
};

}
#endif // QTYPEPRODUCTCOMMANDS_H
