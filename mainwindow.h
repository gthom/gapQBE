#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>

#include <QListWidgetItem>
// #include "champ.h"
//class champ;
namespace Ui
{
    class MainWindowClass;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);

    ~MainWindow();

    Ui::MainWindowClass *ui;
   private:
    //champ* selectionne;

private slots:
    void on_pushButtonCreerTable_clicked();
    void on_pushButtonModifier_clicked();
    void on_listWidgetChamps_itemClicked(QListWidgetItem* item);
    void on_pushButtonAjouter_clicked();
    void on_pushButtonQuitter_clicked();
    void on_action_Quitter_triggered();
    bool existe(QListWidget* laListe,QString nomChamp);
};

#endif // MAINWINDOW_H
