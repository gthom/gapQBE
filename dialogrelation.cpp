#include "dialogrelation.h"
#include "ui_dialogrelation.h"
#include "dialogsortorder.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QGraphicsRectItem>
#include <QDebug>
#include "field.h"
#include <QFontMetrics>
#include "dialogtypejointure.h"
#include "ui_dialogtypejointure.h"
#include <QTextDocument>
#include <QSqlResult>
#include <QMessageBox>
#include "ui_dialogsortorder.h"
#include <QFileDialog>
#include <QSqlDriver>
#include <QMenu>


dialogRelation::dialogRelation(QWidget *parent) :
        scene(this),
        QDialog(parent),
        m_ui(new Ui::dialogRelation)
{
    messageDErreur=tr("Unknown query state");
    requeteOk=false;
    m_ui->setupUi(this);
    //abscisse de la prochaine table
    prochainX=20;
    //recup de la base
    db=QSqlDatabase::database();
    //determination du délimiteur en fonction du driver
    if(db.driverName().contains("MYSQL"))
    {
        delimiteur="\"";
    }
    else
        delimiteur="'";
    //on donne le delimiteur à la customGraphicsView
    m_ui->graphicsView->delimiteur=delimiteur;
    //QMessageBox::warning(this,"pb",db.lastError().text());
    db.open();
    //recup des tables de la base
    QStringList listeDesTables=db.tables();
    m_ui->listWidgetTables->insertItems(0,listeDesTables);
    m_ui->graphicsView->setScene(&scene);

//connexion des signaux aux slots
    connect (m_ui->graphicsView,SIGNAL(jointureRequise(Table *,Table *)),this,SLOT(jointure(Table*,Table*)));
    connect (m_ui->graphicsView,SIGNAL(ilYADesTablesAAjouter(QPoint)),this,SLOT(allezAllezOnAjouteLesTables(QPoint)));
    connect (this,SIGNAL(ilYADesTablesAAjouter(QPoint)),this,SLOT(allezAllezOnAjouteLesTables(QPoint)));  
    connect(m_ui->toolButtonExecuteRequete,SIGNAL(clicked()),this,SLOT(miseAJourResultat()));
    connect (m_ui->checkBoxGroupBy,SIGNAL(clicked()),this,SLOT(on_checkBoxGroupBy_clicked()));
    connect(m_ui->pushButtonAddAgregate,SIGNAL(clicked()),this,SLOT(on_pushButtonAddAggregate_clicked()));
    connect(m_ui->listWidgetAggregates,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(on_customContextMenuAggregate(QPoint)));
    connect(m_ui->lineEditHaving,SIGNAL(textChanged(QString)),this,SLOT(miseAJourResultat()));
    connect(m_ui->lineEditIndex,SIGNAL(textChanged(QString)),this,SLOT(miseAJourResultat()));
    connect(m_ui->lineEditCount,SIGNAL(textChanged(QString)),this,SLOT(miseAJourResultat()));
//quelques actions que j'ai enlevé car impossible d'empêcher l'affichage du menu contextuel
    /*m_ui->graphicsView->addAction(m_ui->actionDelete_tables_s);
    m_ui->graphicsView->addAction(m_ui->actionZoom_in);
    m_ui->graphicsView->addAction(m_ui->actionZoom_out);*/


}

dialogRelation::~dialogRelation()
{
    delete m_ui;
}

void dialogRelation::changeEvent(QEvent *e)
{
    switch (e->type()) {
    case QEvent::LanguageChange:
        m_ui->retranslateUi(this);
        break;
    default:
        break;
    }
}



void dialogRelation::tableSupprimer()
{
    //supprime une table ou plusieurs tables dans la graphics view
    qDebug()<<"void dialogRelation::tableSupprimer()";
    foreach (QGraphicsItem *item, scene.selectedItems())
    {
        if (item->data(32) == "Table")
        {
            Table*t=(Table*)item;
            //suppression des liens concernant la table
            for(int noLien=vectLiens.size()-1;noLien>=0;noLien--)
            {
                if(vectLiens[noLien]->t1==t ||vectLiens[noLien]->t2==t)
                {
                    delete vectLiens[noLien];
                    vectLiens.remove(noLien,1);

                }
            }
            //puis
            //supprime une des tables ajoutée
            int noDeLaTableASupprimer=vectTables.indexOf(t);
            //libération mémoire
            delete vectTables[noDeLaTableASupprimer];
            //suppression de la case du vecteur
            vectTables.remove(noDeLaTableASupprimer,1);
        }

    }//fin du foreach
    //mise à jour de la requête
    miseAJourResultat();

}

void dialogRelation::jointure(Table* t1,Table* t2)
{
    qDebug()<<"void dialogRelation::jointure(table* t1,table* t2)";
    //j'affiche une boite de dialogue pour saisir le type de jointure
    DialogTypeJointure dtj;
    //puis je trouve les deux tables dans le vecteur et ajoute le lien dans la table des liens
    if(dtj.exec())
    {
        QString typ=dtj.m_ui->comboBoxType->currentText();
        if(t1!=t2) //pas de jointure entre une table et elle-même
        {
            Table * table1=NULL;
            Table * table2=NULL;
            //chtite boucle ds le vecteur on sort qd trouve les deux
            long indice=0;
            while(!(table2!=NULL && table1!=NULL))
            {
                if(vectTables[indice]==t1)
                {
                    table1=vectTables[indice];
                }
                if(vectTables[indice]==t2)
                {table2=vectTables[indice];
                }
                indice++;

            }
            Lien * nouveauLien=new Lien(table2,table1,0,&this->scene,typ);
            scene.addItem(nouveauLien);
            nouveauLien->ajouteElementsAuGroupe();
            table1->vectLiens.push_back(nouveauLien);
            table2->vectLiens.push_back(nouveauLien);
            vectLiens.push_back(nouveauLien);

        }
    }
}


