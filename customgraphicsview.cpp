#include "customgraphicsview.h"
#include <QGraphicsItem>
#include <QMimeData>
#include <QDrag>
#include <QDebug>
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
            event->ignore();
            qDebug("drag ignoré");
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
            event->ignore();
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
        QPointF lePointMapp=this->mapToScene(event->pos());
        QPoint  lePointMappe=lePointMapp.toPoint();
        if (this->scene()->itemAt(lePointMappe)->data(32).toString()=="Table")
        {
            table* table1=(table*)this->scene()->itemAt(lePointMappe)->data(34).toLongLong();
            qDebug()<<"table1:"<<table1;

            QString data=event->mimeData()->text();
            QStringList typeEtNomEtAdresse=data.split(';');
            table * table2=(table*) typeEtNomEtAdresse[2].toLongLong();//recup de l'adresse de la table2
            qDebug()<<"table2:"<<table2;
            //création du lien entre les deux tables
            //trouver les deux tables:
            if(table1!=table2)
            emit jointureRequise(table1,table2);
            else
                qDebug()<<"humm";

        }
        else
            event->ignore();
    }
}
