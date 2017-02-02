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
private:
    Q_OBJECT
public:
    customGraphicsView(QWidget * parent):QGraphicsView(parent){};
    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void dropEvent(QDropEvent *event);
    QString delimiteur;
signals:
    void jointureRequise(Table*,Table*);
    void ilYADesTablesAAjouter(QPoint);
    void supprimerTable(QString nomTable);
public slots:
    void zoomIn() { scale(1.2, 1.2); }
    void zoomOut() { scale(1 / 1.2, 1 / 1.2); }

};
#endif // CUSTOMGRAPHICSVIEW_H
