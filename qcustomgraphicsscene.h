#ifndef QCUSTOMGRAPHICSSCENE_H
#define QCUSTOMGRAPHICSSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QDragEnterEvent>

class QCustomGraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    QCustomGraphicsScene(QWidget *);
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
    QString outil;



};

#endif // QCUSTOMGRAPHICSSCENE_H
