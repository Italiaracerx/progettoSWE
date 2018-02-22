#include "graphmanager.h"
#include "graphprinter.h"
#include "mainwindow.h"
#include "iostream"
#include <QGraphicsView>
#include <QPushButton>
#include <QLayout>
//QGraphicsScene è del model serve solo a gestire i nodi non ha resa grafica
//QGraphicsView renderizza gli oggetti descritti in una scene


MainWindow::MainWindow(QWidget *parent, GraphManager &Scene)
    : QMainWindow(parent),
      GraphTable(new GraphPrinter(this)),
      ButtonNode(new QPushButton("Nodino ++",this)),
      ButtonArc(new QPushButton("Archetti ++",this)),
      Model(&Scene)
{
    //dico alla View che disegna chi è il suo model
    GraphTable->setScene(&Scene);
    //prendo il layout della pagina principale e la metto a schermo pieno
    QLayout* l=layout();
    l->setSpacing(0);
    l->setContentsMargins(0, 0, 0, 0);
    //dico che il il grafo è centrato nella pagina principale e lo aggiungo al layout
    this->setCentralWidget(GraphTable);
    ButtonArc->move(100,0);
    connect(ButtonNode,SIGNAL(clicked(bool)),this,SLOT(newNode()));
    connect(ButtonArc,SIGNAL(clicked(bool)),this,SLOT(newArc()));

}

MainWindow::~MainWindow()
{

}

void MainWindow::newNode()
{
    Model->addNodes(10,10);
}

void MainWindow::newArc()
{
    First=0;
    Model->clearSelection();
    connect(Model,SIGNAL(selectionChanged()),this,SLOT(addItem()));
}

void MainWindow::addItem()
{
    if(!First)
    {
        if(Model->selectedItems().size()>0)
        First=(Node*)Model->selectedItems()[0];
    }
    else
    {

        if(Model->selectedItems().size()>0){
        Model->addLineBetween(First,(Node*)Model->selectedItems()[0]);
        disconnect(Model,SIGNAL(selectionChanged()),this,SLOT(addItem()));
        First=0;
        }
    }
}
