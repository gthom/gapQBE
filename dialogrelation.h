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
    Ui::dialogRelation * m_uip(){return m_ui;};
protected:
    virtual void changeEvent(QEvent *e);

private:
    Ui::dialogRelation *m_ui;
    QVector <table*> vectTables;
    QVector <lien*> vectLiens;
    QCustomGraphicsScene scene;
private slots:

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
    void jointure(QString,QString);//jointure demandée entre deux tables de la scene
    void miseAJourResultat();//ce slot actualise la requête et le résultat de la requête
    void changeJoinType(lien *);
    void supprimerLien(lien * leLien);
    void closeEvent(QCloseEvent * event);
    void on_toolButtonFitInView_clicked();//fi in view
};

#endif // DIALOGRELATION_H
