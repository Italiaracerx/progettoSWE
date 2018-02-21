#include "graphmanager.h"
#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GraphManager Model;
    MainWindow w(0,Model);
    w.show();

    return a.exec();
}
