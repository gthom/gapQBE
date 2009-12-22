#include "lien.h"
#include <QDebug>
#include <QAction>
#include <QMenu>
#include <QTextDocument>
#include <QPainter>
#include "math.h"

lien::~lien()
{
    qDebug()<<"ddestructeur du lien";
    if(condition!=NULL)
        delete condition;
}

lien::lien(table* pt1,table* pt2,QGraphicsItem * parent,QGraphicsScene* laScene,QString typ):QGraphicsLineItem(pt1->pos().x()+pt1->boundingRect().width()/2,pt1->pos().y(),pt2->pos().x()+pt2->boundingRect().width()/2,pt2->pos().y(),parent,laScene)
{
    //constructeur du lien
    t1=pt2;
    t2=pt1;
    //il est sélectionnable
    this->setFlag(QGraphicsItem::ItemIsSelectable,true);
    //ajout de la condition de jointure
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
    setZValue(-1000.0);
    updatePosition();
}
 void lien::paint(QPainter *painter, const QStyleOptionGraphicsItem *,
           QWidget *)
 {
     if (t1->collidesWithItem(t2))
         return;
    QColor myColor(Qt::red);
     QPen myPen = pen();
     myPen.setColor(myColor);
     qreal arrowSize = 20;
     painter->setPen(myPen);
     painter->setBrush(myColor);

     QLineF centerLine(t1->pos(), t2->pos());
     QPolygonF endPolygon = t2->polygon();
     QPointF p1 = endPolygon.first() + t2->pos();
     QPointF p2;
     QPointF intersectPoint;
     QLineF polyLine;
     for (int i = 1; i < endPolygon.count(); ++i)
     {
     p2 = endPolygon.at(i) + t2->pos();
     polyLine = QLineF(p1, p2);
     QLineF::IntersectType intersectType =
         polyLine.intersect(centerLine, &intersectPoint);
     if (intersectType == QLineF::BoundedIntersection)
         break;
         p1 = p2;
     }

     setLine(QLineF(intersectPoint, t1->pos()));
    qreal Pi=3.14;
     double angle = ::acos(line().dx() / line().length());
     if (line().dy() >= 0)
         angle = (Pi * 2) - angle;

         QPointF arrowP1 = line().p1() + QPointF(sin(angle + Pi / 3) * arrowSize,
                                         cos(angle + Pi / 3) * arrowSize);
         QPointF arrowP2 = line().p1() + QPointF(sin(angle + Pi - Pi / 3) * arrowSize,
                                         cos(angle + Pi - Pi / 3) * arrowSize);

         arrowHead.clear();
         arrowHead << line().p1() << arrowP1 << arrowP2;
         painter->drawLine(line());
         painter->drawPolygon(arrowHead);
         if (isSelected())
         {
             painter->setPen(QPen(myColor, 1, Qt::DashLine));
             QLineF myLine = line();
             myLine.translate(0, 4.0);
             painter->drawLine(myLine);
             myLine.translate(0,-8.0);
             painter->drawLine(myLine);
         }
 }
 QRectF lien::boundingRect() const
 {
     qreal extra = (pen().width() + 20) / 2.0;

     return QRectF(line().p1(), QSizeF(line().p2().x() - line().p1().x(),
                                       line().p2().y() - line().p1().y()))
         .normalized()
         .adjusted(-extra, -extra, extra, extra);
 }

 QPainterPath lien::shape() const
 {
     QPainterPath path = QGraphicsLineItem::shape();
     path.addPolygon(arrowHead);
     return path;
 }
void lien::updatePosition()
{
//    table * tableGauche=t2;
//    table * tableDroite=t1;
//    if(t1->pos().x()<t2->pos().x())
//    {
//        tableGauche=t1;
//        tableDroite=t2;
//    }
//    qDebug()<<"table gauche:"<<tableGauche->nomTable;

    this->setLine(t1->pos().x()+t1->boundingRect().width()/2,t1->pos().y(),t2->pos().x()+t2->boundingRect().width()/2,t2->pos().y());
    //this->setLine(QLineF(mapFromItem(t1,t1->boundingRect().width()/2,10),mapFromItem(t2,t2->boundingRect().width()/2,10)));

    //intersections
//    QRectF rectInterTG=boundingRect().intersected(tableGauche->boundingRect());
//    QRectF rectInterTD=boundingRect().intersected(tableDroite->boundingRect());
//    QPointF pointGauche=this->line().p1();
//    QPointF pointDroit=this->line().p2();
//    if(pointDroit.x()<pointGauche.x())
//    {
//        pointGauche=this->line().p2();
//        pointDroit=this->line().p1();
//    }
//    qDebug()<<"pointgauche:"<<pointGauche;
//    qDebug()<<"pointdroit:"<<pointDroit;
//    pointGauche.setX(pointGauche.x()+rectInterTG.width());
//
//    pointDroit.setX(pointDroit.x()-rectInterTD.width());
//    qDebug()<<"pointgauche:"<<pointGauche;
//    qDebug()<<"pointdroit:"<<pointDroit;
//    this->setLine(QLineF(pointGauche,pointDroit));
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


