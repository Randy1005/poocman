#ifndef CLYDE_H
#define CLYDE_H
#include "ghost.h"
#include <algorithm>
#include "mazegenerator.h"
#include <QKeyEvent>


class Clyde : public Ghost
{
public:
    Clyde(TimerProxy *, QString, QGraphicsScene *, Maze *);
    void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *) override;

    std::vector<int> availableDirs;
    QPoint directions[4] = {{0, -1}, {0, 1}, {1, 0}, {-1, 0}};

    unsigned seed;
    std::random_device rd;

protected:
    void keyPressEvent(QKeyEvent *event) override;

};

#endif // CLYDE_H
