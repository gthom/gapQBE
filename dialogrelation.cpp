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
#include    <QMessageBox>
#include "ui_dialogsortorder.h"


dialogRelation::dialogRelation(QWidget *parent,QSqlDatabase& pdb) :
        scene(this),
        QDialog(parent),
        m_ui(new Ui::dialogRelation)
{
    m_ui->setupUi(this);
    //abscisse de la prochaine table
    prochainX=20;
    //recup de la base
    db=db.cloneDatabase(pdb,"ploum");
    QMessageBox::warning(this,"pb",db.lastError().text());
    db.open();
    //recup des tables de la base
    QStringList listeDesTables=db.tables();
    m_ui->listWidgetTables->insertItems(0,listeDesTables);
    m_ui->graphicsView->setScene(&scene);


    connect (m_ui->graphicsView,SIGNAL(jointureRequise(table *,table *)),this,SLOT(jointure(table*,table*)));
    connect (m_ui->graphicsView,SIGNAL(ilYADesTablesAAjouter()),this,SLOT(on_toolButtonAddTables_clicked()));
    connect(m_ui->toolButtonExecuteRequete,SIGNAL(clicked()),this,SLOT(miseAJourResultat()));
    connect (m_ui->checkBoxGroupBy,SIGNAL(clicked()),this,SLOT(on_checkBoxGroupBy_clicked()));
    connect(m_ui->pushButtonAddAgregate,SIGNAL(clicked()),this,SLOT(on_pushButtonAddAggregate_clicked()));
    connect(m_ui->lineEditHaving,SIGNAL(textChanged(QString)),this,SLOT(miseAJourResultat()));
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

    foreach (QGraphicsItem *item, scene.selectedItems())
    {
        if (item->data(32) == "Table")
        {
            table*t=(table*)item;
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
            delete vectTables[noDeLaTableASupprimer];
            vectTables.remove(noDeLaTableASupprimer,1);
        }

    }//fin du foreach
    //mise à jour de la requête
    miseAJourResultat();

}

void dialogRelation::jointure(table* t1,table* t2)
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
            table * table1=NULL;
            table * table2=NULL;
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
            lien * nouveauLien=new lien(table2,table1,0,&this->scene,typ);
            table1->vectLiens.push_back(nouveauLien);
            table2->vectLiens.push_back(nouveauLien);
            vectLiens.push_back(nouveauLien);

        }
    }
}


