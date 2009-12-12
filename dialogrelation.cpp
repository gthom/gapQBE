#include "dialogrelation.h"
#include "ui_dialogrelation.h"
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
    db.open();
    //recup des tables de la base
    QStringList listeDesTables=db.tables();
    m_ui->listWidgetTables->insertItems(0,listeDesTables);
    m_ui->graphicsView->setScene(&scene);
    m_ui->tableWidgetSelect->addAction(m_ui->actionSuprime);
    m_ui->tableWidgetSelect->setContextMenuPolicy(Qt::ActionsContextMenu);
    connect (m_ui->graphicsView,SIGNAL(jointureRequise(QString,QString)),this,SLOT(jointure(QString,QString)));
    connect(m_ui->toolButtonExecuteRequete,SIGNAL(clicked()),this,SLOT(miseAJourResultat()));
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

void dialogRelation::on_actionSuprime_triggered()
{
    //supression d'un ou plusieurs champ(s) de la tablewidget work
    if(!m_ui->tableWidgetSelect->selectedItems().empty())
    {
        //suppression des colonnes sélectionnées
        int nbChampASupprimer=m_ui->tableWidgetSelect->selectedItems().count();
        QList <int> colonnesASupprimer;


        for(int noSelection=0;noSelection<nbChampASupprimer;noSelection++)
        {
            //obtention de la colonne
            int nColonne=m_ui->tableWidgetSelect->column(m_ui->tableWidgetSelect->selectedItems()[noSelection]);
            if(!colonnesASupprimer.contains(nColonne))
            {
                colonnesASupprimer.push_back(nColonne);
            }
        }
        qSort(colonnesASupprimer);
        for(int no=colonnesASupprimer.size()-1;no>=0;no--)
        {  int nColonne=colonnesASupprimer[no];
            m_ui->tableWidgetSelect->removeColumn(nColonne);
        }
    }
}


void dialogRelation::tableSupprimer()
{
    //supprime une table dans la graphics view
    table*t=(table*)(scene.selectedItems().first());
    foreach (QGraphicsItem *item, scene.selectedItems())
    {
         if (item->data(32) == "Table") {
             //on enlève les liens de la scene
             foreach (lien * theLien,((table*)item)->vectLiens)
             {
                 //on enleve le lien de la scene
                 scene.removeItem(theLien);
             }
         //on enleve la table de la scene
         scene.removeItem(item);
         }

     }

    //suppression des liens concernant la table
    for(int noLien=vectLiens.size()-1;noLien>=0;noLien--)
    {
        if(vectLiens[noLien]->t1==t ||vectLiens[noLien]->t2==t)
        {
            vectLiens.remove(noLien,1);

        }
    }
    //puis
    //supprime une des tables ajoutée
    vectTables.remove(vectTables.indexOf(t));
}

void dialogRelation::jointure(QString t1,QString t2)
{
    //j'affiche une boite de dialogue pour saisir le type de jointure
    DialogTypeJointure dtj;
    //puis je trouve les deux tables dans le vecteur et ajoute le lien dans la tables des liens
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
                if(vectTables[indice]->nomTable==t1)
                {
                    table1=vectTables[indice];
                }
                if(vectTables[indice]->nomTable==t2)
                {table2=vectTables[indice];
                }
                indice++;

            }
            lien * nouveauLien=new lien(table1,table2,0,&this->scene,typ);
            table1->vectLiens.push_back(nouveauLien);
            table2->vectLiens.push_back(nouveauLien);
            vectLiens.push_back(nouveauLien);

        }
    }
}

