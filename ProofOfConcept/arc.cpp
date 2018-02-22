#include "arc.h"

#include <QPen>
#include <QPainter>
#include <graphmanager.h>
Arc::Arc(const QGraphicsItem *start, const QGraphicsItem *end, QGraphicsItem *parent):
    QGraphicsLineItem(parent),
    starting(start),
    ending(end),
    myColor(Qt::black)
{
    setPen(QPen(myColor));
    //ha la priorità piu bassa viene mostrato sotto di tutto
    this->setZValue(-1);
}


void Arc::updatePosition()
{
    //creo la linea e la imposto
    //questa soluzione per trovare i punti è buona ma pesante come un mattone il problema è che ritornare la pos degli
    //oggetti stessi pare non funzionare quindi devo mapparli
    //questo porta a mappare 2 volte se sto muovendo l'oggetto, qui e per disegnarlo
    QLineF line(mapFromItem(starting,starting->boundingRect().center()),mapFromItem(ending,ending->boundingRect().center()));
    setLine(line);
}


void Arc::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    //se i due cerchi si sovrappongono non disegno nulla
    if (starting->collidesWithItem(ending))
            return;
    //altrimenti prendo le cose che mi servono
    QPen myPen = pen();
    myPen.setColor(myColor);
    painter->setPen(myPen);
    painter->setBrush(myColor);
    //eeeee
    //Pura Matematica per calcolare i 3 punti della freccia have fun
    //mette la punta della freccia sulla circonferenza nello stesso punto del'intersezione della retta
    QPointF arrowPoint(
                line().p2().x()-cos((line().angle()/360)*M_PI*2)*(GraphManager::NODES_DIAMETER/2),
                line().p2().y()+sin((line().angle()/360)*2*M_PI)*(GraphManager::NODES_DIAMETER/2)
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
    //disegna la linea
    painter->drawLine(line());
    //disegna la freccia
    painter->drawPolygon(arrowHead);
}

QRectF Arc::boundingRect() const
{
    qreal width=(ARROW_HEIGHT+pen().width())/2.0;
    //la ingrosso la hit box e render box della freccia
    return QRectF(line().p1(),line().p2())
            .normalized()
            .adjusted(-width,-width,width,width);
}
