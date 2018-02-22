#include "arc.h"

#include <QPen>
#include <QPainter>
#include <graphmanager.h>
Arc::Arc(const Node &start, const Node &end, QGraphicsItem *parent):
    QGraphicsLineItem(parent),
    starting((QGraphicsItem*)&start),
    ending((QGraphicsItem*)&end),
    myColor(Qt::black)
{

    setFlag(QGraphicsItem::ItemIsSelectable);
    setPen(QPen(myColor));
    //ha la priorità piu bassa viene mostrato sotto di tutto
    this->setZValue(10);
}


void Arc::updatePosition()
{
    //creo la linea e la imposto
    //questa soluzione per trovare i punti è buona ma pesante come un mattone il problema è che ritornare la pos degli
    //oggetti stessi pare non funzionare quindi devo mapparli
    //questo porta a mappare 2 volte se sto muovendo l'oggetto, qui e per disegnarlo
    //devo creare e settare una linea da centro a centro cosi quando paint opera riuscirà a renderizzare la linea correttamente
    QLineF line(mapFromItem(starting,starting->boundingRect().center()),mapFromItem(ending,ending->boundingRect().center()));
    setLine(line);
}

Node *Arc::getItem(NodePoint x)
{
    return x?(Node*)ending:(Node*)starting;
}

bool Arc::operator==(const Arc &item) const
{
    return starting==item.starting&&ending==item.ending;
}




void Arc::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    //se i due cerchi si sovrappongono non disegno nulla
    if (starting->collidesWithItem(ending))
            return;
    //altrimenti prendo le cose che mi servono

    QPen myPen = pen();
    if(isSelected()){

        myPen.setColor(Qt::green);
        painter->setPen(myPen);
        painter->setBrush(Qt::green);


    }
    else
    {
        myPen.setColor(myColor);
        painter->setPen(myPen);
        painter->setBrush(myColor);
    }

    //eeeee
    //Pura Matematica per calcolare i 3 punti della freccia have fun
    //mette la punta della freccia sulla circonferenza nello stesso punto del'intersezione della retta
    QPointF arrowPoint(
                line().p2().x()-cos((line().angle()/360)*M_PI*2)*(GraphManager::NODES_DIAMETER/2),
                line().p2().y()+sin((line().angle()/360)*2*M_PI)*(GraphManager::NODES_DIAMETER/2)
                );
    //mette la coda della freccia sulla circonferenza nel punto di intersezione con la retta
    QPointF arrowTail=QPointF(line().p1().x()+cos((line().angle()/360)*M_PI*2)*(GraphManager::NODES_DIAMETER/2),
                line().p1().y()-sin((line().angle()/360)*2*M_PI)*(GraphManager::NODES_DIAMETER/2)
                );
    //disegna gli altri due punti sottraendo al punt della freccia con 60° angolo
    QPointF arrowP1 = arrowPoint - QPointF(sin(line().angle()/360*M_PI*2+M_PI/3) * ARROW_HEIGHT,
                                        +cos(line().angle()/360*M_PI*2+M_PI/3) * ARROW_HEIGHT);
    QPointF arrowP2 = arrowPoint + QPointF(sin(line().angle()/360*M_PI*2-M_PI/3) * ARROW_HEIGHT,
                                        +cos(line().angle()/360*M_PI*2-M_PI/3) * ARROW_HEIGHT);
    //crea il poligono e lo setta con i nuovi 3 punti
    arrowHead.clear();
    //qvector permette di inserire cosi punti in un array
    arrowHead << arrowPoint << arrowP1 << arrowP2;
    //disegna la linea dalle due circonferenze non dai centri
    painter->drawLine(arrowTail,arrowPoint);
    //disegna la freccia
    painter->drawPolygon(arrowHead);
}

QPainterPath Arc::shape() const
{
    QPainterPath path;
    QPolygonF t;
    //sempre matematica
    QPointF arrowPoint2(
                line().p2().x()-cos((line().angle()/360)*M_PI*2)*(GraphManager::NODES_DIAMETER/2),
                line().p2().y()+sin((line().angle()/360)*2*M_PI)*(GraphManager::NODES_DIAMETER/2)
                );
    //mette la coda della freccia sulla circonferenza nel punto di intersezione con la retta
    QPointF arrowTail2=QPointF(line().p1().x()+cos((line().angle()/360)*M_PI*2)*(GraphManager::NODES_DIAMETER/2),
                line().p1().y()-sin((line().angle()/360)*2*M_PI)*(GraphManager::NODES_DIAMETER/2)
                );
    //disegna gli altri due punti sottraendo al punt della freccia con 60° angolo
    QPointF arrowP12 = arrowPoint2 - QPointF(sin(line().angle()/360*M_PI*2) * ARROW_HEIGHT/2,
                                        +cos(line().angle()/360*M_PI*2) * ARROW_HEIGHT/2);
    QPointF arrowP22 = arrowPoint2 + QPointF(sin(line().angle()/360*M_PI*2) * ARROW_HEIGHT/2,
                                        +cos(line().angle()/360*M_PI*2) * ARROW_HEIGHT/2);
    t.clear();
    t<<arrowP12<<arrowP22<<arrowTail2<<arrowP12;
    path.addPolygon(t);
    return path;

}

