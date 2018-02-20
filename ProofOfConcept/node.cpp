#include "node.h"

Node::Node(const qreal &x, const qreal &y, const qreal &diameter,QGraphicsScene &Scene):
    QGraphicsEllipseItem(x,y,diameter,diameter),
    MyLines(QList<QGraphicsLineItem*>())
{
    //setto i flag in modo tale che l'oggetto si possa muovere e invii segnali alla scena quando cambia posizione
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemSendsScenePositionChanges);
    //aggiungo il nodo alla scena
    Scene.addItem(this);
}

QVariant Node::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    //se l'oggetto si è spostato o la linea è incoeremente posizionata
    if (change == ItemPositionChange) {
        //ottengo il nuovo punto dell'oggetto
        setNewCenterPoint(value.toPointF());
    }
    return QGraphicsItem::itemChange(change, value);
}

void Node::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsEllipseItem::mouseReleaseEvent(event);
    setNewCenterPoint(QPoint(this->x(),this->y()));
}

void Node::addLine(QGraphicsLineItem *line, bool Point1)
{
    MyLines.push_back(line);
    IsPoint1=Point1;
    setNewCenterPoint(QPoint(this->x(),this->y()));
}
bool Node::removeLine(QGraphicsLineItem *line)
{
    MyLines.removeAll(line);
}

void Node::setNewCenterPoint(const QPointF& Position){
            // Muove la posizione dall'angolo del quadrato al centro
            int offset = rect().x() + rect().width()/2;
            const QPoint point =QPoint(this->x()+ offset,this->y() + offset);
            // Muove tutti i punti di linee riferite a lui
            for(QList<QGraphicsLineItem*>::iterator i=MyLines.begin();i<MyLines.end();++i)
            {
                if(IsPoint1)

                    (*i)->setLine(QLineF((*i)->line().p1(),point));
                else

                    (*i)->setLine(QLineF(point,(*i)->line().p2()));
            }
}
