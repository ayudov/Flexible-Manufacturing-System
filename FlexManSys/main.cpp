#include "mainwindow.h"
#include <QApplication>
#include <Billet.h>
#include <Operation.h>
using namespace OperationNameSpace;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
