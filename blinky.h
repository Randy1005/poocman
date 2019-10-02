#ifndef BLINKY_H
#define BLINKY_H
#include "ghost.h"
#include "poocman.h"

class Blinky : public Ghost
{
public:
    Blinky(TimerProxy *, QString, QGraphicsScene *, Maze *, Poocman *);
    void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *) override;

    Poocman *pcman;

};

#endif // BLINKY_H
