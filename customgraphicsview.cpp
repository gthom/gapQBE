#include "customgraphicsview.h"
#include <QGraphicsItem>
#include <QMimeData>
#include <QDrag>
#include <QDebug>
#include <QTextDocument>
#include <QStandardItemModel>
#include <QDropEvent>
#include "dialogrelation.h"
#include "ui_dialogrelation.h"




void customGraphicsView::dragEnterEvent(QDragEnterEvent *event)
 {
    qDebug("void :customGraphicsView:dragEnterEvent(QDragEnterEvent *event)");
    if(event->source()->objectName()=="listWidgetTables")
    {
        event->accept();
    }
    else
    {

        qDebug()<<"mime"<<event->mimeData()->text();
        qDebug()<<"position"<<event->pos();
        QPointF lePointMapp=this->mapToScene(event->pos());
        QPoint  lePointMappe=lePointMapp.toPoint();
        qDebug()<<"Voici le point mappé:"<<lePointMappe;
        //jointures acceptées entre deux tables
        qDebug()<<"this.item at event->pos():"<<this->itemAt(lePointMappe)->data(32).toString();
        qDebug()<<"scene.item at event->pos():"<<this->scene()->itemAt(lePointMapp,QTransform())->data(32).toString();

        if (this->scene()->itemAt(lePointMapp,QTransform())->data(32).toString()=="Table")
        {
            event->accept();
            qDebug("drag accepté");
        }
        else
        {
            //si c'est un champ et que l'origine est une valeur de la grille des résultats alors on l'accepte
            if(this->scene()->itemAt(lePointMapp,QTransform())->data(32).toString()=="Field")
            {
                qDebug()<<"dragEnterEvent c'est un champ";
                event->accept();
            }
            else
            {
                QGraphicsView::dragEnterEvent(event);
                qDebug()<<this->scene()->itemAt(lePointMappe,QTransform())->data(32).toString();

            }
        }
    }//fin du sinon
 }
void customGraphicsView::dragMoveEvent(QDragMoveEvent *event)
 {
    qDebug()<<"customGraphicsView::dragMoveEvent(QDragMoveEvent *event)";
    if(event->source()->objectName()=="listWidgetTables")
    {
        event->accept();
    }
    else
    {

        QPointF lePointMapp=this->mapToScene(event->pos());
        QPoint  lePointMappe=lePointMapp.toPoint();
        if (this->scene()->itemAt(lePointMappe,QTransform())->data(32).toString()=="Table")
        {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        }
        else
        {
            if(this->scene()->itemAt(lePointMappe,QTransform())->data(32).toString()=="Field")
            {
                qDebug()<<"c'est un champ";
                event->setDropAction(Qt::MoveAction);
                event->accept();
            }
            else
            {
                qDebug()<<"glourps";
                event->ignore();
            }
        }
    }
 }

void customGraphicsView::dropEvent(QDropEvent *event)
{  QPointF lePointMapp=this->mapToScene(event->pos());
   QPoint  lePointMappe=lePointMapp.toPoint();
    if(event->source()->objectName()=="listWidgetTables")
    {
        //ajout  des tables sélectionnées
        emit ilYADesTablesAAjouter(lePointMappe);
    }
    else
    {
        qDebug()<<"customGraphicsView::dropEvent(QDropEvent *event)";
        //si une table est à l'origine du dragndrop
        if(event->mimeData()->hasFormat("text/Table"))
        {
            qDebug()<<"il a le format text/Table";
            //si la destination est une table
            if (this->scene()->itemAt(lePointMappe,QTransform())->data(32).toString()=="Table")
            {
                Table* table1=(Table*)this->scene()->itemAt(lePointMappe,QTransform())->data(34).toLongLong();
                qDebug()<<"table1:"<<table1;
                QByteArray qba=event->mimeData()->data("text/Table");
                QString data(qba);
                QStringList typeEtNomEtAdresse=data.split(';');
                Table * table2=(Table*) typeEtNomEtAdresse[2].toLongLong();//recup de l'adresse de la table2
                qDebug()<<"table2:"<<table2;
                //création du lien entre les deux tables
                //trouver les deux tables:
                if(table1!=table2)
                    emit jointureRequise(table1,table2);
                else
                    qDebug()<<"jointure réflexive interdite créez un alias";

            }
            else
            {
                //on relâche sur un champ

                if(this->scene()->itemAt(lePointMappe,QTransform())->data(32).toString()=="Field")
                {
                    Field* leChamp=(Field*)this->scene()->itemAt(lePointMappe,QTransform());
                    //si c'est une query à l'origine du drag
                    if(event->mimeData()->data("text/Table").split(';')[1].at(0)=='(')
                    {
                        QString condition=event->mimeData()->data("text/Table").split(';')[1];
                        if(leChamp->cond==NULL)
                        {
                            leChamp->ajouteCondition(" in"+condition);

                        }
                        else
                        {
                            leChamp->modifieCondition(" in"+condition);
                        }

                    }
                }
                else
                event->ignore();
            }

        }
        else //l'emmetteur du drag n'est ni une table ni une query
        {
            //ça peut être un drag de valeur pour condition sur champ
            qDebug()<<"n'a pas le type text/Table";
            if (this->scene()->itemAt(lePointMappe,QTransform())->data(32).toString()=="Field")
            {
                //on va modifier la condition sur champ
                qDebug()<<"drag and drop sur champ";
                qDebug()<<"mimedata de la cellule"<<event->mimeData()->formats();
                Field * leChamp=(Field*)this->scene()->itemAt(lePointMappe,QTransform());
                QString condition;
                if(event->mimeData()->hasFormat("text/Value")) //drag an drop de value sur champ
                {
                    condition=QString(event->mimeData()->data("text/Value").split(';')[1]);
                }
                else
                {
                    //obtention des items droppés si valeur de la grille
                    QStandardItemModel model(this->parent());
                    model.dropMimeData(event->mimeData(), Qt::CopyAction, 0,0, QModelIndex());
                    condition=delimiteur+model.item(0,0)->text()+delimiteur;
                }

                //s'il n'y a pas encore de condition sur le champ
                if(leChamp->cond==NULL)
                {
                    leChamp->ajouteCondition("="+condition);
                }
                else
                {
                    leChamp->modifieCondition("="+condition);
                }
            }
            else
                event->ignore();
        }
    }
}
