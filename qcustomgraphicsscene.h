#ifndef QCUSTOMGRAPHICSSCENE_H
#define QCUSTOMGRAPHICSSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QDragEnterEvent>
#include <QGraphicsSceneContextMenuEvent>

class QCustomGraphicsScene : public QGraphicsScene
{
private:
    Q_OBJECT
public:
    QCustomGraphicsScene(QWidget *);
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
    QString outil;
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
};

#endif // QCUSTOMGRAPHICSSCENE_H
