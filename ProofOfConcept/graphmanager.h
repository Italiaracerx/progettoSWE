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

    void addNodes(const qreal& x,const qreal& y);
    bool addLineBetween(Node* Node1,Node* Node2);
    GraphManager();
    //right click event
    void contextMenuEvent(QContextMenuEvent *ce);
    //non chiedete cosi sono di grandezza decente e nella documentazione c'e scritto qreal senza una vera unità di misura
    //mi documenterò meglio
    const static int NODES_DIAMETER=50;
private:

    QVector<Node*> Nodes;
    QList<QGraphicsLineItem*> Arcs;

};

#endif // GRAPHMANAGER_H
