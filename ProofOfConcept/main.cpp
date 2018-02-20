#include "mainwindow.h"
#include "node.h"
#include <QApplication>
#include <qgraphicsitem.h>
#include <qgraphicsscene.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QGraphicsScene S;
    Node* t=new Node(0,0,50,S);
    Node* t2=new Node(0,0,50,S);
    QGraphicsLineItem *Line=S.addLine(0,0,0,0);
    t->addLine(Line);
    t2->addLine(Line,0);
    MainWindow w(0,S);
    w.show();

    return a.exec();
}