void dialogRelation::on_pushButtonAdd_clicked()
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
    //table* laTable=(table*)sender();
    qDebug()<<"void dialogRelation::tableAjouterChamp()";
    QString nomDuChamp="'Some Text'";
    field* nouveauChamp=new field(false,&scene,nomDuChamp,laTable);
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
        foreach(QList<lien*>* groupeDeLiens,listeDesGroupesDeLiens)//pour chaque groupe de lien
        {
            foreach(lien* unLien,*groupeDeLiens) //pour chaque lien de ce groupe
            {
                if (unLien->estRelieA(lienARanger)) //ajout du lienARanger au groupe
                {
                    *groupeDeLiens<<lienARanger;
                    leLienEstRange=true;
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
    QString from=" FROM ";
    //formation de la liste des tables ajoutées
    QStringList listeDesNomdesTablesRestantAMettreDansLeFrom;
    foreach(table* laTable, vectTables)
    {
        listeDesNomdesTablesRestantAMettreDansLeFrom.append(laTable->nomTable);
    }
    foreach(QList<lien*> *groupeDeLiens,listeDesGroupesDeLiens)//pour chaque groupe de lien
    {
        QString chaineDuGroupe;
        foreach(lien* leLien,*groupeDeLiens)
        {
            QString typeDeJointure=leLien->typeDeJointure;
            QString condition;
            if(leLien->condition!=NULL) //si la jointure est autre que naturelle
            condition=leLien->condition->document()->toPlainText();

            table * t1=leLien->t1;
            table * t2=leLien->t2;
            listeDesNomdesTablesRestantAMettreDansLeFrom.removeAt(listeDesNomdesTablesRestantAMettreDansLeFrom.indexOf(t1->nomTable));
            listeDesNomdesTablesRestantAMettreDansLeFrom.removeAt(listeDesNomdesTablesRestantAMettreDansLeFrom.indexOf(t2->nomTable));
            if(!chaineDuGroupe.contains(t1->nomTable))//pas une bonne idée à recoder
            {
                if(!chaineDuGroupe.contains(t2->nomTable)) //ne contient ni t1 ni t2
                {
                    chaineDuGroupe+=t1->nomTable+" "+typeDeJointure+" JOIN "+t2->nomTable;
                    if(typeDeJointure!="Natural")
                    {
                        chaineDuGroupe+=" on "+condition;
                    }
                }
                else //ne contient pas t1 mais contient t2
                {
                    chaineDuGroupe+=" "+typeDeJointure+" JOIN "+t1->nomTable;
                    if(typeDeJointure!="Natural")
                    {
                        chaineDuGroupe+=" on "+condition;
                    }
                }
            }
            else //contient t1
            {
                chaineDuGroupe+=" "+typeDeJointure+" JOIN "+t2->nomTable;
                    if(typeDeJointure!="Natural")
                    {
                        chaineDuGroupe+=" on "+condition;
                    }
            }
        }//fin du pour chaque groupe de lien
        from+=chaineDuGroupe; //ajout de la chaineDuGroupe au from
    }
    if(!listeDesNomdesTablesRestantAMettreDansLeFrom.empty())
    {
        if(from != " FROM ") //pas tiptop à reprendre
            from+= ",";
        from+= listeDesNomdesTablesRestantAMettreDansLeFrom.join(",");
}

    qDebug()<<from;
    //recherche des champs à afficher et formation simultannée du where ainsi que du order by:
    QString select="select";
    QString where=" where ";
    QString orderBy=" order by ";

    QStringList listeDesChosesAAfficher;
    QStringList listeDesChampsParticipantsAuTri;
    QStringList listeDuWhere;
    foreach (table * uneTable, vectTables)
    {
        foreach (field * unChamp, uneTable->vecteurChamps)
        {
            if(unChamp->affiche) listeDesChosesAAfficher.append(uneTable->nomTable+"."+unChamp->document()->toPlainText());
            if(unChamp->getTri()!="") listeDesChampsParticipantsAuTri.append(uneTable->nomTable+"."+unChamp->document()->toPlainText()+" "+unChamp->getTri());
            if(unChamp->cond!=NULL) listeDuWhere.append(unChamp->document()->toPlainText()+unChamp->cond->document()->toPlainText());
        }
    }
    select +=listeDesChosesAAfficher.join(",");
    orderBy+=listeDesChampsParticipantsAuTri.join(",");
    where+=listeDuWhere.join(" and ");

    //ajouter maintenant au select les agrégats affichés
    //construire le having
    qDebug()<<select<<from<<where<<orderBy;
    //puis former le where


}

