#ifndef NODE_H
#define NODE_H

#include <QGraphicsScene>
#include <qgraphicsitem.h>


class Node : public QGraphicsEllipseItem
{
public:
    //costruisco un nodo  dato un l'angolo superiore sinistro del quadrato in cui è inscritto e il diametro del cerchio, e la dove verrà disegnato
    Node (const qreal& x, const qreal& y, const qreal& diameter, QGraphicsScene& Scene);

    //metodo chiamato quando l'item cambia posizione
    //ridefinisco affichè aggiorni la posizione della linea collegata
    //ritorna la sua nuova posizione
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
    //ridefinito per problemi se "lancio" l'oggetto
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    //aggiunto una nuova linea con un punto che parte da questo oggetto
    void addLine(QGraphicsLineItem* line,bool Point1=true);
    bool removeLine(QGraphicsLineItem *line);
private:
    //
    QList<QGraphicsLineItem*> MyLines;
    bool IsPoint1;
    QPointF LastLinePositionRegister;
    void setNewCenterPoint(const QPointF& Position);
};
#endif // NODE_H
