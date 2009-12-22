#include "table.h"
#include <QFontMetrics>
#include <QAction>
#include <QGraphicsWidget>
#include<QGraphicsSceneContextMenuEvent>
#include <QGraphicsItem>
#include <QMenu>
#include <QDebug>
#include "field.h"
#include <QInputDialog>


table::table(dialogRelation* mum,QString nom,qreal x,qreal y, QGraphicsItem* parent, QGraphicsScene * laScene,QStringList listeDesChamps)
        :maman(mum),QGraphicsRectItem(x,y,200,200,parent,laScene)

{

    nomTable=nom;
    alias="";
    //le titre
    title=new QGraphicsTextItem(this);
    title->setFont(QFont("Verdana",10,QFont::Bold,false));
    //déterminons la largeur de la table:
    long largeurMaxi=QFontMetrics(title->font()).width(nomTable);
    for(int noChamp=0;noChamp<listeDesChamps.count();noChamp++)
    {
        long largeurDuChamp=QFontMetrics(title->font()).width(listeDesChamps[noChamp]);
        if (largeurDuChamp>largeurMaxi) largeurMaxi=largeurDuChamp;
    }
    //construction du QGraphicsRectItem
    setRect(x,y,largeurMaxi+10,200);
    //création du titre
    setBrush(QColor("#FFFF00"));//jaune
    title->setPos(0,0);//par rapport à son parent
    title->setTextWidth(boundingRect().width());
    title->setHtml("<center>"+nomTable+"</center>");

    //stockage de quelques infos
    //c'est une table
    title->setData(32,"Table");
    //on stocke son nom
    title->setData(33,nomTable);
    setData(32,"Table");
    setData(33,nomTable);
    long ordonne=title->boundingRect().height();
    //ajout d'une ligne sous le titre
    laLigne=new QGraphicsLineItem(0,ordonne,boundingRect().width(),ordonne,this,laScene);
    this->setRect(0,0,largeurMaxi+10,ordonne+10);
    //création des champs dans la table
    for(int noChamp=0;noChamp<listeDesChamps.count();noChamp++)
    {
        vecteurChamps.push_back(new field(maman,false,laScene,listeDesChamps[noChamp],this));
        vecteurChamps[noChamp]->setPos(10,ordonne);
        //les champs d'origine ne peuvent être modifiés
          //vecteurChamps[noChamp]->setTextInteractionFlags(Qt::TextEditable);
        vecteurChamps[noChamp]->setData(32,"Field");
        vecteurChamps[noChamp]->setData(33,nom+"."+listeDesChamps[noChamp]);
        ordonne+=vecteurChamps[noChamp]->boundingRect().height();
        this->setRect(0,0,largeurMaxi+20,ordonne+10);
    }
}



 void table::contextMenuEvent(QGraphicsSceneMouseEvent *event)
 {
     //ce qui se passe lorsque le menu contextuel de la table est appelé
     qDebug()<<"void table::contextMenuEvent(QGraphicsSceneMouseEvent *event)";
     QMenu menu;
     //si je n'était pas sélectionnée, je le deviens
     this->setSelected(true);
     //création des actions du menu
     QAction *removeAction = menu.addAction(QObject::tr("&Remove"));
     QObject::connect(removeAction, SIGNAL(triggered()),maman, SLOT(tableSupprimer()));
     QAction *addFreeFieldAction = menu.addAction(QObject::tr("&Add free Field"));
     QAction *removeOrAddAliasAction;
     if(this->alias!="")
     removeOrAddAliasAction=menu.addAction(QObject::tr("&Remove alias"));
     else
     removeOrAddAliasAction=menu.addAction(QObject::tr("&Add alias"));
     //exécution du menu
     QAction * actionChoisie=menu.exec(event->screenPos());
     if(actionChoisie==addFreeFieldAction)
     {
         maman->tableAjouterChamp(this);
     }
     else
     {
         if(actionChoisie==removeOrAddAliasAction)
         {
             if(alias!="")
             {
                 alias="";
                 this->title->setHtml(nomTable);
                 maman->miseAJourResultat();
             }
             else
             {
                 bool ok;
                 QString candidat=QInputDialog::getText(maman, QObject::tr("Give alias name"),
                                          QObject::tr("Alias:"), QLineEdit::Normal,
                                          this->nomTable+"1", &ok);
                 if(ok)
                 {
                     alias=candidat;
                     this->title->setHtml(nomTable+" as "+alias);
                     maman->miseAJourResultat();
                 }
             }
         }
     }

 }

QVariant table::itemChange(GraphicsItemChange change,const QVariant &value)

{
    if (change == QGraphicsItem::ItemPositionChange) {
         foreach (lien *leLien, vectLiens) {
             leLien->updatePosition();
         }
     }

     return value;
}






