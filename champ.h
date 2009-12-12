#ifndef CHAMP_H
#define CHAMP_H

#include <QListWidgetItem>
#include <QListWidget>
#include "mainwindow.h"
class MainWindow;
class champ : public QListWidgetItem
{
   private: MainWindow* maman;
           QString fieldType,fieldDefault,fieldSize,fieldCheck;
           bool fieldObligatoire;
public:
    QString fieldName;
    bool fieldPK;
    champ(QListWidget*,MainWindow *);
    void modification();
    void display();
    QString getFieldName() {return fieldName;}
};

#endif // CHAMP_H
