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


class Lien;
class Field;
class dialogRelation;
class Table : public QGraphicsRectItem
{
public:

    enum { Type = TABLE};
    int type() const
    {
        // Enable the use of qgraphicsitem_cast with this item.
        return Type;
    }
    Table(dialogRelation* mum,QString nom,qreal x,qreal y, QGraphicsItem* parent, QGraphicsScene * laScene, QStringList listeDesChamps);
    ~Table();
    QGraphicsTextItem* title;//le titre
    QGraphicsLineItem* laLigne;//la ligne sous le titre ui
    QString nomTable;//nom de la table
    QString getNomTable(){return (alias.isEmpty())?nomTable:alias;}
    QString alias;  //nom d'alias
    QVector<Lien*> vectLiens;//les liens qui la touchent.
    QVector<Field *> vecteurChamps;//ses champs
    void contextMenuEvent(QGraphicsSceneMouseEvent *event);//demande de menu contextuel
    QVariant itemChange(GraphicsItemChange change,const QVariant &value);//qd la table change
    dialogRelation* maman;// lien vers la maman
    QPolygonF polygon(){return QPolygonF(this->boundingRect());}
    QString nomTableTronque(){return (nomTable.length()>13)?nomTable.left(10)+"...":nomTable;}
};

#endif // TABLE_H
