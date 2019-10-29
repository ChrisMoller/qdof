#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QCoreApplication::setOrganizationName("MSDS");
    QCoreApplication::setOrganizationDomain("mollerware.com");
    QCoreApplication::setApplicationName("QDOF");

    MainWindow w;

    return a.exec();
}
