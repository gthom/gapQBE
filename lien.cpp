#include "lien.h"
#include <QDebug>
#include <QAction>
#include <QMenu>
#include <QTextDocument>

lien::~lien()
{
    qDebug()<<"ddestructeur du lien";
    if(condition!=NULL)
        delete condition;
}

lien::lien(table* pt1,table* pt2,QGraphicsItem * parent,QGraphicsScene* laScene,QString typ):QGraphicsLineItem(pt1->pos().x()+pt1->boundingRect().width()/2,pt1->pos().y(),pt2->pos().x()+pt2->boundingRect().width()/2,pt2->pos().y(),parent,laScene)
{
    //constructeur du lien
    t1=pt1;
    t2=pt2;
    this->setFlag(QGraphicsItem::ItemIsSelectable,true);
    if(typ!="Natural")
    {
        condition=new QGraphicsTextItem(this);
        condition->setData(32,"Lien");
        QObject::connect(condition->document(),SIGNAL(contentsChanged()),t1->maman, SLOT(miseAJourResultat()));
        condition->setHtml(t1->nomTable+".xxx="+t2->nomTable+".yyy");
        QPoint position=boundingRect().center().toPoint();
        position.setX(position.x()-QFontMetrics(condition->font()).width(condition->toPlainText())/2);
        condition->setPos(position);
        condition->setDefaultTextColor(Qt::red);
        condition->setTextInteractionFlags(Qt::TextEditable);
    }
    else
        condition=NULL;
    this->typeDeJointure=typ;
    setData(32,"Lien");
    //aspect différent en fonction du type de jointure:
    if(typ=="Natural")
    {

        this->setPen(QPen(QColor("green")));


    }
    else
    {
        if(typ=="Inner")
        {
            this->setPen(QPen(QColor("blue")));
        }
        //etc pour les autre types de jointure
    }
}
void lien::updatePosition()
{
    this->setLine(t1->pos().x()+t1->boundingRect().width()/2,t1->pos().y(),t2->pos().x()+t2->boundingRect().width()/2,t2->pos().y());
    //changer la place de la condition de jointure
    if(this->typeDeJointure!="Natural")
    {
        QPoint position=boundingRect().center().toPoint();
        position.setX(position.x()-QFontMetrics(condition->font()).width(condition->toPlainText())/2);
        condition->setPos(position);
    }
}
void lien::contextMenuEvent(QGraphicsSceneMouseEvent *event)
{
    //ce qui se passe lorsque le menu contextuel de la table est appelé
     qDebug()<<"void lien::contextMenuEvent(QGraphicsSceneMouseEvent *event)";
     QMenu menu;
     //si je n'était pas sélectionnée, je le deviens
     this->setSelected(true);
     //création des actions du menu
     QAction *removeAction = menu.addAction(QObject::tr("&Remove"));
     QAction *changeJoinType = menu.addAction(QObject::tr("&Change join type"));
     //exécution du menu et récupération de l'action choisie
     QAction * actionChoisie=menu.exec(event->screenPos());

     if(actionChoisie==changeJoinType) t1->maman->changeJoinType(this);
     else
      {
         //autre choix du menu
         if(actionChoisie==removeAction) t1->maman->supprimerLien(this);
      }  
}
void lien::updateType()
{//mise à jour du type de jointure
    if(typeDeJointure!="Natural")
    {
        if(condition==NULL)
        {
        condition=new QGraphicsTextItem(this);
        condition->setData(32,"Lien");
        QObject::connect(condition->document(),SIGNAL(contentsChanged()),t1->maman, SLOT(miseAJourResultat()));
        condition->setHtml(t1->nomTable+".xxx="+t2->nomTable+".yyy");
        QPoint position=boundingRect().center().toPoint();
        position.setX(position.x()-QFontMetrics(condition->font()).width(condition->toPlainText())/2);
        condition->setPos(position);
        condition->setDefaultTextColor(Qt::red);
        condition->setTextInteractionFlags(Qt::TextEditable);
        }
    }
    else
    {
        if(condition!=NULL) delete condition;
        condition=NULL;
    }
    //aspect différent en fonction du type de jointure:
    if(typeDeJointure=="Natural")
    {

        this->setPen(QPen(QColor("green")));


    }
    else
    {
        if(typeDeJointure=="Inner")
        {
            this->setPen(QPen(QColor("blue")));
        }
        //etc pour les autre types de jointure
    }
}