void dialogRelation::on_toolButtonMove_clicked()
{
    qDebug()<<"void dialogRelation::on_toolButtonMove_clicked()";
    //Choix de l'outil move
    scene.outil="move";
    m_ui->graphicsView->setCursor(QCursor(Qt::ArrowCursor));
}
void dialogRelation::on_toolButtonJoin_clicked()
{
    qDebug()<<"void dialogRelation::on_toolButtonJoin_clicked()";
    //choix de l'outil drag
    scene.outil="drag";
    m_ui->graphicsView->setCursor(QCursor(Qt::PointingHandCursor));
}
void dialogRelation::tableAjouterChamp(Table * laTable)
{
    //but:Ajouter un champ libre à la table
    //   exemple select 'bonjour' from client
    //attention aux titres qui se font passer pour des tables

    qDebug()<<"void dialogRelation::tableAjouterChamp()";
    QString nomDuChamp=delimiteur+"Some Text"+delimiteur;
    Field* nouveauChamp=new Field(this,true,&scene,nomDuChamp,laTable);
    //c'est sa table
    nouveauChamp->laTable=laTable;
    //ajout du nouveau champ au vecteur des champs
    laTable->vecteurChamps.append(nouveauChamp);
    //augmenter la hauteur de la table
    int hauteurChamp=QFontMetrics(nouveauChamp->font()).height();
    QRect ancien=laTable->boundingRect().toRect();
    //position du champ
    nouveauChamp->setPos(10,ancien.height());
    //les données du champ
    nouveauChamp->setData(32,"Field");
    nouveauChamp->setData(33,laTable->nomTable+"."+nomDuChamp);
    //il est éditable
    nouveauChamp->setTextInteractionFlags(Qt::TextEditable);
    //lorsque le texte du champ libre est modifié, mettre à jour la requête
    connect(nouveauChamp->document(),SIGNAL(contentsChanged()),this, SLOT(miseAJourResultat()));
    //redim de la hauteur de la table
    ancien.setHeight(ancien.height()+hauteurChamp);
    laTable->setRect(ancien);

}
QList<QList <Lien*> *> obtenirListeDesGroupesAuquelEstRelieLeLienARanger(Lien* lienARanger,QList<QList <Lien*> *>listeDesGroupesDeLiens)
{
   QList<QList <Lien*> *> resultat;
   foreach(QList<Lien*>* groupeDeLiens,listeDesGroupesDeLiens)//pour chaque groupe de lien déjà trouvé
   {
               foreach(Lien* unLien,*groupeDeLiens) //pour chaque lien de ce groupe
               {
                   if (unLien->estRelieA(lienARanger)) //ajout du lienARanger au groupe
                   {
                       if(!resultat.contains(groupeDeLiens))
                       resultat.append(groupeDeLiens);
                   }

               }
   }
   qDebug()<<"le lien fait partie de "<<resultat.count()<<" groupes";
   return resultat;
}
 QList<Lien*> dialogRelation::ordonnancer(QList <Lien*> * leGroupe)
{
    QList<Lien*> leGroupeOrdonnance;
    //il va falloir ici mettre les tables dans l'ordre
    //trouver les extrémités puis partir d'une extrémité pour arriver à l'autre.
    QMap <QString,int> mapTables;
    foreach(Lien * leLien, *leGroupe)
    {
        if (mapTables.contains(leLien->t1->nomTable))
        {
            //incrementation
            mapTables[leLien->t1->nomTable]++;
        }
        else
        {
           mapTables[leLien->t1->nomTable]=1;
        }
        if (mapTables.contains(leLien->t2->nomTable))
        {
            //incrementation
            mapTables[leLien->t2->nomTable]++;
        }
        else
        {
           mapTables[leLien->t2->nomTable]=1;
        }
    }//fin du foreach
    //la map est Remplie on choisit une des tables qui n'est citée qu'une seule fois
    //c'est une extrémitée
    int noCellule=0;
    while(!(noCellule==mapTables.count() || mapTables.values()[noCellule]==1))
    {
        noCellule++;
    }//fin du while
    if(noCellule==mapTables.count())//aucune table n'apparait qu'une seule fois donc il y a un lien en trop
    {
        qDebug()<<"IMPOSSIBLE DE COMMENCER BOUCLE DANS LES LIAISONS entre les tables";

    }
    else//On peut commencer
    {
        //trouver le lien qui a pour t1 ou t2 la table citée dans mapTables[noCellule]
        QString nomTable=mapTables.keys()[noCellule];
        int indiceDuLien=0;
        while(!(leGroupe->at(indiceDuLien)->t1->nomTable==nomTable || leGroupe->at(indiceDuLien)->t2->nomTable==nomTable))
        {
            indiceDuLien++;
        }
        QString tableSuivante;
        (leGroupe->at(indiceDuLien)->t1->nomTable==nomTable)?
                tableSuivante=leGroupe->at(indiceDuLien)->t2->nomTable:
                tableSuivante=leGroupe->at(indiceDuLien)->t1->nomTable;
        leGroupeOrdonnance.append(leGroupe->at(indiceDuLien));
        QList<Lien*>groupeReduit=*leGroupe;
        groupeReduit.removeOne(leGroupe->at(indiceDuLien));
        leGroupeOrdonnance<<liensSuivants(groupeReduit,tableSuivante);
    }
return leGroupeOrdonnance;
#warning à faire et vite
}
QList<Lien *> dialogRelation::liensSuivants(QList<Lien *> lesLiensRestants, QString nomTable)
{
    QList<Lien*> resultat;
    if(lesLiensRestants.count()==1)
        resultat<<lesLiensRestants.at(0);
    else
    {
        foreach(Lien * unLien, lesLiensRestants)
        {
            if(unLien->t1->nomTable==nomTable || unLien->t2->nomTable==nomTable)
            {
                //on l'enlève des liens restants
                lesLiensRestants.removeOne(unLien);
                if(unLien->t1->nomTable==nomTable)
                resultat<<unLien<<liensSuivants(lesLiensRestants,unLien->t2->nomTable);
                else
                 resultat<<unLien<<liensSuivants(lesLiensRestants,unLien->t1->nomTable);
            }
        }
    }
    return resultat;
}

