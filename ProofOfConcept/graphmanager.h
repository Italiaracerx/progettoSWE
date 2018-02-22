#ifndef GRAPHMANAGER_H
#define GRAPHMANAGER_H

#include <qgraphicsscene.h>

class Node;
class QContextMenuEvent;
class QMenu;
class QAction;
class GraphManager:public QGraphicsScene
{
public:
    //aggiunge un nodo alla lista
    void addNodes(const qreal& x,const qreal& y);
    //aggiunge un arco al grafo se un arco di quel tipo non esiste già e se i nodi dati sono corretti
    bool addLineBetween(Node* Node1,Node* Node2);
    GraphManager();
    ~GraphManager();
    //non chiedete cosi sono di grandezza decente e nella documentazione c'e scritto qreal senza una vera unità di misura
    //mi documenterò meglio
    const static int NODES_DIAMETER=50;
private:
    QVector<Node*> Nodes;
    QList<QGraphicsLineItem*> Arcs;

};

#endif // GRAPHMANAGER_H
