#ifndef ARC_H
#define ARC_H

#include <QGraphicsLineItem>


class Node;
class QGraphicsItem;
class Arc: public QGraphicsLineItem
{
public:
    enum NodePoint
    {
        start=0,
        end=1,
    };
    QRectF boundingRect() const;
    Arc(int startNode, int endNode, QGraphicsItem* parent=0);
    //metodo che definisce la forma della freccia la punta bisogna definirla a mano
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *,QWidget *);
   //da chiamare per fare l'update della freccia in modo che punti in maniera coerente
    void updatePosition(const Arc::NodePoint,const QPointF& end);
    int getNodeId(NodePoint x)const ;
    //segnala ritorna l'item indicato start o end
    bool operator==(const Arc& item)const;
    //   QPainterPath shape() const;
    QPainterPath shape() const;
private:

    const static int ARROW_HEIGHT=8;
    QPolygonF arrowHead;
    //colore della freccia, da chi parte e dove arriva
    const QColor myColor;
    int starting;
    int ending;
    bool nodeCollides;

};

#endif // ARC_H
