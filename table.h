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
class field;
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
    QGraphicsTextItem* title;//le titre
    QGraphicsLineItem* laLigne;//la ligne sous le titre ui
    QString nomTable;//nom de la table
    QString alias;  //nom d'alias
    QVector<lien*> vectLiens;//les liens qui la touchent.
    QVector<field *> vecteurChamps;//ses champs
    void contextMenuEvent(QGraphicsSceneMouseEvent *event);//demande de menu contextuel
    QVariant itemChange(GraphicsItemChange change,const QVariant &value);//qd la table change
    dialogRelation* maman;// lien vers la maman

};

#endif // TABLE_H