void dialogRelation::miseAJourResultat()
{
    //actualisation du résultat de la requête
    qDebug()<<"void dialogRelation::miseAJourResultat()";
    QStringList fromList;
    QList<QList <Lien*> *> listeDesGroupesDeLiens;
    //grouper les liens ensemble
    foreach(Lien * lienARanger ,vectLiens) //pour chaque lien de la planche
    {
        //je regarde si un groupe contient une des tables du lien si oui je le rajoute au groupe sinon je crée un groupe et je le mets dedans
        //bool leLienEstRange=false;//pour l'instant le lien n'est pas rangé
        //QList<lien*>* premierGroupe=NULL;
        //ici la boucle n'est pas fantastique car on peut supprimer un groupe de lien
        QList<QList <Lien*> *> listeDesGroupesAuquelEstRelieLeLienARanger= obtenirListeDesGroupesAuquelEstRelieLeLienARanger(lienARanger,listeDesGroupesDeLiens);
        //si le lien n'appartient encore à aucun groupe
        if(listeDesGroupesAuquelEstRelieLeLienARanger.empty())
        {
            //ajout d'un nouveau groupe de lien
            QList <Lien*>* nouveauGroupe= new QList <Lien*>;
            *nouveauGroupe<<lienARanger;
            listeDesGroupesDeLiens.append(nouveauGroupe);
            //deboggage
            qDebug()<<"nouveau groupe avec "<<lienARanger->t1->nomTable<<" "<<lienARanger->t2->nomTable;
        }
        else
        {
            //il peut être relié à deux groupes auquel cas il faut les fusionner
            if(listeDesGroupesAuquelEstRelieLeLienARanger.count()==2)
            {
                qDebug()<<"fusion de deux groupes necessaires"<<listeDesGroupesAuquelEstRelieLeLienARanger;
                listeDesGroupesAuquelEstRelieLeLienARanger.at(0)->append(*listeDesGroupesAuquelEstRelieLeLienARanger[1]); //<<*listeDesGroupesAuquelEstRelieLeLienARanger[1];
                *listeDesGroupesAuquelEstRelieLeLienARanger[0]<<lienARanger;
                listeDesGroupesDeLiens.removeOne(listeDesGroupesAuquelEstRelieLeLienARanger[1]);
                qDebug()<<"Nombre de groupe:"<<listeDesGroupesDeLiens.count();
            }
            //ou être dans un seul et il suffit alors d'y rajouter notre lien
            else
            {
                *listeDesGroupesAuquelEstRelieLeLienARanger[0]<<lienARanger;
                qDebug()<<"ajout de lien dans le groupe existant";
            }
        }

        /*foreach(QList<lien*>* groupeDeLiens,listeDesGroupesDeLiens)//pour chaque groupe de lien déjà trouvé
        {
            foreach(lien* unLien,*groupeDeLiens) //pour chaque lien de ce groupe
            {
                if (unLien->estRelieA(lienARanger)) //ajout du lienARanger au groupe
                {

                    if(premierGroupe!=NULL) //il appartient à deux groupes il faut donc fusionner les deux groupes
                    {
                        //fusionner premierGroupe et groupeDeLiens et ne pas le rajouter
                        *premierGroupe<<*groupeDeLiens;                 
                        groupeDeLiens->empty();
                        //et on supprime le groupeDeLiens puisqu'il a été fusionné avec le premier
                        listeDesGroupesDeLiens.removeOne(groupeDeLiens);

                    }
                    else
                    {
                        *groupeDeLiens<<lienARanger;
                        //memorisation du fait qu'il est dans un groupe essais infructueux du 27/01/2017
                        premierGroupe=groupeDeLiens;
#warning erreur ici
                    }
                    //dans les deux cas le lien et rangé
                    leLienEstRange=true;
                }
            }//fin du pour chaque lien de ce groupe
        }//fin du pour chaque groupe de lien*/
        //si le lien n'est toujours pas rangé alors il faut créer un groupe et le mettre dedans
       /* if(!leLienEstRange)
        {
            QList<lien*> *nouveauGroupe=new QList<lien*>;
            *nouveauGroupe<<lienARanger;
            listeDesGroupesDeLiens<<nouveauGroupe;
        }*/
    }//fin de pour chaque lien de la planche
    //
    //Dans chaque groupe les tables st reliées par les conditions
    //et entre chaque groupe le séparateur est la virgule
    QString from="";
    //formation de la liste des tables ajoutées

    QList <Table*> listeDesTablesRestantAMettreDansLeFrom;
    //au départ on y met ttes les tables
    foreach(Table* laTable, vectTables)
    {
        listeDesTablesRestantAMettreDansLeFrom.append(laTable);
    }
    bool desGroupesOnEteTrouves=false;
    qDebug()<<"Il y a "<<listeDesGroupesDeLiens.count()<<" groupes de lien";
    foreach(QList<Lien*> *groupeDeLiens,listeDesGroupesDeLiens)//pour chaque groupe de lien
    {
        qDebug()<<"voici un groupe************************";
        foreach(Lien * unLien,* groupeDeLiens)
        {
          qDebug()<<unLien->t1->nomTable<<" vers "<<unLien->t2->nomTable;
        }


        QString chaineDuGroupe;
        QList<Table*>tablesDuGroupe;
        //ordonnancer chaque groupe de lien
        groupeDeLiens=new QList<Lien*>(ordonnancer(groupeDeLiens));
        //pour chaque lien du groupe
        foreach(Lien* leLien,*groupeDeLiens)
        {

            QString typeDeJointure=leLien->typeDeJointure;
            QString condition;
            if(leLien->condition!=NULL) //si la jointure est autre que naturelle
                condition=leLien->condition->document()->toPlainText();
            //recup des deux tables du lien
            Table * t1=leLien->t1;
            Table * t2=leLien->t2;
            //on les enlève de la liste des Tables Restant A Mettre Dans Le From
            //listeDesTablesRestantAMettreDansLeFrom.removeAt(listeDesTablesRestantAMettreDansLeFrom.indexOf(t1));
            listeDesTablesRestantAMettreDansLeFrom.removeOne(t1);
            //listeDesTablesRestantAMettreDansLeFrom.removeAt(listeDesTablesRestantAMettreDansLeFrom.indexOf(t2));
            listeDesTablesRestantAMettreDansLeFrom.removeOne(t2);
            QString nomTableT1AvecAlias=t1->nomTable;
            if(t1->alias!="")nomTableT1AvecAlias+=" "+t1->alias;
            QString nomTableT2AvecAlias=t2->nomTable;
            if(t2->alias!="")nomTableT2AvecAlias+=" "+t2->alias;
            if(!tablesDuGroupe.contains(t1))//si t1 n'a pas encore été ajoutée
            {
                if(!tablesDuGroupe.contains(t2)) //ne contient ni t1 ni t2
                {
                    //ajout de t1 et t2 aux tables concernées par le groupe
                    tablesDuGroupe.append(t1);
                    tablesDuGroupe.append(t2);

                    chaineDuGroupe+=nomTableT1AvecAlias+" "+typeDeJointure+" JOIN "+nomTableT2AvecAlias;
                    if(typeDeJointure!="Natural" && typeDeJointure!="Cross")
                    {
                        chaineDuGroupe+=" on "+condition;
                    }
                }
                else //ne contient pas t1 mais contient t2
                {
                    //ajouter t1 aux tables du groupe
                     tablesDuGroupe.append(t1);
                    chaineDuGroupe+=" "+typeDeJointure+" JOIN "+nomTableT1AvecAlias;
                    if(typeDeJointure!="Natural"&& typeDeJointure!="Cross")
                    {
                        chaineDuGroupe+=" ON "+condition;
                    }

                }
            }//t1 a été déjà rajoutée
            else //contient t1
            {

                if(!tablesDuGroupe.contains(t2))
                {
                    tablesDuGroupe.append(t2);
                    chaineDuGroupe+=" "+typeDeJointure+" JOIN "+nomTableT2AvecAlias;
                    if(typeDeJointure!="Natural"&& typeDeJointure!="Cross")
                    {
                        chaineDuGroupe+=" ON "+condition;
                    }
                }
                else
                {
                    qDebug()<<"************************T2 existe DEJA********************";
                    //il y a un bug
                    close();
                }
            }
        }//fin du pour chaque groupe de lien
        if(!chaineDuGroupe.isEmpty())
        {
            if(!from.isEmpty()) from+=','; //en effet il faut relier les groupes par une virgule
            from+=chaineDuGroupe; //ajout de la chaineDuGroupe au from
            desGroupesOnEteTrouves=true;
        }
    }//fin du pour chaque groupe de liens
    //s'il y a des tables isolées
    if(!listeDesTablesRestantAMettreDansLeFrom.empty())
    {
        QStringList listeDesNomdesTablesRestantAMettreDansLeFrom;
        if(desGroupesOnEteTrouves) //il faut rajouter une , au from
            from+= ",";
        //formation de la liste des noms de table à rajouter au from
        foreach (Table* t, listeDesTablesRestantAMettreDansLeFrom)
        {
            QString nomComplet=t->nomTable;
            if(t->alias!="") nomComplet+=" "+t->alias;
            listeDesNomdesTablesRestantAMettreDansLeFrom.append(nomComplet);
        }

        from+= listeDesNomdesTablesRestantAMettreDansLeFrom.join(",");
    }

    qDebug()<<from;
    //recherche des champs à afficher et formation simultannée du where ainsi que du order by:
    QString select="SELECT ";
    QString where=" WHERE ";
    QString orderBy=" ORDER BY ";

    QStringList listeDesChosesAAfficher;
    QStringList listeDesChampsParticipantsAuTri;
    QStringList listeDuWhere;
    QMap<int,QString> maMap;
    foreach (Table * uneTable, vectTables)
    {
        foreach (Field * unChamp, uneTable->vecteurChamps)
        {

            QString nomCompletDuChamp;
            //dans le cas ou des modifs ont été tapées dans le champ il faut mettre le préfixe à l(intérieur ou pas du tout si c'est un champ libre
            if(unChamp->freeField)
            {
                nomCompletDuChamp=unChamp->document()->toPlainText();
            }
            else //champ natif de la table
            {
                //s'il n'a pas été trafiqué
                if(unChamp->nomInitial==unChamp->document()->toPlainText())
                {
                    //on le prefixe par le nom de la table ou son alias
                    QString alias=uneTable->alias;
                    if(alias.isEmpty()) alias=uneTable->nomTable;
                    nomCompletDuChamp=alias+"."+unChamp->nomInitial;
                }
                else nomCompletDuChamp=unChamp->document()->toPlainText();
            }
            if(unChamp->affiche) listeDesChosesAAfficher.append(nomCompletDuChamp);
            if(unChamp->getTri()!="") maMap[unChamp->numeroDansLeTri]=nomCompletDuChamp+" "+unChamp->getTri();//listeDesChampsParticipantsAuTri.insert(unChamp->numeroDansLeTri,nomCompletDuChamp+" "+unChamp->getTri());
            if(unChamp->cond!=NULL) listeDuWhere.append(nomCompletDuChamp+" "+unChamp->cond->document()->toPlainText());
        }
    }
    QStringList listeDesChosesDuGroupBy=listeDesChosesAAfficher;
    //ajout des champs libres:
    foreach (Field* leChamp,vectChampsLibres)
    {
        if(leChamp->affiche)
        {
            listeDesChosesAAfficher.append(leChamp->document()->toPlainText());
            if(!leChamp->alias.isEmpty())
            {
                listeDesChosesDuGroupBy.append(leChamp->alias);
            }
            else
            {
                QString sonTexte=leChamp->document()->toPlainText();
                if(sonTexte.contains(" AS "))
                {
                    QStringList qsl=sonTexte.split(" AS ");
                    listeDesChosesDuGroupBy.append(qsl[qsl.count()-1]);
                }
                else
                {
                    listeDesChosesDuGroupBy.append(leChamp->document()->toPlainText());
                }
            }
        }
    }
    if(!listeDesChosesAAfficher.empty() && m_ui->toolButtonDistinct->isChecked())
        select+=" DISTINCT ";
    //ATTENTION TEST
    //select +=listeDesChosesAAfficher.join(",");
    //Remplacé par
    QString what=selectDansLOrdre();
    select+=what;
    //regardons si les champs calculés participent au tri
    QString tabTri[]={"no","asc","desc"};
    for(int noChamp=0;noChamp<m_ui->listWidgetAggregates->count();noChamp++)
    {
        if(m_ui->listWidgetAggregates->item(noChamp)->data(34)!=0) //si le champ participe au tri
        {
            //attention au as
            QString nomSansAlias=m_ui->listWidgetAggregates->item(noChamp)->text().split(" AS ")[0];
            maMap[m_ui->listWidgetAggregates->item(noChamp)->data(35).toInt()]=nomSansAlias+" "+tabTri[m_ui->listWidgetAggregates->item(noChamp)->data(34).toInt()];
        }

    }

    //trier la liste des champs participants au tri par leur ordre d'apparition

    //order by
    //a partir de la map formation de la liste

    foreach (QString champ, maMap)
    {
        listeDesChampsParticipantsAuTri.append(champ);
    }
    orderBy+=listeDesChampsParticipantsAuTri.join(",");
    where+=listeDuWhere.join(" AND ");

    //ajouter maintenant au select les agrégats affichés
    //construire le having
    QString requete="";
    if(!what.isEmpty())
    {
        requete=select;
        if(!(from.isEmpty()))
        {
            requete+=" FROM "+from;
        }
        if(!listeDuWhere.empty())
        {
            requete+=where;
        }
         //ajouter ici group by et having
        if(m_ui->checkBoxGroupBy->isChecked())
        {
            if(!listeDesChosesAAfficher.empty())
                requete+= " GROUP BY "+listeDesChosesDuGroupBy.join(",");
        }
        if(!m_ui->lineEditHaving->text().isEmpty())
        {
            requete+= " HAVING "+m_ui->lineEditHaving->text();
        }
        if(!listeDesChampsParticipantsAuTri.empty())
        {
            requete+=orderBy;
        }
    }
    QString limit;
    if(! m_ui->lineEditIndex->text().isEmpty() || ! m_ui->lineEditCount->text().isEmpty())
    {
        limit=" LIMIT ";
        limit+=(! m_ui->lineEditCount->text().isEmpty())?m_ui->lineEditCount->text():"1";
        limit+=" OFFSET ";
        limit+=(! m_ui->lineEditIndex->text().isEmpty())?m_ui->lineEditIndex->text():"1";

    }
    if(!limit.isEmpty()) requete+=limit;
    m_ui->lineEditQuery->setText(requete);



}

