#include "qcustomgraphicsscene.h"
#include <QGraphicsItem>
#include <QDrag>
#include <QDebug>

#include "table.h"
#include "field.h"
#include "types.h"
#include <QMenu>
#include <QAction>

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
            QDrag *drag = new QDrag(((QWidget*)this->parent()));
            QMimeData *mimeData = new QMimeData;
            mimeData->setText(elt->data(32).toString()+';'+elt->data(33).toString());
            drag->setMimeData(mimeData);
            //drag->setPixmap(iconPixmap);
            Qt::DropAction dropAction = drag->exec();
        }

    }
    else//bouton droit
    {
        if (mouseEvent->button() == Qt::RightButton)
        {   QGraphicsItem * elementConcerne=NULL;
            //si personne à la position de la souris
            if(itemAt(mouseEvent->scenePos())==NULL)
            {
                //et personne dans le rectangle autour
                if(items(QRectF(mouseEvent->scenePos().x()-1,mouseEvent->scenePos().y()-1,2,2)).count()==0)
                {
                    //appel du menu contextuel de la zone de travail

                    QMenu menuContextuelDeRien;
                    QAction* ajouteUnChampARien=menuContextuelDeRien.addAction(tr("Ajoute un &champ libre"));
                    QAction* ajouteUnAgregat=menuContextuelDeRien.addAction(tr("Ajoute un a&grégat"));
                    menuContextuelDeRien.exec(mouseEvent->screenPos());

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

