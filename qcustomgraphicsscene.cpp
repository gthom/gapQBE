#include "qcustomgraphicsscene.h"
#include <QGraphicsItem>
#include <QDrag>
#include <QDebug>
#include "query.h"
#include "table.h"
#include "field.h"
#include "types.h"
#include "ui_dialogrelation.h"
#include <QMenu>
#include <QAction>
#include <QInputDialog>

QCustomGraphicsScene::QCustomGraphicsScene(QWidget * parent):QGraphicsScene(parent)
{
 outil="move";
}
void QCustomGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{

    qDebug("void QCustomGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)");
    if (mouseEvent->button() == Qt::LeftButton
        && (itemAt(mouseEvent->scenePos())!=NULL))
    {
        //trouver l'objet à la position:

        QGraphicsItem * elt=itemAt(mouseEvent->scenePos());
        elt->setSelected(!elt->isSelected());
        if(outil=="drag")
        {
            if(!(elt->data(32).toString()=="Field"))
            {
            QDrag *drag = new QDrag(((QWidget*)this->parent()));
            QMimeData *mimeData = new QMimeData;
            QByteArray qba;
            qba.append(elt->data(32).toString());
            qba.append(";");
            qba.append(elt->data(33).toString());
            qba.append(";");
            qba.append(elt->data(34).toString());
            mimeData->setData("text/"+elt->data(32).toString(),qba);
            drag->setMimeData(mimeData);
            //drag->setPixmap(iconPixmap);
            Qt::DropAction dropAction = drag->exec();
        }
        }

    }
    else//bouton droit
    {
        qDebug()<<"bouton droit";
        if (mouseEvent->button() == Qt::RightButton)
        {   QGraphicsItem * elementConcerne=NULL;
            //si personne à la position de la souris
            if(itemAt(mouseEvent->scenePos())==NULL)
            {
                //et personne dans le rectangle autour
                if(items(QRectF(mouseEvent->scenePos().x()-1,mouseEvent->scenePos().y()-1,2,2)).count()==0)
                {
                    //construction et appel du menu contextuel de la zone de travail
                    QMenu menuContextuelDeRien(QObject::tr("Workspace Menu"));
                    //ajout du titre
                    QAction* titre=new QAction(menuContextuelDeRien.title(),this);
                    titre->setDisabled(true);
                    menuContextuelDeRien.addAction(titre);
                    //titre->setSeparator(true);
                    titre->setFont(QFont("verdana",9,3,true));

                    //ajout des actions du menu:
                    QAction* ajouteUnChampARien=menuContextuelDeRien.addAction(tr("Add a &free field"));

                    QAction* enregistreCommeSourceDeDonnees;
                    QAction* enregistreCommeValeur;
                    //option de menu permettant de mémoriser la requête en tant que source de donnée
                    //si la requête est ok
                    //on propose l'action mémoriser
                    dialogRelation* maman=(dialogRelation*)parent();
                    if(maman->requeteOk)
                    {
                        enregistreCommeSourceDeDonnees=menuContextuelDeRien.addAction(tr("Save as SubQuery"));
                        //si une seule valeur
                        if(maman->m_uip()->tableWidgetPreview->rowCount()==1 &&maman->m_uip()->tableWidgetPreview->columnCount()==1)
                         enregistreCommeValeur=   menuContextuelDeRien.addAction(tr("Save as Value"));
                    }
                    QAction * actionChoisie=menuContextuelDeRien.exec(mouseEvent->screenPos());
                    if(actionChoisie==enregistreCommeValeur)
                    {
                        //création de la sub query
                            bool saisieAliasOk;
                            QString alias=QInputDialog::getText(maman,maman->windowTitle()+tr("Register as value"),tr("Give query's Alias:"),QLineEdit::Normal,"VALUE1", &saisieAliasOk);
                            if(saisieAliasOk)
                            {
                                field * newChamp=new field(maman,true,maman->getScene(),0);
                                newChamp->setData(32,"Value");
                                newChamp->setData(33,"("+maman->m_uip()->lineEditQuery->text()+")");
                                newChamp->setData(34,(qlonglong)newChamp);

                                newChamp->setData(36,"QUERY");
                                newChamp->nomInitial="("+maman->m_uip()->lineEditQuery->text()+") as "+alias;
                                newChamp->document()->setPlainText(newChamp->nomInitial);
                                newChamp->cond=NULL;
                                //newChamp->setTextInteractionFlags(Qt::TextEditable);
                                newChamp->setFlag(QGraphicsItem::ItemIsMovable,true);
                                newChamp->setFlag(QGraphicsItem::ItemIsSelectable,true);
                        //lorsque le texte du champ libre est modifié, mettre à jour la requête
                        //connect(nouveauChamp->document(),SIGNAL(contentsChanged()),maman, SLOT(miseAJourResultat()));
                                maman->vectChampsLibres.append(newChamp);

                                //vider la liste des fonctions agrégat et décocher grouper
                                maman->m_uip()->checkBoxGroupBy->setChecked(false);
                                maman->m_uip()->listWidgetAggregates->clear();
                            }
                    }
                    else
                    {
                    if(actionChoisie==ajouteUnChampARien)
                    {
                        QString what=maman->delimiteur+QObject::tr("something")+maman->delimiteur;
                        field * nouveauChamp=new field(maman,true,this,what,0);
                        //c'est un champ en dehors de tte table
                        nouveauChamp->laTable=NULL;
                        nouveauChamp->setPos(mouseEvent->scenePos());
                        nouveauChamp->setData(32,"Field");
                        //nouveauChamp->setData(33,nomDuChamp);
                        //il est éditable
                        nouveauChamp->setTextInteractionFlags(Qt::TextEditable);
                        nouveauChamp->setFlag(QGraphicsItem::ItemIsMovable,true);
                        nouveauChamp->setFlag(QGraphicsItem::ItemIsSelectable,true);
                        //lorsque le texte du champ libre est modifié, mettre à jour la requête
                        //connect(nouveauChamp->document(),SIGNAL(contentsChanged()),maman, SLOT(miseAJourResultat()));
                        maman->vectChampsLibres.append(nouveauChamp);

                    }
                    else
                    {
                        if(actionChoisie==enregistreCommeSourceDeDonnees)
                        {
                            //création de la sub query
                            bool saisieAliasOk;
                            QString alias=QInputDialog::getText(maman,maman->windowTitle()+tr("Sub Query"),tr("Give Query's Alias:"),QLineEdit::Normal,"REQ1", &saisieAliasOk);
                            if(saisieAliasOk)
                            {

                                query * newQuery=new query(maman,"("+maman->m_uip()->lineEditQuery->text()+")",maman->prochainX,30,0,maman->getScene(),maman->listeDesChampsDuResultat,maman->m_uip()->lineEditQuery->text(),alias);
                                newQuery->setData(36,"QUERY");
                                newQuery->setData(32,"Table");
                                newQuery->setData(33,"("+maman->m_uip()->lineEditQuery->text()+")");
                                newQuery->setData(34,(qlonglong)newQuery);
                                maman->ajouteTable(newQuery);
                                //vider la liste des fonctions agrégat et décocher grouper
                                maman->m_uip()->checkBoxGroupBy->setChecked(false);
                                maman->m_uip()->listWidgetAggregates->clear();
                            }

                        }
                    }
                }

                }
                else//qlq chose ds le rectangle
                {
                    elementConcerne=items(QRectF(mouseEvent->scenePos().x()-1,mouseEvent->scenePos().y()-1,2,2))[0];
                }
            }
            else elementConcerne=itemAt(mouseEvent->scenePos());
            if(elementConcerne!=NULL)
            {
                if(elementConcerne->data(32)=="Table")
                {
                    if (!qgraphicsitem_cast<table*> (elementConcerne ))//le titre dit qu'il est une table
                    {
                        //mais la table est son parent
                        elementConcerne=elementConcerne->parentItem();
                    }

                    ((table*)elementConcerne)->contextMenuEvent(mouseEvent);
                }
                else//cela peut être un lien ou un field
                {
                    if(elementConcerne->data(32)=="Field")
                    {
                        ((field*)elementConcerne)->contextMenuEvent(mouseEvent);
                    }
                    else
                    {
                        if(elementConcerne->data(32)=="Lien")
                        {
                            if(!qgraphicsitem_cast<lien*> (elementConcerne ))//si c'est sa condition qui a été cliquée
                            {
                                elementConcerne=elementConcerne->parentItem();
                            }
                            ((lien*)elementConcerne)->contextMenuEvent(mouseEvent);
                        }

                    }
                }
            }//fin if elementConcerne!=NULL

        }
    }

    QGraphicsScene::mousePressEvent(mouseEvent);

}

