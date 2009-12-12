#ifndef DIALOGRELATION_H
#define DIALOGRELATION_H

#include <QtGui/QDialog>
#include "table.h"
#include <QGraphicsScene>
#include <QSqlDatabase>
#include <QMouseEvent>
#include "qcustomgraphicsscene.h"
#include "lien.h"
namespace Ui {
    class dialogRelation;
}
class table;
class lien;
class dialogRelation : public QDialog {
    Q_OBJECT
    Q_DISABLE_COPY(dialogRelation)
public:
    explicit dialogRelation(QWidget *parent,QSqlDatabase&);
    virtual ~dialogRelation();
    QSqlDatabase  db;//la database de travail
    long prochainX;//abscisse de la prochaine table insérée

protected:
    virtual void changeEvent(QEvent *e);

private:
    Ui::dialogRelation *m_ui;
    QVector <table*> vectTables;
    QVector <lien*> vectLiens;
    QCustomGraphicsScene scene;
private slots:

    void on_toolButtonJoin_clicked();//sélection de l'outil relier
    void on_toolButtonMove_clicked();//sélection de l'outil déplacer
    void on_pushButtonAdd_clicked();//ajout des tables sélectionnées à la requête
public slots:
    void on_actionSuprime_triggered();//suppression dans la QTableWidget work
    void tableSupprimer();//suppression d'une table dans la scene
    void tableAjouterChamp(table*);//ajout d'un champ libre dans une table de la scene
    void jointure(QString,QString);//jointure demandée entre deux tables de la scene
    void miseAJourResultat();//ce slot actualise la requête et le résultat de la requête
};

#endif // DIALOGRELATION_H
