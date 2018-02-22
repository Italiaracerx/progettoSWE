#include "arc.h"
#include "graphmanager.h"
#include "node.h"
#include "iostream"
#include <QContextMenuEvent>
#include <qmenu.h>

GraphManager::GraphManager():
    QGraphicsScene(),
    Nodes(QVector<Node*>()),
    Arcs(QList<QGraphicsLineItem*>())
{

    addNodes(20,20);
    addNodes(50,50);
    addNodes(70,20);
    addLineBetween(Nodes[0],Nodes[1]);
    addLineBetween(Nodes[1],Nodes[0]);
    addLineBetween(Nodes[2],Nodes[1]);
    addLineBetween(Nodes[2],Nodes[0]);
}

GraphManager::~GraphManager()
{
    //cancello gli elementi
    for(QVector<Node*>::iterator i=Nodes.begin();i!=Nodes.end();++i)
        delete (*i);
    for(QList<QGraphicsLineItem*>::iterator i=Arcs.begin();i!=Arcs.end();++i)
        delete (*i);
}

void GraphManager::addNodes(const qreal &x, const qreal &y)
{

    QColor tmp;
    tmp.setRgb(qrand() % ((255 + 1) - 0) + 0,qrand() % ((255 + 1) - 0) + 0,qrand() % ((255 + 1) - 0) + 0);
    Node* t=new Node(x,y,NODES_DIAMETER,tmp);
    Nodes.push_back(t);
    this->addItem(t);
}

bool GraphManager::addLineBetween(Node *Node1, Node *Node2)
{
    //se i nodi esistono nella mia lista di nodi(non si sa mai)
    int pos1=Nodes.indexOf(Node1),pos2=Nodes.indexOf(Node2);
    //ritorna -1 se non esiste
    bool nodesExists=(pos1>=0&&pos2>=0);
    if(nodesExists&&Node1!=Node2)
    {
        //creo la linea e aggiungo ai due nodi i punti
        Arc *temp=new Arc(*Nodes.at(pos1),*Nodes.at(pos2));
        //cerco se l'arco esiste già
        bool found=false;
        for(QList<QGraphicsLineItem*>::const_iterator i=Arcs.constBegin();!found && i!=Arcs.constEnd();++i)
        {
            if((*((Arc*)(*i)))==*temp)
            {
                found=true;
            }
        }
        if(!found)
        {
        Nodes.at(pos1)->addLine(temp);
        Nodes.at(pos2)->addLine(temp);
        Arcs.push_back(temp);
        this->addItem(temp);
        temp->updatePosition();
        }
        else
        {
            delete temp;
            nodesExists=false;
        }
    }
    //se i nodi esistono l'operazione ha successo altrimenti no
    return nodesExists;
}

void GraphManager::removeFocusItem()
{
    QGraphicsItem* item=selectedItems()[0];
    if(Nodes.contains((Node*)item)){
        Node* temp=(Node*)item;
        foreach(Arc* arc,temp->getArcList())
        {
            Arcs.removeAll(arc);
            arc->getItem(Arc::start)->removeLine(arc);
            arc->getItem(Arc::end)->removeLine(arc);
            removeItem(arc);
            delete arc;
        }
        Nodes.removeAll(temp);
        removeItem(temp);
        delete temp;
    }
    else if(Arcs.contains((Arc*)item))
    {
        Arc* temp=(Arc*)item;
        Arcs.removeAll(temp);
        temp->getItem(Arc::start)->removeLine(temp);
        temp->getItem(Arc::end)->removeLine(temp);
        removeItem(temp);
        delete temp;
    }

}
