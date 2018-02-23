#include "arc.h"
#include "graphmanager.h"
#include "node.h"
#include "iostream"
#include <QContextMenuEvent>
#include <qmenu.h>

GraphManager::GraphManager():
    QGraphicsScene(),
    Nodes(QVector<Node*>()),
    Arcs(QList<Arc*>())
{
    //Per mostrare 3 nodi all inizio
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
    //cancello le liste
    for(QVector<Node*>::iterator i=Nodes.begin();i!=Nodes.end();++i)
        delete (*i);
    for(QList<Arc*>::iterator i=Arcs.begin();i!=Arcs.end();++i)
        delete (*i);
}

void GraphManager::addNodes(const qreal &x, const qreal &y)
{
    //randomizzo il colore
    QColor tmp;
    tmp.setRgb(qrand() % ((255 + 1) - 0) + 0,qrand() % ((255 + 1) - 0) + 0,qrand() % ((255 + 1) - 0) + 0);
    //creo il nodo e lo aggiungo alla lista
    Node* t=new Node(x,y,NODES_DIAMETER,tmp);
    Nodes.push_back(t);
    this->addItem(t);
}

bool GraphManager::addLineBetween(QGraphicsItem *Node1, QGraphicsItem *Node2)
{
    //se i nodi esistono nella mia lista di nodi
    //downcastin di puntatore se trovo che un puntatore nella lista punta alla stessa area di memoria essendo partita dal sottooggetto ho
    //ho solo allargato l'area di memoria pero il punto iniziale è lo stesso
    //se trovo allora il puntatore era un nodo
    int pos1=Nodes.indexOf((Node*)Node1),pos2=Nodes.indexOf((Node*)Node2);
    //ritorna -1 se non esiste
    //se esistono entrambi e sono diversi
    bool nodesExists=(pos1>=0&&pos2>=0)&&Node1!=Node2;
    if(nodesExists)
    {
        //creo la linea e aggiungo ai due nodi i punti
        Arc *temp=new Arc(*Nodes.at(pos1),*Nodes.at(pos2));
        //cerco se l'arco esiste già
        bool found=false;
        for(QList<Arc*>::const_iterator i=Arcs.constBegin();!found && i!=Arcs.constEnd();++i)
        {
            if((*(*i))==*temp)
            {
                found=true;
            }
        }
        //se non la trovo la aggiungo altrimenti la cancello e dico all operazione che è fallita
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
    //non è sua madre buona ma in un certo senso è rtti fatto da noi
    //faccio == tra ptr quindi se puntano alla stessa area di memoria so che è un nodo perchè nodes contiene solo Nodi
    //idem per dopo
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
    //non è sua madre buona ma in un certo senso è rtti fatto da noi
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