void dialogRelation::changeJoinType(Lien * leLien)
{   //appelé par le menu contextuel changer le type du lien
    qDebug()<<"void dialogRelation::changeJoinType(lien * leLien)";
    DialogTypeJointure dd;
    if(dd.exec())
    {
        if(leLien->typeDeJointure!=dd.m_ui->comboBoxType->currentText())//si le nouveau type est différent de l'ancien
        {
            leLien->typeDeJointure=dd.m_ui->comboBoxType->currentText();
            leLien->updateType();
            miseAJourResultat();
        }
    }
}
void dialogRelation::supprimerLien(Lien * leLien)
{
    qDebug()<<"void dialogRelation::supprimerLien(lien * leLien)";
    //effacement du lien dans le vecteur central:
    vectLiens.remove(vectLiens.indexOf(leLien),1);
    delete leLien;
    //rafraichissement de la requête
    miseAJourResultat();
}

void dialogRelation::on_lineEditQuery_textChanged(QString leSql )
{
    QSqlQuery req;
    requeteOk=false;
    //on vide la listeDesChampsDuResultat
    int nbDeChamp=listeDesChampsDuResultat.count();
    for(int noChamp=0;noChamp<nbDeChamp;noChamp++)
    {
        listeDesChampsDuResultat.removeAt(0);
    }

    qDebug()<<"void dialogRelation::on_lineEditQuery_textChanged(QString leSql )";
    qlonglong nbLignes;
    if(m_ui->toolButtonApercuAuto->isChecked())
    {

        //attention aux big queries
        //essais d'obtention du nombre de lignes concernées:
        QStringList qsl=leSql.split("FROM");
        bool affichageDemande=true;
        if(qsl.count()==2)
        {


            QString qStringNombreDeLigne="select count(*) from "+qsl.at(1);
            qDebug()<<qStringNombreDeLigne;
            if(req.exec(qStringNombreDeLigne))
            {
                req.first();
                nbLignes=req.value(0).toLongLong();
                qDebug()<<"Nombre de ligne:"<<nbLignes;
                if(nbLignes>100)
                {
                    if(QMessageBox::warning(this,this->windowTitle(),tr("The row count is ")+QString::number(nbLignes)+tr("\r\n are you really sure you want to display them?"),QMessageBox::Yes|QMessageBox::No,QMessageBox::No)==QMessageBox::No)
                    {
                        affichageDemande=false;
                    }
                }
                //affichage de l'importance du résultat

            }
            else
            {
                //affichageDemande=false;
                qDebug()<<"la requête permettant d'obtenir le nb de ligne a échoué";
            }
        }

        if(affichageDemande)
        {
            if (req.exec(leSql))
            {

                //m_ui->tableWidgetPreview->setStyleSheet("background-color:green");
                m_ui->pushButtonQueryState->setStyleSheet("background-color:green;color:yellow;");
                m_ui->tableWidgetPreview->clear();

                //si aperçu auto alors affichage du résultat de la requête

                //affichage des titres
                //req.first();
                QSqlRecord leRecord=req.record();
                int nbDeChamp=leRecord.count();
                //la requête est ok si le nb de champ est supérieur à 0
                requeteOk=nbDeChamp>0;
                if(requeteOk)
                {
                    for(int noChamp=0;noChamp<leRecord.count();noChamp++)
                    {
                      listeDesChampsDuResultat<<leRecord.fieldName(noChamp);
                    }
                    messageDErreur=tr("Query seems good,\n no error detected");
                }
                m_ui->tableWidgetPreview->setColumnCount(nbDeChamp);
                QStringList listeDesNomsDeChamp;
                for(int noCol=0;noCol<leRecord.count();noCol++)
                {
                    listeDesNomsDeChamp<<leRecord.fieldName(noCol);      
                }
                m_ui->tableWidgetPreview->setHorizontalHeaderLabels(listeDesNomsDeChamp);
                 for(int noCol=0;noCol<leRecord.count();noCol++)
                {

                    m_ui->tableWidgetPreview->horizontalHeaderItem(noCol)->setFont(QFont("verdana",10,5,true));
                }
                int noLigne=0;
                m_ui->tableWidgetPreview->setRowCount(0);

                while(!(!req.next()||noLigne==500))
                {

                    m_ui->tableWidgetPreview->setRowCount(m_ui->tableWidgetPreview->rowCount()+1);
                    for(int noChamp=0;noChamp<leRecord.count();noChamp++)
                    {
                        m_ui->tableWidgetPreview->setItem(noLigne,noChamp,new QTableWidgetItem(req.value(noChamp).toString()));
                    }
                    noLigne++;
                    m_ui->progressBarResultat->setValue(((double)noLigne/(double)nbLignes)*100);
                }
                if(noLigne==500)
                {
                    QMessageBox::critical(this,this->windowTitle(),tr("The result is to big to be displayed entirely"),QMessageBox::Ok);
                }
            }
        }


    }
    //si la requête n'est pas bonne
    if(!(requeteOk))
        {
            //m_ui->tableWidgetPreview->setStyleSheet("background-color:red");
            m_ui->pushButtonQueryState->setStyleSheet("background-color:red;color:white;");
            m_ui->tableWidgetPreview->clear();
            m_ui->tableWidgetPreview->setRowCount(0);
            m_ui->tableWidgetPreview->setColumnCount(0);
            m_ui->tableWidgetPreview->clear();
            //message d'erreur
            messageDErreur=req.lastError().text();


        }
    //activation/désactivation du bouton exporter au format csv
    m_ui->pushButtonExportCsv->setEnabled(requeteOk);

}

