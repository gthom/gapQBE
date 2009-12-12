#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTextCodec>
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindowClass)
{
    ui->setupUi(this);
    QTextCodec::setCodecForTr(QTextCodec::codecForName("utf8"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_Quitter_triggered()
{
    close();
}

void MainWindow::on_pushButtonQuitter_clicked()
{
    close();
}

bool MainWindow::existe(QListWidget* laListe,QString nomChamp)
{
    bool trouve=false;
    int indice=0;
    while(!(trouve || indice>=laListe->count()))
    {
        if(((champ *)laListe->item(indice))->getFieldName()==nomChamp)
            trouve=true;
        else indice++;
    }
    return trouve;
}
void MainWindow::on_pushButtonAjouter_clicked()
{

    if(!existe(ui->listWidgetChamps,ui->lineEditNouveauFieldName->text()))
    {
    champ * nouveau=new champ(this->ui->listWidgetChamps,this);
    //je nettoie les zones de saisie
    ui->lineEditNouveauFieldName->setText("");
    ui->statusBar->showMessage(tr("le champ a été ajouté"));
}
    else ui->statusBar->showMessage(tr("le champ existe déjà"));


}

void MainWindow::on_listWidgetChamps_itemClicked(QListWidgetItem* item)
{
    selectionne=(champ*)item;
    ((champ*)item)->display();
}

void MainWindow::on_pushButtonModifier_clicked()
{
    selectionne->modification();
}
//a faire supression de champ
//creation de la   table
//contraintes de table

void MainWindow::on_pushButtonCreerTable_clicked()
{
    QString create;
    create="create table "+ ui->lineEditTableName->text()+"(";
    QString pk=",primary key(";
    bool firstChampDeLaPk=true;
    for(int noChamp=0;noChamp<ui->listWidgetChamps->count();noChamp++)
    {
        create+=ui->listWidgetChamps->item(noChamp)->text();
        champ * leChamp=(champ *)ui->listWidgetChamps->item(noChamp);
        if(leChamp->fieldPK)
        {
            if(!firstChampDeLaPk)pk+=",";
            pk+=leChamp->fieldName;
            firstChampDeLaPk=false;

        }
        if(noChamp<ui->listWidgetChamps->count()-1)create+=',';
    }
    //ajout eventuel de la primary key
    if(!firstChampDeLaPk) {pk+=')';create+=pk;}
    //boucle qui forme la primary key


    create+=");";
    QMessageBox::information(this,"sql",create);

}
