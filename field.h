#ifndef FIELD_H
#define FIELD_H

#include <QGraphicsTextItem>
#include <QGraphicsPixmapItem>
#include "types.h"

class field : public QGraphicsTextItem
{

public:
    enum { Type = FIELD};
    int type() const
    {
        // Enable the use of qgraphicsitem_cast with this item.
        return Type;
    }
    field(bool,QGraphicsScene* pScene,QString pName="'something'",QGraphicsItem* pParent=0);
    bool affiche;
    QGraphicsPixmapItem * oeil;
    QGraphicsPixmapItem * iconSort;
    QGraphicsTextItem * cond;
    QGraphicsLineItem * trait;
    void contextMenuEvent(QGraphicsSceneMouseEvent *event);
    bool freeField;
    enum typeDeTri{noSort,ascSort,descSort} tri;
    QString getTri();
};

#endif // FIELD_H
