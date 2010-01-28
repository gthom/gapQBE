#ifndef QUERY_H
#define QUERY_H
#include "table.h"

class query : public table
{
public:
    query(dialogRelation* mum,QString nom,qreal x,qreal y, QGraphicsItem* parent, QGraphicsScene * laScene, QStringList listeDesChamps,QString requete,QString alias);
    QString sql;
};

#endif // QUERY_H
