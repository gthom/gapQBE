#ifndef TABLE_H
#define TABLE_H
#include <QObject>
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QGraphicsSceneMouseEvent>
#include "lien.h"
#include "dialogrelation.h"
#include "types.h"
#include "field.h"


class lien;
class dialogRelation;
class table : public QGraphicsRectItem
{





public:

    enum { Type = TABLE};

    int type() const
    {
        // Enable the use of qgraphicsitem_cast with this item.
        return Type;
    }

    table(dialogRelation* mum,QString nom,qreal x,qreal y, QGraphicsItem* parent, QGraphicsScene * laScene, QStringList listeDesChamps);
    QGraphicsTextItem* title;
    QGraphicsLineItem* laLigne;
    QString nomTable;
    QVector<lien*> vectLiens;
    QVector<field *> vecteurChamps;
    void contextMenuEvent(QGraphicsSceneMouseEvent *event);
    QVariant itemChange(GraphicsItemChange change,const QVariant &value);
    dialogRelation* maman;

};

#endif // TABLE_H
