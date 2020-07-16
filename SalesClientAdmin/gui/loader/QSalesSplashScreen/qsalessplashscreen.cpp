#include "qsalessplashscreen.h"
#include <QIcon>

using namespace Gui::Loader;

QSalesSplashScreen::QSalesSplashScreen(const QPixmap &pixmap)
    : QSplashScreen(pixmap)
{

}

void QSalesSplashScreen::setSplashMessage(QString message)
{
    this->showMessage(message, Qt::AlignBottom | Qt::AlignCenter, Qt::black);
}


void QSalesSplashScreen::showSplashScreen()
{
    setStyle();
    this->show();
}

void QSalesSplashScreen::setStyle()
{
    this->setWindowFlag(Qt::WindowStaysOnTopHint);

    QFont font;
    font.setPixelSize(24);
    this->setFont(font);
}

