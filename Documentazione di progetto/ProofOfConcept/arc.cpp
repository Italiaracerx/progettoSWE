#include "arc.h"

#include <QPen>
#include <QPainter>
#include <graphmanager.h>
#include <qmath.h>
QRectF Arc::boundingRect() const
{
    return QGraphicsLineItem::boundingRect().normalized().adjusted(-ARROW_HEIGHT,-ARROW_HEIGHT,ARROW_HEIGHT,ARROW_HEIGHT);
}

Arc::Arc(int start,int end, QGraphicsItem *parent):
    QGraphicsLineItem(parent),
    starting(start),
    ending(end),
    myColor(Qt::black)
{
    setLine(0,0,0,0);
    setFlag(QGraphicsItem::ItemIsSelectable);
    setPen(QPen(myColor));
    //ha la priorità piu bassa viene mostrato sotto di tutto
    this->setZValue(10);
}

void Arc::updatePosition(Arc::NodePoint node,const QPointF& newPoint)
{
    QLineF line;
    if(node==NodePoint::start)
    {
       line.setP2(this->line().p2());
       line.setP1(newPoint);
    }
       else
    {

        line.setP1(this->line().p1());
        line.setP2(newPoint);
    }
    QPointF v=line.p1()-line.p2();
    qreal x=v.x(),y=v.y();
    nodeCollides=false;
    if(((x*x)+(y*y))<=pow((2*GraphManager::NODES_RADIUS),2))
    {
        nodeCollides=true;
    }
        setLine(line);
}

int Arc::getNodeId(Arc::NodePoint x) const
{
    return x?ending:starting;
}

bool Arc::operator==(const Arc &item) const
{
    return starting==item.starting&&ending==item.ending;
}

QPainterPath Arc::shape() const
{
    QPainterPath p;
    QPolygonF head;
    QPointF point=line().p1()-line().p2();
    point=(point/qSqrt(point.x()*point.x()+point.y()*point.y()));

    //Pura Matematica per calcolare i 3 punti della freccia have fun
    QPointF orthogonal(-point.y(),point.x());
    QPointF arrowPoint=line().p2()+point*GraphManager::NODES_RADIUS;
    QPointF arrowTail=line().p1()-point*GraphManager::NODES_RADIUS;
    //disegna gli altri due punti sottraendo al punt della freccia con 60° angolo
    QPointF arrowP1 = line().p2()+point*(GraphManager::NODES_RADIUS+ARROW_HEIGHT) - orthogonal*(ARROW_HEIGHT+2);
    QPointF arrowP2 = line().p2()+point*(GraphManager::NODES_RADIUS+ARROW_HEIGHT) + orthogonal*(ARROW_HEIGHT+2);
    //crea il poligono e lo setta con i nuovi 3 punti
    head.clear();
    //creo la hitbox
    head << arrowPoint << arrowP1 << arrowPoint+point*ARROW_HEIGHT-orthogonal*2 << arrowTail-orthogonal*2<<arrowTail-+orthogonal*2<<arrowP2<<arrowHead;
    //aggiungo la hitbox
    p.addPolygon(head);
    return p;
}



void Arc::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    //se i due cerchi si sovrappongono non disegno nulla
    //devo castare perchè non posso avere la definizione di nodo nella classe
    //è la classe base anyway
    //altrimenti prendo le cose che mi servono

    if(nodeCollides)return;

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

    QPointF point=line().p1()-line().p2();
    point=(point/qSqrt(point.x()*point.x()+point.y()*point.y()));
    QPointF orthogonal(-point.y(),point.x());
    //Pura Matematica per calcolare i 3 punti della freccia have fun
    //mette la punta della freccia sulla circonferenza nello stesso punto del'intersezione della retta

    //mette la coda della freccia sulla circonferenza nel punto di intersezione con la retta
    QPointF arrowPoint=line().p2()+point*GraphManager::NODES_RADIUS;
    QPointF arrowTail=line().p1()-point*GraphManager::NODES_RADIUS;
    //disegna gli altri due punti sottraendo al punt della freccia con 60° angolo
    QPointF arrowP1 = line().p2()+point*(GraphManager::NODES_RADIUS+ARROW_HEIGHT) - orthogonal*ARROW_HEIGHT;
    QPointF arrowP2 = line().p2()+point*(GraphManager::NODES_RADIUS+ARROW_HEIGHT) + orthogonal*ARROW_HEIGHT;
    //crea il poligono e lo setta con i nuovi 3 punti
    arrowHead.clear();
    //qvector permette di inserire cosi punti in un array
    arrowHead << arrowPoint << arrowP1 << arrowP2;
    //disegna la linea dalle due circonferenze non dai centri
    painter->drawLine(arrowTail,arrowPoint);
    //disegna la freccia
    painter->drawPolygon(arrowHead);
}


