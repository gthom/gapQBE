#include "table.h"
#include <QFontMetrics>
#include <QAction>
#include <QGraphicsWidget>
#include<QGraphicsSceneContextMenuEvent>
#include <QGraphicsItem>
#include <QMenu>
#include <QDebug>
#include "field.h"
#include <QInputDialog>

table::~table()
{
    qDebug()<<"table::~table()";
    delete this->laLigne;
    delete this->title;
    //effacement des champs
    foreach(field* leChamp,vecteurChamps)
    {
        delete leChamp;
    }
}
table::table(dialogRelation* mum,QString nom,qreal x,qreal y, QGraphicsItem* parent, QGraphicsScene * laScene,QStringList listeDesChamps)
        :maman(mum),QGraphicsRectItem(x,y,200,200,parent)

{
qDebug()<<"constructeur de table";
    nomTable=nom;


    alias="";
    //le titre
    title=new QGraphicsTextItem(this);
    title->setFont(QFont("Verdana",10,QFont::Bold,false));
    //déterminons la largeur de la table:
    long largeurMaxi=QFontMetrics(title->font()).width(nomTableTronque());
    for(int noChamp=0;noChamp<listeDesChamps.count();noChamp++)
    {
        long largeurDuChamp=QFontMetrics(title->font()).width(listeDesChamps[noChamp]);
        if (largeurDuChamp>largeurMaxi) largeurMaxi=largeurDuChamp;
    }
    //construction du QGraphicsRectItem
    setRect(x,y,largeurMaxi+10,200);
    //création du titre
    setBrush(QColor("#FFFF00"));//jaune
    title->setPos(0,0);//par rapport à son parent
    title->setTextWidth(boundingRect().width());
    title->setHtml("<center>"+nomTableTronque()+"</center>");

    //stockage de quelques infos
    //c'est une table
    title->setData(32,"Table");
    title->setData(34,qVariantFromValue((qlonglong)this));
    //on stocke son nom
    title->setData(33,nomTable);
    setData(32,"Table");
    setData(33,nomTable);
    setData(34,qVariantFromValue((qlonglong)this));
    long ordonne=title->boundingRect().height();
    //ajout d'une ligne sous le titre
    laLigne=new QGraphicsLineItem(0,ordonne,boundingRect().width(),ordonne,this);
    this->setRect(0,0,largeurMaxi+10,ordonne+10);
    //création des champs dans la table
    for(int noChamp=0;noChamp<listeDesChamps.count();noChamp++)
    {
        vecteurChamps.push_back(new field(maman,false,laScene,listeDesChamps[noChamp],this));
        vecteurChamps[noChamp]->setPos(10,ordonne);
        //sa table c'est moi
        vecteurChamps[noChamp]->laTable=this;
        //les champs d'origine ne peuvent être modifiés
          //vecteurChamps[noChamp]->setTextInteractionFlags(Qt::TextEditable);
        vecteurChamps[noChamp]->setData(32,"Field");
        vecteurChamps[noChamp]->setData(33,nom+"."+listeDesChamps[noChamp]);
        ordonne+=vecteurChamps[noChamp]->boundingRect().height();
        this->setRect(0,0,largeurMaxi+20,ordonne+10);
    }
    setAcceptDrops(false);
}



 void table::contextMenuEvent(QGraphicsSceneMouseEvent *event)
 {
     //ce qui se passe lorsque le menu contextuel de la table est appelé
     qDebug()<<"void table::contextMenuEvent(QGraphicsSceneMouseEvent *event)";
     QMenu menu(QObject::tr("Table Menu"));
     //ajout du titre

     QAction* titre=new QAction(menu.title(),this->maman);
    titre->setDisabled(true);
    menu.addAction(titre);
    //titre->setSeparator(true);
    titre->setFont(QFont("verdana",9,3,true));
    //si je n'était pas sélectionnée, je le deviens
    this->setSelected(!this->isSelected());

     //si je n'était pas sélectionnée, je le deviens
     this->setSelected(true);
     //création des actions du menu
     QAction *removeAction = menu.addAction(QObject::tr("&Remove"));
     QObject::connect(removeAction, SIGNAL(triggered()),maman, SLOT(tableSupprimer()));
     QAction *addFreeFieldAction = menu.addAction(QObject::tr("&Add free Field"));
     QAction *removeOrAddAliasAction;
     QAction * editAlias;
     //les alias ne sont pas accessibles pour les sous-requêtes
     //comment savoir si une table est une sous-requête
     if(!(data(36).toString()=="QUERY"))
     {
     if(this->alias!="")
     removeOrAddAliasAction=menu.addAction(QObject::tr("&Remove alias"));
     else
     removeOrAddAliasAction=menu.addAction(QObject::tr("&Add alias"));
 }
     else//c'est une sous-requête
     {
         editAlias=menu.addAction(QObject::tr("&Edit alias"));
     }

     //exécution du menu
     QAction * actionChoisie=menu.exec(event->screenPos());
     if(actionChoisie==editAlias)
     {
         //affichage d'une boîte de dialogue de saisie de l'alias
                bool ok;
                 QString candidat=QInputDialog::getText(maman, QObject::tr("Give alias name"),
                                          QObject::tr("Alias:"), QLineEdit::Normal,
                                          alias, &ok);
                 if(ok)
                 {
                     alias=candidat;
                 }
     }
     else
     {
     if(actionChoisie==addFreeFieldAction)
     {
         maman->tableAjouterChamp(this);
     }
     else
     {
         if(actionChoisie==removeOrAddAliasAction)
         {
             if(alias!="")//il y a un alias c'est donc qu'on veut l'enlever
             {

                 this->title->setHtml(nomTableTronque());
                 foreach (lien *leLien, vectLiens)
                 {
                     if(leLien->typeDeJointure!="Natural" && leLien->typeDeJointure!="Cross")
                     {//à améliorer remplacement de l'alias par le nom de la table dans la condition
                         //leLien->texteDeLaCondition.replace(alias,nomTable);
                         //leLien->condition->setPlainText(leLien->texteDeLaCondition);
                         //qDebug()<<"textedelacondition :"<<leLien->texteDeLaCondition;
                             //je split sur l'opérateur
                             QRegExp operateur("(=|<=|<>|>=|<|>)");
                             int pos=operateur.indexIn(leLien->texteDeLaCondition);
                             //recup de l'opérateur
                             QString op=operateur.cap(1);
                             QStringList qsl=leLien->texteDeLaCondition.split(QRegExp("=|<=|<>|<|>|>="));
                             //qDebug()<<"partie gauche :"<<qsl[0]<<" partiedroite "<<qsl[1]<<" operateur "<<op;
                             QStringList partieGauche;
                             partieGauche=qsl[0].split(".");
                             QStringList partieDroite=qsl[1].split(".");
                             if(leLien->t1==this)
                             {
                                 if(partieGauche[0]==alias) partieGauche[0]=nomTable;
                             }
                             else
                             {
                                 if(partieDroite[0]==alias) partieDroite[0]=nomTable;
                             }
                             leLien->texteDeLaCondition=partieGauche.join(".")+op+partieDroite.join(".");
                             leLien->condition->setPlainText(leLien->texteDeLaCondition);
                     }
                 }
                 alias="";
                 maman->miseAJourResultat();
             }
             else
             {
                 bool ok;
                 QString candidat=QInputDialog::getText(maman, QObject::tr("Give alias name"),
                                          QObject::tr("Alias:"), QLineEdit::Normal,
                                          this->nomTable+"1", &ok);
                 if(ok)
                 {
                     alias=candidat;
                     QString nomAvecAlias=nomTableTronque()+" as "+alias;

                     //obtention de la largeur
                     long largeurNouveauTitre=QFontMetrics(title->font()).width(nomAvecAlias);
                     //s'il ne tient pas on élargit la table
                     if(boundingRect().width()-20<largeurNouveauTitre)
                     {
                         this->setRect(0,0,largeurNouveauTitre+50,boundingRect().height());
                         this->title->setTextWidth(largeurNouveauTitre+50);
                         //redimensionnement de la ligne
                         this->laLigne->setLine(this->laLigne->x(),this->laLigne->y(),this->laLigne->x()+largeurNouveauTitre+50,this->laLigne->y());
                     }
                     this->title->setHtml("<center>"+nomAvecAlias+"</center>");
                     foreach (lien *leLien, vectLiens)
                     {
                         if(leLien->typeDeJointure!="Natural"&& leLien->typeDeJointure!="Cross")
                         {
                             //qDebug()<<"textedelacondition :"<<leLien->texteDeLaCondition;
                             //je split sur l'opérateur
                             QRegExp operateur("(=|<=|<>|>=|<|>)");
                             int pos=operateur.indexIn(leLien->texteDeLaCondition);
                             //recup de l'opérateur
                             QString op=operateur.cap(1);
                             QStringList qsl=leLien->texteDeLaCondition.split(QRegExp("=|<=|<>|<|>|>="));
                             //qDebug()<<"partie gauche :"<<qsl[0]<<" partiedroite "<<qsl[1]<<" operateur "<<op;
                             QStringList partieGauche;
                             partieGauche=qsl[0].split(".");
                             QStringList partieDroite=qsl[1].split(".");
                             if(leLien->t1==this)
                             {
                                 if(partieGauche[0]==nomTable) partieGauche[0]=alias;
                             }
                             else
                             {
                                 if(partieDroite[0]==nomTable) partieDroite[0]=alias;
                             }
                             leLien->texteDeLaCondition=partieGauche.join(".")+op+partieDroite.join(".");
                             leLien->condition->setPlainText(leLien->texteDeLaCondition);
                         }
                     }
                     maman->miseAJourResultat();
                 }
             }
         }
     }
 }

 }

QVariant table::itemChange(GraphicsItemChange change,const QVariant &value)

{
    qDebug()<<"QVariant table::itemChange(GraphicsItemChange change,const QVariant &value)";
    if (change == QGraphicsItem::ItemPositionChange) {
         foreach (lien *leLien, vectLiens) {
             leLien->updatePosition();
         }
     }
    qDebug()<<"fin table::itemChange()";
     return value;
}








