#include "appstarter.h"

//
AppStarter::AppStarter(QObject *parent) :
    QObject(parent)
{
    engine = new QQmlApplicationEngine(this);
    middleware = new MiddlewareQML(this);
    connect(engine, &QQmlApplicationEngine::warnings,
            this, &AppStarter::saveQmlEngineWarnings);

    engine->rootContext()->setContextProperty("middlewareQML", middleware);
    engine->rootContext()->setContextProperty("qmlProperty", middleware->qmlProperty);
    engine->addImageProvider(QLatin1String("products"), middleware->productImageProvider);

    const QUrl url(QStringLiteral("qrc:/QMLFile/mainView.qml"));
    engine->load(url);

    if (engine->rootObjects().isEmpty())
        qApp->exit(-1);
}

AppStarter::~AppStarter()
{
    middleware->deleteLater();
    engine->deleteLater();
}

void AppStarter::saveQmlEngineWarnings(const QList<QQmlError> &listError)
{
    QString folder = QStandardPaths::writableLocation(QStandardPaths::DownloadLocation);
    QFile file(folder + "/qmlEngineError.txt");

    for (auto err : listError) {
        if (file.open(QIODevice::Append)) {
            QTextStream stream( &file );
            stream << "\n" << QDateTime::currentDateTime().toString()
                   << ": " << err.toString() << endl;
        }
    }

    file.close();
}
