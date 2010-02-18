#include "lien.h"
#include <QDebug>
#include <QAction>
#include <QMenu>
#include <QTextDocument>
#include <QPainter>
#include "math.h"
#include <QInputDialog>
#include <QVector>

lien::~lien()
{
    qDebug()<<"destructeur du lien";
    //je me retire du vecteur de mes deux tables
    t1->vectLiens.remove(t1->vectLiens.indexOf(this),1);
    t2->vectLiens.remove(t2->vectLiens.indexOf(this),1);
    //l'effacement du lien dans le vecteur central est réalisé par la méthode supprimeLien de la classe dialogRelation
    if(condition!=NULL)
        delete condition;
    delete texte1;
    delete texte2;

}

lien::lien(table* pt1,table* pt2,QGraphicsItem * parent,QGraphicsScene* laScene,QString typ):QGraphicsLineItem(pt1->pos().x()+pt1->boundingRect().width()/2,pt1->pos().y(),pt2->pos().x()+pt2->boundingRect().width()/2,pt2->pos().y(),parent,laScene)
{
    //constructeur du lien
    t1=pt2;
    t2=pt1;
    texte1=new QGraphicsTextItem(this,this->scene());
    texte2=new QGraphicsTextItem(this,this->scene());
    //il est sélectionnable
    this->setFlag(QGraphicsItem::ItemIsSelectable,true);
    //ajout de la condition de jointure
    if(typ!="Natural")
    {
        condition=new QGraphicsTextItem(this);
        condition->setData(32,"Lien");
        QObject::connect(condition->document(),SIGNAL(contentsChanged()),t1->maman, SLOT(miseAJourResultat()));
        this->texteDeLaCondition=t1->getNomTable()+".xxx="+t2->getNomTable()+".yyy";
        condition->setHtml(texteDeLaCondition);
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
     painter->setPen(myPen);
     painter->setBrush(myColor);
     QPointF origine=t1->pos()+QPointF(t1->boundingRect().width()/2,10);
     QPointF destination=t2->pos()+QPointF(t2->boundingRect().width()/2,10);
     QLineF centerLine(origine,destination);
     QPolygonF endPolygon = t2->polygon();
     QPolygonF beginPolygon = t1->polygon();

     QPointF p1 = endPolygon.first()+t2->pos() ;
     QPointF p2;
     QPointF intersectPointT2;
     QLineF polyLine;
     for (int i = 1; i < endPolygon.count(); ++i)
     {
         p2 = endPolygon.at(i)+t2->pos();
         polyLine = QLineF(p1, p2);
         QLineF::IntersectType intersectType =
                 polyLine.intersect(centerLine, &intersectPointT2);
         if (intersectType == QLineF::BoundedIntersection)
             break;
         p1 = p2;
     }
     p1 = beginPolygon.first()+t1->pos() ;

     QPointF intersectPointT1;

     for (int i = 1; i < beginPolygon.count(); ++i)
     {
         p2 = beginPolygon.at(i)+t1->pos();
         polyLine = QLineF(p1, p2);
         QLineF::IntersectType intersectType =
                 polyLine.intersect(centerLine, &intersectPointT1);
         if (intersectType == QLineF::BoundedIntersection)
             break;
         p1 = p2;
     }
     setLine(QLineF(intersectPointT1,intersectPointT2));


     if(typeDeJointure=="Natural")
     {

         texte1->document()->setPlainText("?");

         texte2->document()->setPlainText("?");
     }
     else
     {
         if(typeDeJointure=="Inner")
         {

             texte1->document()->setPlainText("=");

             texte2->document()->setPlainText("=");
         }
         else
         {
             if(typeDeJointure=="left outer")
         {

             texte1->document()->setPlainText("+=");

             texte2->document()->setPlainText("");
         }
         else
         {
             if(typeDeJointure=="right outer")
         {

             texte1->document()->setPlainText("");

             texte2->document()->setPlainText("+=");
         }

         }

         }
     }
         QPointF posTexte1,posTexte2;

         if(intersectPointT1.x()<intersectPointT2.x())
         {
             posTexte1.setX(intersectPointT1.x());
             posTexte2.setX(intersectPointT2.x()-texte2->document()->size().width());

         }
         else
         {
             posTexte2.setX(intersectPointT2.x());
             posTexte1.setX(intersectPointT1.x()-texte1->document()->size().width());

         }
         if(intersectPointT1.y()<intersectPointT2.y())
         {
             posTexte1.setY(intersectPointT1.y());
             posTexte2.setY(intersectPointT2.y()-texte2->document()->size().height());
         }
         else
         {
             posTexte2.setY(intersectPointT2.y());
             posTexte1.setY(intersectPointT1.y()-texte1->document()->size().height());
         }
         texte1->setPos(posTexte1);
         texte2->setPos(posTexte2);


    painter->drawLine(line());

     //
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


    this->setLine(t1->pos().x()+t1->boundingRect().width()/2,t1->pos().y(),t2->pos().x()+t2->boundingRect().width()/2,t2->pos().y());

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
     QMenu menu(QObject::tr("Link Menu"));
     //si je n'était pas sélectionnée, je le deviens
     this->setSelected(true);
     //titre du menu
     QAction* titre=new QAction(menu.title(),scene());
    titre->setDisabled(true);
    menu.addAction(titre);
    //titre->setSeparator(true);
    titre->setFont(QFont("verdana",9,3,true));
    //si je n'était pas sélectionnée, je le deviens
    this->setSelected(!this->isSelected());
     //création des actions du menu
     QAction *removeAction = menu.addAction(QObject::tr("&Remove"));
     QAction *changeJoinType = menu.addAction(QObject::tr("&Change join type"));
     //s'il y a une condition proposer de l'éditer
     QAction* editJoinCond;
     if(this->typeDeJointure!="Natural")
     {
         editJoinCond=menu.addAction(QObject::tr("&Edit join condition"));
     }
     //exécution du menu et récupération de l'action choisie
     QAction * actionChoisie=menu.exec(event->screenPos());

     if(actionChoisie==changeJoinType) t1->maman->changeJoinType(this);
     else
      {
         //autre choix du menu
         if(actionChoisie==removeAction)
         {
             t1->maman->supprimerLien(this);
         }
         else
         {
             if(actionChoisie==editJoinCond)
             {
                 bool ok;
                 QString text = QInputDialog::getText(0, QObject::tr("Edit Join Condition"),
                                                      QObject::tr("Join Condition:"), QLineEdit::Normal,
                                                      this->condition->document()->toPlainText(), &ok);
                 if (ok && !text.isEmpty())

                     this->condition->document()->setPlainText(text);
             }
         }
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
        condition->setHtml(t1->getNomTable()+".xxx="+t2->getNomTable()+".yyy");
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

}


