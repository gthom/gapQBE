#ifndef DIALOGRELATION_H
#define DIALOGRELATION_H

#include <QtGui/QDialog>
#include "table.h"
#include <QGraphicsScene>
#include <QSqlDatabase>
#include <QMouseEvent>
#include <QListWidgetItem>
#include "qcustomgraphicsscene.h"
#include "lien.h"
namespace Ui {
    class dialogRelation;
}
class table;
class lien;
class field;
class dialogRelation : public QDialog {
    Q_OBJECT
    Q_DISABLE_COPY(dialogRelation)
public:
    explicit dialogRelation(QWidget *parent,QSqlDatabase&);
    virtual ~dialogRelation();
    QSqlDatabase  db;//la database de travail
    long prochainX;//abscisse de la prochaine table insérée
    Ui::dialogRelation * m_uip(){return m_ui;};
    QVector <field*> vectChampsLibres;
    //qlulques méthodes
    int nombreDeChampsDansLeSelect();//nb de champs affichés
    int maxCleDeLaMap();//numéro du dernier Champ affiché
    QString selectDansLOrdre();//chaîne avant le from sans select;
    QMap <int,QString> mapSelect();//renvoie la map numero d'ordre,chaine du champ

protected:
    virtual void changeEvent(QEvent *e);

private:
    Ui::dialogRelation *m_ui;
    QVector <table*> vectTables;

    QVector <lien*> vectLiens;
    QCustomGraphicsScene scene;
private slots:

    void on_lineEditAgregate_textChanged(QString );
    void on_pushButtonExportCsv_clicked();
    void on_actionZoom_out_triggered();
    void on_actionZoom_in_triggered();
    void on_toolButtonDistinct_clicked();
    void on_toolButtonSO_clicked();
    void on_listWidgetAggregates_itemClicked(QListWidgetItem* item);
    void on_pushButtonQuitter_clicked();
    void on_listWidgetTables_itemSelectionChanged();
    void on_toolButtonAddTables_clicked();
    void on_toolButtonApercuAuto_clicked();
    void on_lineEditQuery_textChanged(QString );
    void on_toolButtonJoin_clicked();//sélection de l'outil relier
    void on_toolButtonMove_clicked();//sélection de l'outil déplacer

public slots:

    void tableSupprimer();//suppression d'une table dans la scene
    void tableAjouterChamp(table*);//ajout d'un champ libre dans une table de la scene
    void jointure(table*,table*);//jointure demandée entre deux tables de la scene
    void miseAJourResultat();//ce slot actualise la requête et le résultat de la requête
    void changeJoinType(lien *);
    void supprimerLien(lien * leLien);
    void closeEvent(QCloseEvent * event);
    void on_toolButtonFitInView_clicked();//fi in view
    void on_checkBoxGroupBy_clicked();//group by clické
    void on_pushButtonAddAggregate_clicked();//ajout d'un agrégat


};

#endif // DIALOGRELATION_H
