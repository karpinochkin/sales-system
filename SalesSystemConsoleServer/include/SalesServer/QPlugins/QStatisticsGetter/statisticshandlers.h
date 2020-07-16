#ifndef STATISTICSHANDLERS_H
#define STATISTICSHANDLERS_H

#include "templatestatisticshandler.h"

namespace Statistics {

class QMoney : public QTemplateStatisticsHandler
{
public:
    QMoney(QDatabaseConrol *db);
    ~QMoney() override = default;

private:
    QDatabaseConrol *db = nullptr;

    QVector<QVariant> getFirstVector() override;
    QString getKey(QVariant &) override;
    QVector<QVariant> getSecondVector(QVariant &, QDateTime startDate, QDateTime endDate) override;
    QDateTime getItemDateTime(QVariant &item) override;
    void updateResult(double *result, QVariant &item) override;
};

class QUsersMoney : public QTemplateStatisticsHandler
{
public:
    QUsersMoney(QDatabaseConrol *db);
    ~QUsersMoney() override = default;

private:
    QDatabaseConrol *db = nullptr;
    QHash <int, QReceipt> receiptHash;

    void hook(const StatisticsInput &info) override;
    QVector<QVariant> getFirstVector() override;
    QString getKey(QVariant &) override;
    QVector<QVariant> getSecondVector(QVariant &, QDateTime startDate, QDateTime endDate) override;
    QDateTime getItemDateTime(QVariant &item) override;
    void updateResult(double *result, QVariant &item) override;

};

class QNumberSoldProduct : public QTemplateStatisticsHandler
{
public:
    QNumberSoldProduct(QDatabaseConrol *db, const int idProduct);
    ~QNumberSoldProduct() override = default;

private:
    QDatabaseConrol *db = nullptr;
    int idProduct = -1;

    QVector<QVariant> getFirstVector() override;
    QString getKey(QVariant &) override;
    QVector<QVariant> getSecondVector(QVariant &, QDateTime startDate, QDateTime endDate) override;
    bool checkHook(QVariant &item) override;
    QDateTime getItemDateTime(QVariant &item) override;
    void updateResult(double *result, QVariant &item) override;
};

class QNumberSoldProductsForPointSale : public QTemplateStatisticsHandler
{
public:
    QNumberSoldProductsForPointSale(QDatabaseConrol *db, const int idPointSale);
    ~QNumberSoldProductsForPointSale() override = default;

private:
    QDatabaseConrol *db = nullptr;
    int idPointSale = -1;

    QVector<QVariant> getFirstVector() override;
    QString getKey(QVariant &) override;
    QVector<QVariant> getSecondVector(QVariant &, QDateTime startDate, QDateTime endDate) override;
    bool checkHook(QVariant &item) override;
    QDateTime getItemDateTime(QVariant &item) override;
    void updateResult(double *result, QVariant &item) override;
};

}

#endif // STATISTICSHANDLERS_H
