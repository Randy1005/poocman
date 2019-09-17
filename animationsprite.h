#ifndef ANIMATIONSPRITE_H
#define ANIMATIONSPRITE_H


#include <QGraphicsObject>

class AnimationSprite : QGraphicsObject
{
public:
    AnimationSprite();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    // animation methods
    void startAnim(const QString &animName);


private:
    QPixmap *mSpriteImage;


private slots:
    void timeUpdated(int);


};

#endif // ANIMATIONSPRITE_H
