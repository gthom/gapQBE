#include "field.h"
#include <QMenu>
#include <QAction>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsLineItem>
#include <QDebug>
#include <QTextDocument>

field::field(dialogRelation* mum ,bool isFree,QGraphicsScene* pScene,QString pName,QGraphicsItem* pParent)
    :QGraphicsTextItem(pName,pParent,pScene)
{
    maman=mum;
    nomInitial=pName;
    //affichage de l'oeil fermé: le champ n'est pas affiché
    affiche=false;
    oeil=new QGraphicsPixmapItem(QPixmap(":/mini-eye.xpm"),this,pScene);
    oeil->setPos(-20,5);
    oeil->setVisible(affiche);//false puisque non affiché
    freeField=isFree;
    //affichage du tri
    tri=noSort;//pas de tri sur le champ
    iconSort=new QGraphicsPixmapItem(QPixmap(),this,pScene);
    iconSort->setPos(-8,5);
    //pas de condition sur le champ pour l'instant genre ='Dupond' ou <123
    cond=NULL;
    connect(document(),SIGNAL(contentsChanged()),this,SIGNAL(jAiChange()));
    connect(this, SIGNAL(jAiChange()),maman , SLOT(miseAJourResultat()));

}
void field::contextMenuEvent(QGraphicsSceneMouseEvent *event)
{
    //ce qui se passe lorsque le menu contextuel du champ est appelé
    qDebug()<<"void field::contextMenuEvent(QGraphicsSceneMouseEvent *event)";
    QMenu menu;
    //si je n'était pas sélectionnée, je le deviens
    this->setSelected(true);
    //création des actions du menu
    if(freeField)
        QAction *removeAction = menu.addAction(tr("&Remove"));

    QAction *afficherAction = menu.addAction(tr("&Display(on/off)"));
    //affichage conditionnel du menu concernant les conditions
    QAction *addCondAction;
    QAction *removeCondAction;
    if(cond==NULL)
    {
        addCondAction= menu.addAction(tr("&AddCondition"));
    }
    else
    {
        removeCondAction= menu.addAction(tr("&removeCondition"));
    }
    //fin affichage du menu concernant les conditions
    QAction *choisirCritereDeTriAction=menu.addAction(tr("Sort(asc,desc,off)"));
    //exécution du menu
    QAction* actionChoisie=menu.exec(event->screenPos());
    if(actionChoisie!=NULL)
    {
        //qlq chose a été fait
        if (actionChoisie==afficherAction)
        {
            this->affiche=!this->affiche;
            this->oeil->setVisible(this->affiche);
        }
        else
        {
            if(actionChoisie==choisirCritereDeTriAction)
            {
                QMenu menu2;
                QAction * asc=menu2.addAction(tr("&Asc"));
                QAction * desc=menu2.addAction(tr("&Desc"));
                QAction * off=menu2.addAction(tr("&Off"));
                QAction* triChoisi=menu2.exec(event->screenPos());
                if(triChoisi==asc)
                {
                    tri=ascSort;
                }
                else
                {
                    if(triChoisi==desc)
                    {
                        tri=descSort;
                    }
                    else
                    {
                        if(triChoisi==off)
                        {
                            tri=noSort;
                        }
                    }
                }
                QString icon;
                switch(tri)
                {
                case noSort:icon="";break;
                case ascSort:icon=":/upSort.xpm";break;
                case descSort:icon=":/downSort.xpm";break;
                }
                this->iconSort->setPixmap(QPixmap(icon));

            }
            else
            {
                if(actionChoisie==addCondAction)
                {
                    //faire une zone de saisie pour l'action
                    //et le trait et l'opérateur
                    //is null is not null
                    //= < > <>
                    cond=new QGraphicsTextItem(tr("=\"something\""),this,scene());
                    QObject::connect(cond->document(),SIGNAL(contentsChanged()),maman, SLOT(miseAJourResultat()));
                    cond->setPos(100+this->boundingRect().width(),0);//QFontMetrics(cond->font()).height()/2);
                    cond->setTextInteractionFlags(Qt::TextEditable);
                    //et le trait
                    trait=new QGraphicsLineItem(this->pos().x()+this->boundingRect().width(),QFontMetrics(cond->font()).height()/2,cond->pos().x(),cond->pos().y()+QFontMetrics(cond->font()).height()/2,this, scene());
                }
                else
                {
                    if(actionChoisie==removeCondAction) //suppression d'une condition sur un champ
                    {
                        delete cond;
                        cond=NULL;
                        //effacer le trait aussi
                        delete trait;

                    }
                }
            }
        }

        emit jAiChange();
    }//fi du si qlq chose a ete fait
}
QString field::getTri()
{
    QString resultat;
            switch(tri)
            {
                case noSort:resultat="";break;
                case ascSort:resultat="ASC";break;
                case descSort:resultat="DESC";break;
            }
            return resultat;
}
