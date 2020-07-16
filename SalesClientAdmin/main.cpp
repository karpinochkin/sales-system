#include <QApplication>
#include "include/QClientLoader/qclientloader.h"
#include <memory>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    auto loader = std::make_unique<QClientLoader>();
    a.setApplicationName("Sales Admin Client");

    return a.exec();
}
