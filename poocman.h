#ifndef POOCMAN_H
#define POOCMAN_H
#include "animationsprite.h"
#include "commonInfo.h"
#include "pacdot.h"
#include "ghost.h"
#include <QKeyEvent>

class Poocman : public AnimationSprite
{
public:
    Poocman(TimerProxy *, QString, QGraphicsScene *,Maze *);
    ~Poocman() override;

    void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *) override;
    QRectF boundingRect() const override;

    void setSpeed(double);
    double getSpeed();
    void setDirection(QPoint);
    QPoint getDirection();
    void spawn();


    double speed;
    QPoint direction;

    int currDir; // 0 up 1 down 2 right 3 left

    static int lives;
    static int dotsEaten;



protected:
    void keyPressEvent(QKeyEvent *) override;


};

#endif // POOCMAN_H
