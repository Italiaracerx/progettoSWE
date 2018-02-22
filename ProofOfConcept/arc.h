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
        end=1
    };
    Arc(const Node &start, const Node &end, QGraphicsItem* parent=0);
    //metodo che definisce la forma della freccia la punta bisogna definirla a mano
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *,QWidget *);
    // ridefinizione migliore della hitbox per selezionare le frecce ora è un triangolo con la base sulla freccia
    //si potrebbe fare di meglio ma appesantirebbe vedremo comunque
    QPainterPath shape() const;
    //da chiamare per fare l'update della freccia in modo che punti in maniera coerente
    void updatePosition();
    //segnala ritorna l'item indicato start o end
    Node *getItem(NodePoint);
    bool operator==(const Arc& item)const;
private:
    const static int ARROW_HEIGHT=10;
    QPolygonF arrowHead;
    //colore della freccia, da chi parte e dove arriva
    const QColor myColor;
    const QGraphicsItem *starting;
    const QGraphicsItem *ending;

};

#endif // ARC_H