void dialogRelation::on_toolButtonApercuAuto_clicked()
{
    qDebug()<<"void dialogRelation::on_toolButtonApercuAuto_clicked()";
    //m_ui->toolButtonApercuAuto->setChecked(!m_ui->toolButtonApercuAuto->isChecked());
    if(m_ui->toolButtonApercuAuto->isChecked())
    {
        //icon
        m_ui->toolButtonApercuAuto->setIcon(QIcon(":/previewOn"));
        emit on_lineEditQuery_textChanged(m_ui->lineEditQuery->text());
    }
    else
    {
        m_ui->toolButtonApercuAuto->setIcon(QIcon(":/previewOff"));
    }
}

void dialogRelation::allezAllezOnAjouteLesTables(QPoint lePoint=QPoint(0,0))
{
    qDebug()<<"void dialogRelation::allezAllezOnAjouteLesTables(QPoint lePoint)";
    //ajout de la table sélectionnée à la customGraphicsView
    if(!m_ui->listWidgetTables->selectedItems().empty())
    {

        foreach(QListWidgetItem * qlwi,m_ui->listWidgetTables->selectedItems())
        {
            QString nomTable=qlwi->text();
            QSqlQuery req("select * from "+nomTable,db);
            QSqlRecord enr=req.record();
            QStringList listeDesChamps;

            for(int noChamp=0;noChamp<enr.count();noChamp++)
            {
                listeDesChamps<<enr.fieldName(noChamp);
            }
            Table* tableAjoutee=new Table(this,nomTable,0,0,0,&scene,listeDesChamps);
            if (lePoint.x()==0 &&lePoint.y()==0)
            {
                //calcul de la position la plus sympa
                //il va falloir travailler sur ce prochainX
                lePoint=QPoint(prochainX,30);
            }
            tableAjoutee->setPos(lePoint);

            ajouteTable(tableAjoutee);
        }
        m_ui->listWidgetTables->clearSelection();
    }
}

