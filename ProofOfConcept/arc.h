#ifndef ARC_H
#define ARC_H

#include <QGraphicsLineItem>


class Node;
class QGraphicsItem;
class Arc: public QGraphicsLineItem
{
public:
    Arc(const QGraphicsItem * start, const QGraphicsItem * end, QGraphicsItem* parent=0);
    //metodo che definisce la forma della freccia la punta bisogna definirla a mano
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *,QWidget *);
    QRectF boundingRect() const;
    //da chiamare per fare l'update della freccia in modo che punti in maniera coerente
    void updatePosition();
private:
    const static int ARROW_HEIGHT=10;
    QPolygonF arrowHead;
    //colore della freccia, da chi parte e dove arriva
    const QColor myColor;
    const QGraphicsItem *starting;
    const QGraphicsItem *ending;

};

#endif // ARC_H
