#ifndef FIELD_H
#define FIELD_H

#include <QGraphicsTextItem>
#include <QGraphicsPixmapItem>
#include "types.h"
#include "dialogrelation.h"
class dialogRelation;
class field :   public QGraphicsTextItem
{
    Q_OBJECT
private:
    dialogRelation * maman;

public:
    enum { Type = FIELD};
    int type() const
    {
        // Enable the use of qgraphicsitem_cast with this item.
        return Type;
    }
    field(dialogRelation* mum ,bool,QGraphicsScene* pScene,QString pName="'something'",QGraphicsItem* pParent=0);
    bool affiche;
    QGraphicsPixmapItem * oeil;
    QGraphicsPixmapItem * iconSort;
    QGraphicsTextItem * cond;//condition: exemple ='Dupond'
    QGraphicsLineItem * trait;//trait entre le champ et la condition
    QString nomInitial;
    void contextMenuEvent(QGraphicsSceneMouseEvent *event);
    bool freeField;
    enum typeDeTri{noSort,ascSort,descSort} tri;
    int  numeroDansLeTri;
    int numeroOrdreDansLeSelect;
    QString getTri();
    void dropEvent( QGraphicsSceneDragDropEvent* event);
    void dragEnterEvent( QGraphicsSceneDragDropEvent* event);
    void dragMoveEvent(QGraphicsSceneDragDropEvent *event);
    void ajouteCondition(QString texteCondition);
    void modifieCondition(QString);
  signals:
          void jAiChange();
};

#endif // FIELD_H
