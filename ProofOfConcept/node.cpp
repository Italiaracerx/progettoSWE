#include "arc.h"
#include "node.h"

Node::Node(const qreal &x, const qreal &y, const qreal &diameter,const QColor& color,const int importance):
    QGraphicsEllipseItem(x,y,diameter,diameter),
    MyArcs(QVector<Arc*>())
{
    setPos(x,y);
    //setto i flag in modo tale che l'oggetto si possa muovere e invii segnali alla scena quando cambia posizione
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemSendsScenePositionChanges);
    this->setBrush(color);
    this->setZValue(importance);
}

QVariant Node::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    //se l'oggetto si è spostato incoeremente posizionata
    if (change == ItemPositionChange&&scene()) {
        //dico ai miei archi di aggiornarsi
        updateArcs();
    }
    return QGraphicsItem::itemChange(change, value);
}

void Node::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    //chiamo a super perchè è lui a mettere le nuove coordinate al nodo grafico quando viene spostato
    QGraphicsEllipseItem::mouseReleaseEvent(event);
    //visto che si possono lanciare gli oggetti circa dopo che ho mollato il mouse potrebbe spostarsi l'oggetto di un pò
    //in realtà non è un vero lancio ma l'evento itemChange avviene ad un determinato frame rate quindi quando mollo il mouse potrebbe
    //non aggiornarsi questo lo obbliga ad un ultimo refresh
    updateArcs();
}



void Node::addLine(Arc *line)
{
    //qt ha un hiding degli oggetti buono quindi non posso passare solo il punto della linea interessato perchè non riesco
    //ad accederci (sono privati quindi manco con l'ereditarietà) per questo motivo passo la linea intera e se questo nodo
    //ha il punto A o il punto B del segmento
    MyArcs.push_back(line);
    //aggiorno il punto con le mie coordinate di centro
}
bool Node::removeLine(Arc *line)
{
    //dopo aver chiamato questo starà a qualcun altro distruggere la linea
    //non lo ritengo competenza di un nodo distruggere gli archi ma del modellatore del grafo
    MyArcs.indexOf(line);
}
void Node::updateArcs()
{
    for(QVector<Arc*>::iterator i=MyArcs.begin();i!=MyArcs.end();++i)
        (*i)->updatePosition();
}
