#ifndef NODE_H
#define NODE_H

#include <QGraphicsScene>
#include <qgraphicsitem.h>
class Arc;

class Node : public QObject,public QGraphicsEllipseItem
{
    Q_OBJECT
public:
    //costruisco un nodo  dato un l'angolo superiore sinistro del quadrato in cui è inscritto e il diametro del cerchio, e la dove verrà disegnato
    Node (const qreal& x, const qreal& y, const qreal& radius, const QColor &color, const int importance=1);
    //probabilmente sarebbe meglio chiedere delle coordinate del centro e poi costruire tutto conoscendo
    //forse lo faro in seguito
    //ridefinisco paint per stampare l'info al centro del nodo
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *,QWidget *);
    //metodo chiamato quando l'item cambia posizione
    //ridefinisco affichè aggiorni la posizione della linea collegata
    //ritorna la sua nuova posizione
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
    //ridefinito per problemi se "lancio" l'oggetto
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    //aggiunto una nuova linea con un punto che parte da questo oggetto
    int getId()const;
private:
    static int NODE_NUMBER;
    const int id;
    QColor myColor;
    const qreal myRadius;
    void updateArcs();
signals:
    void notifyPositionChange(const Node* Id);
};
#endif // NODE_H
