#ifndef CUSTOMGRAPHICSVIEW_H
#define CUSTOMGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QMouseEvent>
#include <QDragEnterEvent>
#include <QDragMoveEvent>
#include <QDropEvent>
#include <QObject>
#include "table.h"


class customGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    customGraphicsView(QWidget * parent):QGraphicsView(parent){};
    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void dropEvent(QDropEvent *event);
signals:
    void jointureRequise(table*,table*);
    void ilYADesTablesAAjouter();
    void supprimerTable(QString nomTable);
};

#endif // CUSTOMGRAPHICSVIEW_H
