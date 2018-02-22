#include "graphmanager.h"
#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GraphManager Model;
    MainWindow w(0,Model);
    w.showMaximized();

    return a.exec();
}