void dialogRelation::on_toolButtonMove_clicked()
{
    //Choix de l'outil move
    scene.outil="move";
    m_ui->graphicsView->setCursor(QCursor(Qt::ArrowCursor));
}
void dialogRelation::on_toolButtonJoin_clicked()
{
    //choix de l'outil drag
    scene.outil="drag";
    m_ui->graphicsView->setCursor(QCursor(Qt::PointingHandCursor));
}
void dialogRelation::tableAjouterChamp(table * laTable)
{
    //but:Ajouter un champ libre à la table
    //   exemple select 'bonjour' from client
    //attention aux titres qui se font passer pour des tables

    qDebug()<<"void dialogRelation::tableAjouterChamp()";
    QString nomDuChamp="\"Some Text\"";
    field* nouveauChamp=new field(this,true,&scene,nomDuChamp,laTable);
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

    //THE end
}
void dialogRelation::miseAJourResultat()
{
    //actualisation du résultat de la requête
    qDebug()<<"void dialogRelation::miseAJourResultat()";
    QStringList fromList;
    QList<QList <lien*> *> listeDesGroupesDeLiens;
    //grouper les liens ensemble
    foreach(lien * lienARanger ,vectLiens) //pour chaque lien de la planche
    {
        //je regarde si un groupe contient une des tables du lien si oui je le rajoute au groupe sinon je crée un groupe et je le mets dedans
        bool leLienEstRange=false;//pour l'instant le lien n'est pas rangé
        QList<lien*>* premierGroupe=NULL;
        foreach(QList<lien*>* groupeDeLiens,listeDesGroupesDeLiens)//pour chaque groupe de lien
        {
            foreach(lien* unLien,*groupeDeLiens) //pour chaque lien de ce groupe
            {
                if (unLien->estRelieA(lienARanger)) //ajout du lienARanger au groupe
                {

                    if(premierGroupe!=NULL) //il appartient à deux groupes il faut donc fusionner les deux groupes
                    {
                        //fusionner premierGroupe et groupeDeLiens
                        *premierGroupe<<*groupeDeLiens;
                        groupeDeLiens->empty();
                        listeDesGroupesDeLiens.removeOne(groupeDeLiens);

                    }
                    else
                    {
                        *groupeDeLiens<<lienARanger;
                        leLienEstRange=true;
                    }
                }
            }
        }
        //si le lien n'est toujours pas rangé alors il faut créer un groupe et le mettre dedans
        if(!leLienEstRange)
        {
            QList<lien*> *nouveauGroupe=new QList<lien*>;
            *nouveauGroupe<<lienARanger;
            listeDesGroupesDeLiens<<nouveauGroupe;
        }
    }
    //
    //Dans chaque groupe les tables st reliées par les conditions
    //et entre chaque groupe le séparateur est la virgule
    QString from="";
    //formation de la liste des tables ajoutées

    QList <table*> listeDesTablesRestantAMettreDansLeFrom;
    //au départ on y met ttes les tables
    foreach(table* laTable, vectTables)
    {
        listeDesTablesRestantAMettreDansLeFrom.append(laTable);
    }
    bool desGroupesOnEteTrouves=false;
    foreach(QList<lien*> *groupeDeLiens,listeDesGroupesDeLiens)//pour chaque groupe de lien
    {
        QString chaineDuGroupe;
        QList<table*>tablesDuGroupe;
        foreach(lien* leLien,*groupeDeLiens)
        {
            QString typeDeJointure=leLien->typeDeJointure;
            QString condition;
            if(leLien->condition!=NULL) //si la jointure est autre que naturelle
                condition=leLien->condition->document()->toPlainText();
            //recup des deux tables du lien
            table * t1=leLien->t1;
            table * t2=leLien->t2;
            //on les enlève de la liste des Tables Restant A Mettre Dans Le From
            listeDesTablesRestantAMettreDansLeFrom.removeAt(listeDesTablesRestantAMettreDansLeFrom.indexOf(t1));
            listeDesTablesRestantAMettreDansLeFrom.removeAt(listeDesTablesRestantAMettreDansLeFrom.indexOf(t2));
            QString nomTableT1AvecAlias=t1->nomTable;
            if(t1->alias!="")nomTableT1AvecAlias+=" "+t1->alias;
            QString nomTableT2AvecAlias=t2->nomTable;
            if(t2->alias!="")nomTableT2AvecAlias+=" "+t2->alias;
            if(tablesDuGroupe.indexOf(t1)==-1)//si t1 n'a pas encore été ajoutée
            {
                if(tablesDuGroupe.indexOf(t2)==-1) //ne contient ni t1 ni t2
                {
                    //ajout de t1 et t2 aux tables concernées par le groupe
                    tablesDuGroupe.append(t1);
                    tablesDuGroupe.append(t2);

                    chaineDuGroupe+=nomTableT1AvecAlias+" "+typeDeJointure+" JOIN "+nomTableT2AvecAlias;
                    if(typeDeJointure!="Natural")
                    {
                        chaineDuGroupe+=" on "+condition;
                    }
                }
                else //ne contient pas t1 mais contient t2
                {
                    chaineDuGroupe+=" "+typeDeJointure+" JOIN "+nomTableT1AvecAlias;
                    if(typeDeJointure!="Natural")
                    {
                        chaineDuGroupe+=" on "+condition;
                    }
                    tablesDuGroupe.append(t1);
                }
            }
            else //contient t1
            {
                chaineDuGroupe+=" "+typeDeJointure+" JOIN "+nomTableT2AvecAlias;
                if(typeDeJointure!="Natural")
                {
                    chaineDuGroupe+=" on "+condition;
                }
                tablesDuGroupe.append(t2);
            }
        }//fin du pour chaque groupe de lien
        if(!chaineDuGroupe.isEmpty())
        {
            from+=chaineDuGroupe; //ajout de la chaineDuGroupe au from
            desGroupesOnEteTrouves=true;
        }
    }
    if(!listeDesTablesRestantAMettreDansLeFrom.empty())
    {
        QStringList listeDesNomdesTablesRestantAMettreDansLeFrom;
        if(desGroupesOnEteTrouves) //il faut rajouter une , au from
            from+= ",";
        //formation de la liste des noms de table à rajouter au from
        foreach (table* t, listeDesTablesRestantAMettreDansLeFrom)
        {
            QString nomComplet=t->nomTable;
            if(t->alias!="") nomComplet+=" "+t->alias;
            listeDesNomdesTablesRestantAMettreDansLeFrom.append(nomComplet);
        }
        from+= listeDesNomdesTablesRestantAMettreDansLeFrom.join(",");
    }

    qDebug()<<from;
    //recherche des champs à afficher et formation simultannée du where ainsi que du order by:
    QString select="select ";
    QString where=" where ";
    QString orderBy=" order by ";

    QStringList listeDesChosesAAfficher;
    QStringList listeDesChampsParticipantsAuTri;
    QStringList listeDuWhere;
    QMap<int,QString> maMap;
    foreach (table * uneTable, vectTables)
    {
        foreach (field * unChamp, uneTable->vecteurChamps)
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
    //ajout des champs libres:
    foreach (field* leChamp,vectChampsLibres)
    {
        listeDesChosesAAfficher.append(leChamp->document()->toPlainText());
    }
    if(!listeDesChosesAAfficher.empty() && m_ui->toolButtonDistinct->isChecked())
        select+=" distinct ";
    select +=listeDesChosesAAfficher.join(",");
    //ajouter ici les champs calculés
    QStringList listeDesChampCalcules;
    for(int noChamp=0;noChamp<m_ui->listWidgetAggregates->count();noChamp++)
    {
        listeDesChampCalcules<<m_ui->listWidgetAggregates->item(noChamp)->text();
    }
    if(!listeDesChampCalcules.empty())
    {
        if(!listeDesChosesAAfficher.empty())
        {
            select+=',';
        }
        select+=listeDesChampCalcules.join(",");
    }
    //trier la liste des champs participants au tri par leur ordre d'apparition

    //order by
    //a partir de la map formation de la liste
    foreach (QString champ, maMap)
    {
        listeDesChampsParticipantsAuTri.append(champ);
    }
    orderBy+=listeDesChampsParticipantsAuTri.join(",");
    where+=listeDuWhere.join(" and ");

    //ajouter maintenant au select les agrégats affichés
    //construire le having
    QString requete="";
    if(!listeDesChosesAAfficher.empty()||!listeDesChampCalcules.empty())
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
                requete+= " GROUP BY "+listeDesChosesAAfficher.join(",");
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


    m_ui->lineEditQuery->setText(requete);



}

void dialogRelation::changeJoinType(lien * leLien)
{   //appelé par le menu contextuel changer le type du lien
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
void dialogRelation::supprimerLien(lien * leLien)
{
    qDebug()<<"void dialogRelation::supprimerLien(lien * leLien)";
    //effacement du lien du vecteur de la table 1
    leLien->t1->vectLiens.remove(leLien->t1->vectLiens.indexOf(leLien),1);
    //effacement du lien du vecteur de la table 2
    leLien->t2->vectLiens.remove(leLien->t2->vectLiens.indexOf(leLien),1);
    //effacement du lien dans le vecteur central:
    vectLiens.remove(vectLiens.indexOf(leLien),1);
    delete leLien;
    //rafraichissement de la requête
    miseAJourResultat();
}

void dialogRelation::on_lineEditQuery_textChanged(QString leSql )
{   qlonglong nbLignes;
    qDebug()<<"void dialogRelation::on_lineEditQuery_textChanged(QString leSql )";
    if(m_ui->toolButtonApercuAuto->isChecked())
    {
        QSqlQuery req;
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
                    if(QMessageBox::warning(this,this->windowTitle(),"The row count is "+QString::number(nbLignes)+"\r\n are you really sure you want to display them?",QMessageBox::Yes|QMessageBox::No,QMessageBox::No)==QMessageBox::No)
                    {
                        affichageDemande=false;
                    }
                }
                //affichage de l'importance du résultat

            }
            else
            {
                affichageDemande=false;
                qDebug()<<"la requête permettant d'obtenir le nb de ligne a échoué";
            }
        }

        if(affichageDemande)
        {
            if (req.exec(leSql))
            {

                m_ui->tableWidgetPreview->setStyleSheet("background-color:green");
                m_ui->tableWidgetPreview->clear();
                //si aperçu auto alors affichage du résultat de la requête

                //affichage des titres
                //req.first();
                QSqlRecord leRecord=req.record();
                m_ui->tableWidgetPreview->setColumnCount(leRecord.count());
                QStringList listeDesNomsDeChamp;
                for(int noCol=0;noCol<leRecord.count();noCol++)
                {
                    listeDesNomsDeChamp<<leRecord.fieldName(noCol);
                }
                m_ui->tableWidgetPreview->setHorizontalHeaderLabels(listeDesNomsDeChamp);
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
                    QMessageBox::critical(this,this->windowTitle(),"The result is to big to be displayed entirely",QMessageBox::Ok);
                }
            }
        }
        else
        {
            m_ui->tableWidgetPreview->setStyleSheet("background-color:red");
            m_ui->tableWidgetPreview->clear();
            //todo: affichage du message d'erreur quelque part
        }

    }

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

