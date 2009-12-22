#include "customgraphicsview.h"
#include <QGraphicsItem>
#include <QMimeData>
#include <QDrag>
#include <QDebug>
#include "table.h"
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
            QString nomTable1=this->scene()->itemAt(lePointMappe)->data(33).toString();

            QString data=event->mimeData()->text();
            QStringList typeEtNom=data.split(';');
            //création du lien entre les deux tables
            //trouver les deux tables:
            emit jointureRequise(nomTable1,typeEtNom[1]);

        }
        else
            event->ignore();
    }
}
