#include "arc.h"
#include "graphmanager.h"
#include "node.h"

GraphManager::GraphManager():
    QGraphicsScene(),
    Nodes(QVector<Node*>()),
    Arcs(QList<QGraphicsLineItem*>())
{

    addNodes(20,20);
    addNodes(50,50);
    //nodo 1 è rosso nodo 2 è nero
    Nodes[0]->setPen(QPen(QColor(Qt::red)));
    addLineBetween(Nodes[0],Nodes[1]);
    addLineBetween(Nodes[1],Nodes[0]);

}

void GraphManager::addNodes(const qreal &x, const qreal &y)
{
    Node* t=new Node(x,y,Radius);
    Nodes.push_back(t);
    this->addItem(t);
}

bool GraphManager::addLineBetween(Node *Node1, Node *Node2)
{
    //se i nodi esistono nella mia lista di nodi(non si sa mai)
    int pos1=Nodes.indexOf(Node1),pos2=Nodes.indexOf(Node2);
    //ritorna -1 se non esiste
    bool nodesExists=(pos1>=0||pos2>=0);
    if(nodesExists)
    {
        //creo la linea e aggiungo ai due nodi i punti
        //safe cast sono sottoclassi
        Arc *temp=new Arc((QGraphicsItem*)Nodes.at(pos1),(QGraphicsItem*)Nodes.at(pos2));

        Nodes.at(pos1)->addLine(temp);
        Nodes.at(pos2)->addLine(temp);
        Arcs.push_back(temp);
        this->addItem(temp);
        temp->updatePosition();
    }
    //se i nodi esistono l'operazione ha successo altrimenti no
    return nodesExists;
}