void dialogRelation::on_toolButtonAddTables_clicked()
{
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
            table* tableAjoutee=new table(this,nomTable,0,0,0,&scene,listeDesChamps);
            tableAjoutee->setPos(prochainX,30);

            vectTables.push_back(tableAjoutee);
            prochainX+=tableAjoutee->boundingRect().width()+10;
            tableAjoutee->setFlag(QGraphicsItem::ItemIsSelectable);
            tableAjoutee->setFlag(QGraphicsItem::ItemIsMovable);
        }
        m_ui->listWidgetTables->clearSelection();
    }
}

void dialogRelation::on_listWidgetTables_itemSelectionChanged()
{
    m_ui->toolButtonAddTables->setEnabled(!m_ui->listWidgetTables->selectedItems().empty());
}

void dialogRelation::on_pushButtonQuitter_clicked()
{
    close();
}
void dialogRelation::closeEvent(QCloseEvent * event)
{
    if(QMessageBox::warning(this,this->windowTitle(),tr("Do you really want to Quit"),QMessageBox::Yes|QMessageBox::No,QMessageBox::No)==QMessageBox::Yes)
    {
        event->accept();
    }
    else event->ignore();
}
void dialogRelation::on_toolButtonFitInView_clicked()
{
    m_ui->graphicsView->fitInView(m_ui->graphicsView->sceneRect());
}
void dialogRelation::on_checkBoxGroupBy_clicked()
{

    this->miseAJourResultat();
}
void dialogRelation::on_pushButtonAddAggregate_clicked()
{
    QListWidgetItem * agregat=new QListWidgetItem(0,1002) ;
    agregat->setFlags (agregat->flags () | Qt::ItemIsEditable);
    agregat->setText(m_ui->lineEditAgregate->text());
    m_ui->listWidgetAggregates->addItem(agregat);
    m_ui->lineEditAgregate->setText("");
    miseAJourResultat();
 }
