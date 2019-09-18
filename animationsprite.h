#ifndef ANIMATIONSPRITE_H
#define ANIMATIONSPRITE_H


#include <QGraphicsObject>
#include <QDebug>
#include "timerproxy.h"

class AnimationSprite : public QGraphicsObject
{
    Q_OBJECT

public:
    AnimationSprite(TimerProxy *);
    ~AnimationSprite();
    void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *);
    QRectF boundingRect() const = 0;


    // animation methods
    void startAnim(const QString &);



private slots:
    void timeUpdated(int);

private:
    QPixmap *mSpriteImage;

};

#endif // ANIMATIONSPRITE_H
