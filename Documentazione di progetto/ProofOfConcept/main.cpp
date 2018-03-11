#include "graphmanager.h"
#include "mainwindow.h"
#include <QApplication>
#include <QTime>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //creo il modello del grafo
    GraphManager Model;
    //creo un seed per il random per generare colori a caso per i nodi
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());
    //creo la view
    MainWindow w(0,Model);
    //mostro a schermo intero
    w.showMaximized();

    return a.exec();
}
