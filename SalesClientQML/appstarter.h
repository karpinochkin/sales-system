#ifndef APPSTARTER_H
#define APPSTARTER_H

#include <QObject>
#include <QDebug>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QApplication>
#include <QStandardPaths>
#include "middlewareqml.h"
#include "productimageprovider.h"

class AppStarter : public QObject
{
    Q_OBJECT
public:
    explicit AppStarter(QObject *parent = nullptr);
    ~AppStarter() override;

    QQmlApplicationEngine *engine = nullptr;
    MiddlewareQML *middleware = nullptr;

public slots:
    void saveQmlEngineWarnings(const QList<QQmlError> &listError);
};

#endif // APPSTARTER_H
