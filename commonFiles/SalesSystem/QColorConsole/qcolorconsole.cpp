#include "qcolorconsole.h"

QColorConsole::QColorConsole()
{

}

void QColorConsole::operator <<(QDataStream &stream)
{
    stream >> currentRed;
    stream >> currentGreen;
    stream >> currentBlue;
}

void QColorConsole::operator >>(QDataStream &stream)
{
    stream << currentRed;
    stream << currentGreen;
    stream << currentBlue;
}

int QColorConsole::red() const
{
    return currentRed;
}

int QColorConsole::green() const
{
    return currentGreen;
}

int QColorConsole::blue() const
{
    return currentBlue;
}

void QColorConsole::setRed(int r)
{
    currentRed = r;
}

void QColorConsole::setGreen(int g)
{
    currentGreen = g;
}

void QColorConsole::setBlue(int b)
{
    currentBlue = b;
}

void QColorConsole::clear()
{
    currentRed = -1;
    currentBlue = -1;
    currentGreen = -1;
}
