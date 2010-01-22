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
        qDebug()<<"scene.item at event->pos():"<<this->scene()->itemAt(lePointMappe)->data(32).toString();

        if (this->scene()->itemAt(lePointMappe)->data(32).toString()=="Table")
        {
            event->accept();
            qDebug("drag accepté");
        }
        else
        {
            //si c'est un champ et que l'origine est une valeur de la grille des résultats alors on l'accepte
            if(this->scene()->itemAt(lePointMappe)->data(32).toString()=="Field")
            {
                qDebug()<<"dragEnterEvent c'est un champ";
                event->accept();
            }
            else
            {
                QGraphicsView::dragEnterEvent(event);
                qDebug()<<this->scene()->itemAt(lePointMappe)->data(32).toString();

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
        if (this->scene()->itemAt(lePointMappe)->data(32).toString()=="Table")
        {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        }
        else
        {
            if(this->scene()->itemAt(lePointMappe)->data(32).toString()=="Field")
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
{  if(event->source()->objectName()=="listWidgetTables")
    {
        //ajout  des tables sélectionnées
        emit ilYADesTablesAAjouter();
    }
    else
    {
        qDebug()<<"customGraphicsView::dropEvent(QDropEvent *event)";
        //si une table est à l'origine du dragndrop
        if(event->mimeData()->hasFormat("text/table"))
        {
            QPointF lePointMapp=this->mapToScene(event->pos());
            QPoint  lePointMappe=lePointMapp.toPoint();
            if (this->scene()->itemAt(lePointMappe)->data(32).toString()=="Table")
            {
                table* table1=(table*)this->scene()->itemAt(lePointMappe)->data(34).toLongLong();
                qDebug()<<"table1:"<<table1;
                QByteArray qba=event->mimeData()->data("text/table");
                QString data(qba);
                QStringList typeEtNomEtAdresse=data.split(';');
                table * table2=(table*) typeEtNomEtAdresse[2].toLongLong();//recup de l'adresse de la table2
                qDebug()<<"table2:"<<table2;
                //création du lien entre les deux tables
                //trouver les deux tables:
                if(table1!=table2)
                    emit jointureRequise(table1,table2);
                else
                    qDebug()<<"jointure réflexive interdite";

            }
            else
                event->ignore();
        }
        else
        {
            //ça peut être un drag de valeur pour condition sur champ
            QPointF lePointMapp=this->mapToScene(event->pos());
            QPoint  lePointMappe=lePointMapp.toPoint();
            if (this->scene()->itemAt(lePointMappe)->data(32).toString()=="Field")
            {
                //on va modifier la condition sur champ
                qDebug()<<"drag and drop sur champ";
                qDebug()<<"mimedata de la cellule"<<event->mimeData()->formats();
                field * leChamp=(field*)this->scene()->itemAt(lePointMappe);
                //obtention des items droppés

                QStandardItemModel model(this->parent());
                model.dropMimeData(event->mimeData(), Qt::CopyAction, 0,0, QModelIndex());
                QString leContenuDeLaCellule="\""+model.item(0,0)->text()+"\"";

                //s'il n'y a pas encore de condition sur le champ
                if(leChamp->cond==NULL)
                {
                    leChamp->ajouteCondition("="+leContenuDeLaCellule);

                }
                else
                {
                    leChamp->modifieCondition("="+leContenuDeLaCellule);


                }
            }
            else
                event->ignore();
        }
    }
}
