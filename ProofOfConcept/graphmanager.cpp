#include "arc.h"
#include "graphmanager.h"
#include "node.h"
#include "iostream"
#include <QContextMenuEvent>
#include <qmenu.h>
#include <algorithm>
#include <iterator>
#include <qDebug>
GraphManager::GraphManager():
    QGraphicsScene(),
    Nodes(QVector<Node*>()),
    Arcs(QVector<Arc*>())
{
    //Per mostrare 3 nodi all inizio
    addNodes(200,200);
    addNodes(50,50);
    addNodes(70,20);
    addLineBetween(Nodes[0],Nodes[1]);
    addLineBetween(Nodes[1],Nodes[0]);
    addLineBetween(Nodes[2],Nodes[1]);
    addLineBetween(Nodes[2],Nodes[0]);
}

GraphManager::~GraphManager()
{
    //cancello le liste
    for(QVector<Node*>::iterator i=Nodes.begin();i!=Nodes.end();++i)
        delete (*i);
    for(QVector<Arc*>::iterator i=Arcs.begin();i!=Arcs.end();++i)
        delete (*i);
}

GraphManager::nodeMoved(const Node* node)
{
    updateArcsOfNode(node);
}

void GraphManager::addNodes(const qreal &x, const qreal &y)
{
    //randomizzo il colore
    QColor tmp;
    tmp.setRgb(qrand() % ((255 + 1) - 0) + 0,qrand() % ((255 + 1) - 0) + 0,qrand() % ((255 + 1) - 0) + 0);
    //creo il nodo e lo aggiungo alla lista
    Node* t=new Node(x,y,NODES_RADIUS,tmp);

    Nodes.push_back(t);  
    connect(t,t->notifyPositionChange,this,updateArcsOfNode);
    addItem(t);
}

bool GraphManager::addLineBetween(QGraphicsItem *Node1, QGraphicsItem *Node2)
{
    //se i nodi esistono nella mia lista di nodi
    //se trovo allora il puntatore era un nodo
    QVector<Node*>::iterator item1=std::find_if(Nodes.begin(),Nodes.end(),[Node1](const Node* item){return Node1==item;});
    QVector<Node*>::iterator item2=std::find_if(Nodes.begin(),Nodes.end(),[Node2](const Node* item){return Node2==item;});
    //ritorna -1 se non esiste
    //se esistono entrambi e sono diversi
    bool nodesExists=(item1!=Nodes.end()&&item2!=Nodes.end())&&Node1!=Node2;
    if(nodesExists)
    {
        //creo la linea e aggiungo ai due nodi i punti
        //cerco se l'arco esiste già
        bool found=false;
        for(QVector<Arc*>::const_iterator i=Arcs.constBegin();!found && i!=Arcs.constEnd();++i)
        {
            if((*i)->getNodeId(Arc::start)==(*item1)->getId()&&(*i)->getNodeId(Arc::end)==(*item2)->getId())
            {
                found=true;
            }
        }
        //se non la trovo la aggiungo altrimenti la cancello e dico all operazione che è fallita
        if(!found)
        {
            Arc* temp=new Arc((*item1)->getId(),(*item2)->getId());
            temp->updatePosition(Arc::start,(*item1)->pos());
            temp->updatePosition(Arc::end,(*item2)->pos());
            Arcs.push_back(temp);
            this->addItem(temp);
        }
        else
        {
            nodesExists=false;
        }
    }
    //se i nodi esistono l'operazione ha successo altrimenti no
    return nodesExists;
}

void GraphManager::removeFocusItem()
{

    QGraphicsItem* item=selectedItems()[0];
    QVector<Node*>::iterator Subject=std::find_if(Nodes.begin(),Nodes.end(),[item](const Node* node){return item==node;});
    if(Subject!=Nodes.end()){
        int Id=(*Subject)->getId();
        QVector<Arc*>::iterator lastValidIt = std::remove_if(Arcs.begin(),Arcs.end(),
                       [Id,this](Arc* arc)
                        {
                        const bool arcFound=arc->getNodeId(Arc::start)==Id||arc->getNodeId(Arc::end)==Id;
                        if(arcFound)
                        {
                            removeItem(arc);
                            delete arc;
                        }
                        return arcFound;
                        });
        Arcs.erase(lastValidIt, Arcs.end());
        Node * temp=*Subject;
        disconnect(temp,temp->notifyPositionChange,this,this->updateArcsOfNode);
        Nodes.erase(Subject);
        removeItem(item);
        delete (temp);
    }
    else
    {
        QVector<Arc*>::iterator Subject=std::find_if(Arcs.begin(),Arcs.end(),[item](const Arc* arc){return item==arc;});
        if(Subject!=Arcs.end()){
            Arc* temp=*Subject;
            Arcs.removeAll(temp);
            removeItem(temp);
            delete (temp);
        }
    }

}
//aggiorna gli archi del nodo
void GraphManager::updateArcsOfNode(const Node *node)
{

    int id=node->getId();
    foreach(Arc* arc,Arcs)
    {
        if(arc->getNodeId(Arc::start)==id)
        {
            arc->updatePosition(Arc::start,node->pos());
        }
        if(arc->getNodeId(Arc::end)==id)
        {
            arc->updatePosition(Arc::end,node->pos());
        }
    }
}
