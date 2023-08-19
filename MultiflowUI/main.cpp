#include "mainwindow.h"

#include <QApplication>
#include <MultiflowLibrary/core/core.h>

int main(int argc, char *argv[])
{
    ML::initialize();

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
