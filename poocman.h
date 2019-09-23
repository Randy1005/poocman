#ifndef POOCMAN_H
#define POOCMAN_H
#include "animationsprite.h"
#include "commonInfo.h"
#include <QKeyEvent>

class Poocman : public AnimationSprite
{
public:
    Poocman(TimerProxy *, QString, QGraphicsScene *, QList<QList<bool>> map);
    ~Poocman() override;

    void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *) override;
    QRectF boundingRect() const override;

    void setSpeed(double);
    double getSpeed();
    void setDirection(QPoint);
    QPoint getDirection();


    double speed;
    QPoint direction;

protected:
    void keyPressEvent(QKeyEvent *) override;


};

#endif // POOCMAN_H