void dialogRelation::on_listWidgetTables_itemSelectionChanged()
{
    qDebug()<<"void dialogRelation::on_listWidgetTables_itemSelectionChanged()";
    m_ui->toolButtonAddTables->setEnabled(!m_ui->listWidgetTables->selectedItems().empty());
}

void dialogRelation::on_pushButtonQuitter_clicked()
{
    close();
}
void dialogRelation::closeEvent(QCloseEvent * event)
{
    qDebug()<<"void dialogRelation::closeEvent(QCloseEvent * event)";
    if(QMessageBox::warning(this,this->windowTitle(),tr("Do you really want to Quit"),QMessageBox::Yes|QMessageBox::No,QMessageBox::No)==QMessageBox::Yes)
    {
        event->accept();
    }
    else event->ignore();
}
void dialogRelation::on_toolButtonFitInView_clicked()
{
    qDebug()<<"void dialogRelation::on_toolButtonFitInView_clicked()";
    m_ui->graphicsView->fitInView(m_ui->graphicsView->sceneRect());
}
void dialogRelation::on_checkBoxGroupBy_clicked()
{
    qDebug()<<"void dialogRelation::on_checkBoxGroupBy_clicked()";
    this->miseAJourResultat();
}
void dialogRelation::on_pushButtonAddAggregate_clicked()
{
    qDebug()<<"void dialogRelation::on_pushButtonAddAggregate_clicked()";
    if(m_ui->lineEditAgregate->text().contains(" as "))
    {
        QListWidgetItem * agregat=new QListWidgetItem(0,1002) ;
        //agregat->setFlags (agregat->flags () | Qt::ItemIsEditable);
        agregat->setText(m_ui->lineEditAgregate->text());
        agregat->setData(34,0);//pas de tri
        agregat->setData(33,false);//pas affiché
        agregat->setData(32,0);//no ds le select
        agregat->setData(35,0);//no ds le tri

        m_ui->listWidgetAggregates->addItem(agregat);
        m_ui->lineEditAgregate->setText("");//j'efface la zone de saisie
        miseAJourResultat();
        //active/desactive le having
        m_ui->lineEditHaving->setEnabled(m_ui->listWidgetAggregates->count()>0);
    }
    else
    {
        QMessageBox::warning(this, this->windowTitle()+tr("add aggregate"),tr("Alias is often needed Sample: \"as average\"\n so please complete your input"));
    }
 }
