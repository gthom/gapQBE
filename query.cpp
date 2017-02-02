#include "query.h"

query::query(dialogRelation* mum,QString nom,qreal x,qreal y, QGraphicsItem* parent, QGraphicsScene * laScene, QStringList listeDesChamps,QString requete,QString pAlias)
        :Table(mum,nom,x,y,parent,laScene,listeDesChamps)

{
    sql=requete;
    alias=pAlias;
}