//menu contextuel de la liste des agrégats


void dialogRelation::on_listWidgetAggregates_itemClicked(QListWidgetItem* item)
{
    m_ui->lineEditAgregate->setText(item->text());
    //et effacement de l'elt
    m_ui->listWidgetAggregates->takeItem(m_ui->listWidgetAggregates->currentRow());
    miseAJourResultat();
}



void dialogRelation::on_toolButtonSO_clicked()
{
    dialogSortOrder * ds;
    ds=new dialogSortOrder(this);
    ds->setWindowTitle(this->windowTitle()+tr("Define sort order"));
    //remplissage de la liste
    //pour chaque champ participant au tri affichage dans la liste et dans l'ordre s''il vous plait
    foreach (table * uneTable, vectTables)
    {
        foreach (field * unChamp, uneTable->vecteurChamps)
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
                //qDebug()<<unChamp->nomInitial<<(qlonglong) unChamp<<"numéro"<<unChamp->numeroDansLeTri;
                ds->m_ui->listWidgetChamps->insertItem(unChamp->numeroDansLeTri,item);
            }
        }
    }
    if(ds->exec())
    {
        for(int noChamp=0;noChamp<ds->m_ui->listWidgetChamps->count();noChamp++)
        {
            //qDebug()<<"coucou";
            QListWidgetItem * item=ds->m_ui->listWidgetChamps->item(noChamp);
            field* leChamp=(field*)(item->data(32).toLongLong());
            leChamp->numeroDansLeTri=noChamp;
            qDebug()<<item->text()<<item->data(32).toLongLong();
        }
        //rafraichissement
       miseAJourResultat();

    }
}

void dialogRelation::on_toolButtonDistinct_clicked()
{
    miseAJourResultat();
}
