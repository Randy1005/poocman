#ifndef GHOST_H
#define GHOST_H
#include "animationsprite.h"
#include "commonInfo.h"

class Ghost : public AnimationSprite
{
public:
    Ghost(TimerProxy *, QString, QGraphicsScene *,Maze *);
    ~Ghost() override;

    void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *) override;
    QRectF boundingRect() const override;

    void setSpeed(double);
    double getSpeed();
    void setDirection(QPoint);
    QPoint getDirection();

    // set different colors for Blinky/Inky/Clyde [setting pixels]
    void setSpriteColor(QColor);


    double speed;
    QPoint direction;

    int currDir; // 0 up 1 down 2 right 3 left


};

#endif // GHOST_H