//menu contextuel de la liste des agrégats


void dialogRelation::on_listWidgetAggregates_itemClicked(QListWidgetItem* item)
{
    qDebug()<<"void dialogRelation::on_listWidgetAggregates_itemClicked(QListWidgetItem* item)";
    m_ui->lineEditAgregate->setText(item->text());
    //et effacement de l'elt
    m_ui->listWidgetAggregates->takeItem(m_ui->listWidgetAggregates->currentRow());
    miseAJourResultat();
    m_ui->lineEditHaving->setEnabled(m_ui->listWidgetAggregates->count()>0);
}



void dialogRelation::on_toolButtonSO_clicked()
{
    qDebug()<<"void dialogRelation::on_toolButtonSO_clicked()";
    dialogSortOrder * ds;
    ds=new dialogSortOrder(this);
    ds->setWindowTitle(this->windowTitle()+tr("Define sort order"));
    //remplissage de la liste
    //pour chaque champ participant au tri affichage dans la liste et dans l'ordre s''il vous plait
    foreach (Table * uneTable, vectTables)
    {
        foreach (Field * unChamp, uneTable->vecteurChamps)
        {

            QString nomCompletDuChamp;
            //dans le cas ou des modifs ont été tapées dans le champ il faut mettre le préfixe à l(intérieur ou pas du tout si c'est un champ libre
            if(unChamp->freeField)
            {
                nomCompletDuChamp=unChamp->document()->toPlainText();
            }
            else //champ natif de la table
            {
                //s'il n'a pas été trafiqué
                if(unChamp->nomInitial==unChamp->document()->toPlainText())
                {
                    //on le prefixe par le nom de la table ou son alias
                    QString alias=uneTable->alias;
                    if(alias.isEmpty()) alias=uneTable->nomTable;
                    nomCompletDuChamp=alias+"."+unChamp->nomInitial;
                }
                else nomCompletDuChamp=unChamp->document()->toPlainText();
            }

            if(unChamp->getTri()!="")//s'il participe au tri
            {
                QListWidgetItem * item=new QListWidgetItem(0,1001);
                item->setText(nomCompletDuChamp);
                item->setData(32,(qlonglong) unChamp);
                item->setData(33,"champ");
                //qDebug()<<unChamp->nomInitial<<(qlonglong) unChamp<<"numéro"<<unChamp->numeroDansLeTri;
                ds->m_ui->listWidgetChamps->insertItem(unChamp->numeroDansLeTri,item);
            }
        }
    }
    //ajout des aggrégats participant au tri
    for(int no=0;no<m_ui->listWidgetAggregates->count();no++)
    {
        if(m_ui->listWidgetAggregates->item(no)->data(34).toInt()!=0)
        {
                QListWidgetItem * item=new QListWidgetItem(0,1001);
                item->setText(m_ui->listWidgetAggregates->item(no)->text());
                item->setData(32,(qlonglong) m_ui->listWidgetAggregates->item(no));
                item->setData(33,"aggregate");
                //qDebug()<<unChamp->nomInitial<<(qlonglong) unChamp<<"numéro"<<unChamp->numeroDansLeTri;
                ds->m_ui->listWidgetChamps->insertItem(m_ui->listWidgetAggregates->item(no)->data(35).toInt(),item);
        }
    }
    if(ds->exec())
    {
        for(int noChamp=0;noChamp<ds->m_ui->listWidgetChamps->count();noChamp++)
        {
            //qDebug()<<"coucou";
            QListWidgetItem * item=ds->m_ui->listWidgetChamps->item(noChamp);
            if(item->data(33).toString()=="champ")
            {
                Field* leChamp=(Field*)(item->data(32).toLongLong());
                leChamp->numeroDansLeTri=noChamp;
            }
            else
            {
                QListWidgetItem * agregate=(QListWidgetItem *)(item->data(32).toLongLong());
                agregate->setData(35,noChamp);
            }
            //qDebug()<<item->text()<<item->data(32).toLongLong();
        }
        //rafraichissement
        miseAJourResultat();

    }
}

void dialogRelation::on_toolButtonDistinct_clicked()
{
    qDebug()<<"void dialogRelation::on_toolButtonDistinct_clicked()";
    miseAJourResultat();
}

void dialogRelation::on_actionZoom_in_triggered()
{
    qDebug()<<"void dialogRelation::on_actionZoom_in_triggered()";
  m_ui->graphicsView->zoomIn();
}

