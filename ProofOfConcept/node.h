#ifndef NODE_H
#define NODE_H

#include <QGraphicsScene>
#include <qgraphicsitem.h>
class Arc;

class Node : public QGraphicsEllipseItem
{
public:
    //costruisco un nodo  dato un l'angolo superiore sinistro del quadrato in cui è inscritto e il diametro del cerchio, e la dove verrà disegnato
    Node (const qreal& x, const qreal& y, const qreal& diameter);
    //probabilmente sarebbe meglio chiedere delle coordinate del centro e poi costruire tutto conoscendo
    //forse lo faro in seguito

    //metodo chiamato quando l'item cambia posizione
    //ridefinisco affichè aggiorni la posizione della linea collegata
    //ritorna la sua nuova posizione
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
    //ridefinito per problemi se "lancio" l'oggetto
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

    //aggiunto una nuova linea con un punto che parte da questo oggetto
    void addLine(Arc *line, bool Point1=true);
    //todo in maniera decente
    bool removeLine(Arc *line);
    QPointF pos() const;
private:
    void updateArcs();
    QVector<Arc*> MyArcs;
};
#endif // NODE_H
