#include "arc.h"
#include "node.h"

#include <QPainter>

int Node::NODE_NUMBER=0;

Node::Node(const qreal &x, const qreal &y, const qreal &radius,const QColor& color,const int importance)
    : QObject()
    , QGraphicsEllipseItem(-radius,-radius,2*radius,2*radius)
    , id(++NODE_NUMBER)
    , myColor(color)
    , myRadius(radius)
{

    setPos(x,y);
    //setto i flag in modo tale che l'oggetto si possa muovere e invii segnali alla scena quando cambia posizione
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemSendsScenePositionChanges);
    setBrush(myColor);
    this->setZValue(importance);
}

void Node::paint(QPainter *painter, const QStyleOptionGraphicsItem * option, QWidget * p)
{
    QPen myPen = pen();
    if(isSelected()){

        setBrush(Qt::yellow);
    }
    else
    {
        setBrush(myColor);
    }

    myPen.setColor(myColor);
    painter->setPen(myPen);
    painter->setBrush(myColor);
    QGraphicsEllipseItem::paint(painter,option,p);
    painter->drawText(rect().center(),QVariant(id).toString());

}

QVariant Node::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    //se l'oggetto si è si è spostato e è connesso ad una scena(sempre per costruzione
    //però è un controllo che viene fatto per buona prassi)

    if (change == ItemPositionChange&&scene()) {
        //dico alla scena che mi sono spostato

        notifyPositionChange(this);
    }
    return QGraphicsItem::itemChange(change,value);
}

void Node::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{    notifyPositionChange(this);
    //chiamo a super perchè è lui a mettere le nuove coordinate al nodo grafico quando viene spostato
    QGraphicsEllipseItem::mouseReleaseEvent(event);
    //visto che si possono lanciare gli oggetti circa dopo che ho mollato il mouse potrebbe spostarsi l'oggetto di un pò
    //in realtà non è un vero lancio ma l'evento itemChange avviene ad un determinato frame rate quindi quando mollo il mouse potrebbe
    //non aggiornarsi questo lo obbliga ad un ultimo refresh

}

int Node::getId() const
{
    return id;
}



