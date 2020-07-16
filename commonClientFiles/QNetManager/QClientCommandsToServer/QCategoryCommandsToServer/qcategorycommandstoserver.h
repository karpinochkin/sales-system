#ifndef QCATEGORYCOMMANDSTOSERVER_H
#define QCATEGORYCOMMANDSTOSERVER_H

#include "../QParentCommandsToServer/qparentcommandstoserver.h"
#include "../commonFiles/SalesSystem/QSalesСategory/qsalescategory.h"
class QCategoryCommandsToServer : public CommandsToServer::QParentCommandsToServer
{
    Q_OBJECT
public:
    explicit QCategoryCommandsToServer(QObject *parent = nullptr);
    ~QCategoryCommandsToServer() = default;

    void load(const QVector<int> &idCategories);
    void loadAll();
    void send(QSalesCategory &category);
    void remove(int id, const QString &name);
};

#endif // QCATEGORYCOMMANDSTOSERVER_H
