#include "mainwindow.h"

#include <QApplication>
#include <MultiflowLibrary/core/core.h>
#include <MultiflowLibrary/logging/logging.h>
#include <MultiflowLibrary/expression/constant.h>
#include <MultiflowLibrary/expression/add.h>
#include <MultiflowLibrary/expression/variable.h>

int main(int argc, char *argv[])
{
    ml::initialize();

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    INFO << "Multiflow UI launched and entered event loop.";
    return a.exec();
}
