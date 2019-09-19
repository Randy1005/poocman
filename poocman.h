#ifndef POOCMAN_H
#define POOCMAN_H
#include "animationsprite.h"

class Poocman : public AnimationSprite
{
public:
    Poocman(TimerProxy *, QString);
    ~Poocman() override;

    void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *) override;
    QRectF boundingRect() const override;
};

#endif // POOCMAN_H
