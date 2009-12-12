#ifndef LIEN_H
#define LIEN_H

#include <QGraphicsLineItem>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include "table.h"
#include <QColor>
#include "types.h"



class table;
class lien : public QGraphicsLineItem
{
public:
    enum { Type = LIEN};
    int type() const
    {
        // Enable the use of qgraphicsitem_cast with this item.
        return Type;
    }
    table* t1;
    table* t2;
    lien(table* qg1,table* qg2,QGraphicsItem* parent, QGraphicsScene * laScene, QString typ="Natural");
    void updatePosition();//lorsqu'une des tables bouge, le lien doit bouger
    QGraphicsTextItem* condition;//condition de jointureex on cde.nocli=client.nocli
    QString texteDeLaCondition;//idem ci-dessus
    QString typeDeJointure;//inner, left outer, right outer, Natural
    void contextMenuEvent(QGraphicsSceneMouseEvent *event);//menu contextuel du lien
    //QString toSql();
    bool estRelieA(lien* autreLien){return ((autreLien->t1==t1) or (autreLien->t1==t2) or (autreLien->t2==t1) or (autreLien->t2==t2));};
};

#endif // LIEN_H
