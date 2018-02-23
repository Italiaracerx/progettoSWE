#ifndef GRAPHMANAGER_H
#define GRAPHMANAGER_H

#include "arc.h"

#include <qgraphicsscene.h>

class Node;
class QContextMenuEvent;
class QMenu;
class QAction;
class GraphManager:public QGraphicsScene
{
    Q_OBJECT
public:
    //aggiunge un nodo alla lista
    void addNodes(const qreal& x,const qreal& y);
    //aggiunge un arco al grafo se un arco di quel tipo non esiste già e se i nodi dati sono corretti
    bool addLineBetween(QGraphicsItem* Node1,QGraphicsItem* Node2);
    //rimuove il nodo dalla lista
    void removeFocusItem();\
    void updateArcsOfNode(const Node* node);
    GraphManager();
    ~GraphManager();
    //non chiedete cosi sono di grandezza decente e nella documentazione c'e scritto qreal senza una vera unità di misura
    //mi documenterò meglio
    const static int NODES_RADIUS=25;
private:
    QVector<Node*> Nodes;
    QVector<Arc*> Arcs;
public slots:
    nodeMoved(const Node* node);

};

#endif // GRAPHMANAGER_H