void dialogRelation::on_actionZoom_out_triggered()
{
  qDebug()<<"void dialogRelation::on_actionZoom_in_triggered()";
  m_ui->graphicsView->zoomOut();
}
QMap <int,QString> dialogRelation::mapSelect()
{
    QMap<int,QString> maMap;
    //on commence par ajouter les champs des tables
    foreach (Table * uneTable, vectTables)
    {
        foreach (Field * unChamp, uneTable->vecteurChamps)
        {
            if(unChamp->affiche) maMap[unChamp->numeroOrdreDansLeSelect]=unChamp->getNomComplet();

        }
    }
    //puis on passe aux champs en dehors des tables(les champs libres
    //ajout des champs libres devant être affichés:
    foreach (Field* leChamp,vectChampsLibres)
    {
        if(leChamp->affiche) maMap[leChamp->numeroOrdreDansLeSelect]=leChamp->document()->toPlainText();
    }
    //et enfin les champs calculés
    for(int noChamp=0;noChamp<m_ui->listWidgetAggregates->count();noChamp++)
    {
        //si le champ doit être affiché
        if(m_ui->listWidgetAggregates->item(noChamp)->data(33).toBool())
        {
          //ds data(32) on a l'ordre ds le select
          maMap[m_ui->listWidgetAggregates->item(noChamp)->data(32).toInt()]=m_ui->listWidgetAggregates->item(noChamp)->text();
        }
    }
    return maMap;
}
QString dialogRelation::selectDansLOrdre()
{
    qDebug()<<"QString dialogRelation::selectDansLOrdre()";
    //renvoie la chaine avant le from
    QStringList sl;
    foreach (QString valeur,mapSelect())
    {
        sl<<valeur;
    }
    return sl.join(",");
}
int dialogRelation::maxCleDeLaMap()
{   qDebug()<<"int dialogRelation::maxCleDeLaMap()";
    //renvoie le + gros numéro d'affichage donc le numéro d'ordre du champ juste avant le from
    int max=0;

    foreach (int valeur,mapSelect().keys())
    {
        if(max<valeur) max=valeur;
    }
    return max;
}
int dialogRelation::nombreDeChampsDansLeSelect()
{
    qDebug()<<"int dialogRelation::nombreDeChampsDansLeSelect()";
    return mapSelect().count();
}

void dialogRelation::on_pushButtonExportCsv_clicked()
{
    qDebug()<<"void dialogRelation::on_pushButtonExportCsv_clicked()";
    //export du résultat au format csv
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setNameFilter(tr("Text files (*.csv *.txt)"));
    if(dialog.exec())
    {
        QFile fichierCsv(dialog.selectedFiles()[0]);
        if(fichierCsv.open(QIODevice::WriteOnly|QIODevice::Text))
        {
            for(int noLigne=0;noLigne<m_ui->tableWidgetPreview->rowCount();noLigne++)
            {
                QStringList ligne;
                for(int noCol=0;noCol<m_ui->tableWidgetPreview->columnCount();noCol++)
                {
                    ligne.append(m_ui->tableWidgetPreview->item(noLigne,noCol)->text());
                }
                fichierCsv.write(ligne.join(";").toLatin1());
                fichierCsv.write("\n");
            }
        }
        fichierCsv.close();
    }

}

void dialogRelation::on_lineEditAgregate_textChanged(QString leContenu)
{
    qDebug()<<"void dialogRelation::on_lineEditAgregate_textChanged(QString leContenu)";
    m_ui->pushButtonAddAgregate->setEnabled( !leContenu.isEmpty());
}

void dialogRelation::on_toolButtonAddTables_clicked()
{
    emit(ilYADesTablesAAjouter(QPoint(0,0)));
}
void dialogRelation::ajouteTable(Table* t)
{

        vectTables.append(t);
        prochainX=t->pos().x()+t->boundingRect().width()+10;
        t->setFlag(QGraphicsItem::ItemIsSelectable);
        t->setFlag(QGraphicsItem::ItemIsMovable);
        t->setFlag(QGraphicsItem::ItemSendsGeometryChanges);
        //essais
        scene.addItem(t);

}

void dialogRelation::on_pushButtonQueryState_clicked()
{
    qDebug()<<"void dialogRelation::on_pushButtonQueryState_clicked()";

   QMessageBox::information(this, windowTitle()+tr(" Database Message"),
                                messageDErreur,
                                QMessageBox::Ok,
                                QMessageBox::Ok);


}

void dialogRelation::on_customContextMenuAggregate(QPoint p)
{
    qDebug()<<"void dialogRelation::on_customContextMenuAggregate(QPoint p)";
    if(m_ui->listWidgetAggregates->selectedItems().count()>0)
    {
        QMenu menuDeLaListeDesAggregats(this);
        QAction * afficher=menuDeLaListeDesAggregats.addAction(tr("&Display(y/n)"));

        QMenu* menu2= menuDeLaListeDesAggregats.addMenu(tr("Sort order"));
        QAction * asc=menu2->addAction(tr("&Asc"));
        QAction * desc=menu2->addAction(tr("&Desc"));
        QAction * off=menu2->addAction(tr("&Off"));

        QAction * actionChoisie=menuDeLaListeDesAggregats.exec(m_ui->listWidgetAggregates->mapToGlobal(p));
        //gestion de l'action choisie:
        QListWidgetItem * eltSelectionne=m_ui->listWidgetAggregates->selectedItems()[0];
        uint affichee=33;
        uint sort=34;//0,1,2
        if (actionChoisie==afficher)
        {
            eltSelectionne->setData(affichee,!eltSelectionne->data(affichee).toBool());
            if(eltSelectionne->data(affichee).toBool())
            {
                eltSelectionne->setIcon(QIcon(QPixmap(":/mini-eye.xpm")));
                //on le met comme dernierChamp affiché
                eltSelectionne->setData(32,maxCleDeLaMap()+1);
            }
            else
                eltSelectionne->setIcon(QIcon(""));
            //ds ts les cas
            miseAJourResultat();
        }
        else
        {
            if(actionChoisie==asc ||actionChoisie==desc ||actionChoisie==off)
            {
                if(actionChoisie==asc)eltSelectionne->setData(sort,1);
                if(actionChoisie==desc)eltSelectionne->setData(sort,2);
                if(actionChoisie==off)eltSelectionne->setData(sort,0);
                eltSelectionne->setData(35,0);//numéro dans le tri
                miseAJourResultat();
            }
        }
    }
}

void dialogRelation::on_actionDelete_tables_s_triggered()
{
    qDebug()<<"void dialogRelation::on_actionDelete_tables_s_triggered()";
    tableSupprimer();
}
