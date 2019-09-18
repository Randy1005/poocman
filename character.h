#ifndef CHARACTER_H
#define CHARACTER_H

#include "animationsprite.h"
#include "timerproxy.h"

class Character : public AnimationSprite
{
public:
    Character(TimerProxy *);
    ~Character() override;

    void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *) override;
    QRectF boundingRect() const override;

};

#endif // CHARACTER_H
