#include "mainwindow.h"

#include <QGraphicsView>
#include <QVBoxLayout>
//QGraphicsScene è del model serve solo a gestire i nodi non ha resa grafica
//QGraphicsView renderizza gli oggetti descritti in una scene


MainWindow::MainWindow(QWidget *parent, QGraphicsScene &Scene)
    : QMainWindow(parent),GraphTable(new QGraphicsView(this))
{
    //dico alla View che disegna chi è il suo model
    GraphTable->setScene(&Scene);
    //prendo il layout della pagina principale e la metto a schermo pieno
    QLayout* l=layout();
    l->setSpacing(0);
    l->setContentsMargins(0, 0, 0, 0);
    //dico che il il grafo è centrato nella pagina principale e lo aggiungo al layout
    this->setCentralWidget(GraphTable);
}

MainWindow::~MainWindow()
{

}
