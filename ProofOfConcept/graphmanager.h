#ifndef GRAPHMANAGER_H
#define GRAPHMANAGER_H

#include <qgraphicsscene.h>

class Node;

class GraphManager:public QGraphicsScene
{
public:
    GraphManager();
    void addNodes(const qreal& x,const qreal& y);
    bool addLineBetween(Node* Node1,Node* Node2);
private:
    //non chiedete cosi sono di grandezza decente e nella documentazione c'e scritto qreal senza una vera unità di misura
    //mi documenterò meglio
    const static int Radius=50;
    QVector<Node*> Nodes;
    QList<QGraphicsLineItem*> Arcs;
};

#endif // GRAPHMANAGER_H
