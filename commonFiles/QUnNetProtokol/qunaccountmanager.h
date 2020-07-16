#ifndef QUNACCOUNTMANAGER_H
#define QUNACCOUNTMANAGER_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDateTime>
#include <QVector>
#include <QTime>
#include <QMutex>

#include <QDebug>

#include "qunaccountinfo.h"

class QUnAccountManager : public QObject
{
    Q_OBJECT
public:
    explicit QUnAccountManager(QSqlDatabase *dataBase_, QObject *parent = nullptr);
    ~QUnAccountManager();

    bool activateEmail (int id, int code);
    bool activateNumber (int id,int code);

    bool createAccount (QUNAccountInfo accountInfo);

    bool checkPassword (int id, QString password);
    bool checkLogin (QString login);

    bool editAccount(QUNAccountInfo &accountInfo);

    QVector<QUNAccountInfo> getAccountsList();
    QUNAccountInfo getAccountInfo(int id);
    QUNAccountInfo getAccountInfo(QString login);
    QString getPassword (int id);
    QString getLogin (int id);
    QString getNumber (int id);
    QString getEmail (int id);
    QString getName (int id);
    QString getPatronymic (int id);
    QString getSurname (int id);
    QString getFullName (int id);
    int getEmailCode (int id);
    int getNumberCode (int id);
    int getRights (int id);
    int getCountAccounts ();

    int generateEmailCode (int id);
    int generateNumberCode (int id);

    int indexOf(QString login);

    bool isEnable(int id);
    bool isActivate(int id);
    bool isActivateEmail (int id);
    bool isActivateNumber (int id);
    bool isVisible (int id);

    bool setLogin (int id, QString login);
    bool setName (int id, QString name);
    bool setPatronymic (int id,QString patronymic);
    bool setSurname (int id, QString surname);
    bool setEmail (int id,QString email);
    bool setNumber (int id,QString number);
    bool setActiate (int id,bool activate);
    bool setActivateEmail (int id,bool activate);
    bool setActivateNumber (int id,bool activate);
    bool setEmailCode (int id,int code);
    bool setnNumberCode (int id,int code);
    bool setRights (int id,int rights);

    bool updateAccount(int id, QUNAccountInfo accountInfo);

private:
    QSqlDatabase *dataBase = NULL;
    void initDB();
    QMutex *mutexDataBase;
    QSqlQuery *execQuery(QString textQuery, bool *ok=NULL);

signals:
    void signalCreatedNewAccount();

public slots:
};

#endif // QUNACCOUNTMANAGER_H
