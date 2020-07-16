#ifndef QSALESSPLASHSCREEN_H
#define QSALESSPLASHSCREEN_H

#include <QSplashScreen>
#include <QObject>

namespace Gui::Loader {

class QSalesSplashScreen : public QSplashScreen
{
    Q_OBJECT
public:
    QSalesSplashScreen(const QPixmap &pixmap = QPixmap());
    QSalesSplashScreen() = delete;
    ~QSalesSplashScreen() = default;

    void setSplashMessage(QString);
    void showSplashScreen();

private:
    void setStyle();
};

}

#endif // QSALESSPLASHSCREEN_H
