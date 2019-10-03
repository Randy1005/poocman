#ifndef BLINKY_H
#define BLINKY_H
#include "ghost.h"
#include "poocman.h"
#include "node.h"
#include "math.h"
class Blinky : public Ghost
{
public:
    Blinky(TimerProxy *, QString, QGraphicsScene *, Maze *, Poocman *);
    void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *) override;
    QVector<Node *> aStar(Maze *, Node *, Node *);

    Poocman *pcman;
    QVector<QPoint> newPositions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};

};

#endif // BLINKY_H
