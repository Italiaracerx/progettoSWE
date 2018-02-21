#include "arc.h"

#include <QPen>
#include <QPainter>

Arc::Arc(const QGraphicsItem *start, const QGraphicsItem *end, QGraphicsItem *parent):
    QGraphicsLineItem(parent),
    starting(start),
    ending(end),
    myColor(Qt::black)
{
    setPen(QPen(myColor));
}
QPainterPath Arc::shape() const
{
    QPainterPath path = QGraphicsLineItem::shape();
    path.addPolygon(arrowHead);
    return path;
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
    if (starting->collidesWithItem(ending))
            return;
    QPen myPen = pen();
    myPen.setColor(myColor);
    qreal arrowSize = 10;
    painter->setPen(myPen);
    painter->setBrush(myColor);
    double angle = std::atan2(-line().dy(), line().dx());
    //Pura Matematica per calcolare i 3 punti have fun
    QPointF arrowPoint(
                line().p2().x()-cos((line().angle()/360)*M_PI*2)*25,
                line().p2().y()+sin((line().angle()/360)*2*M_PI)*25
                );

    QPointF arrowP1 = arrowPoint    - QPointF(sin(angle + M_PI / 3) * arrowSize,
                                        cos(angle + M_PI / 3) * arrowSize);
    QPointF arrowP2 = arrowPoint - QPointF(sin(angle + M_PI - M_PI / 3) * arrowSize,
                                        cos(angle + M_PI - M_PI / 3) * arrowSize);

    arrowHead.clear();
    arrowHead << arrowPoint << arrowP1 << arrowP2;
    painter->drawLine(line());
    painter->drawPolygon(arrowHead);
}
