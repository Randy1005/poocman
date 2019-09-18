#include "animationsprite.h"

AnimationSprite::AnimationSprite(TimerProxy *tpro)
{
    // read anim descriptions (JSON file or any other format)


    // initialize mSpriteImage


    // connect SIGNAL(TimerProxy::updateTime(int msecs)) to SLOT(timeUpdated(int))
    connect(tpro, SIGNAL(updateTime(int)), this, SLOT(timeUpdated(int)));
}

AnimationSprite::~AnimationSprite() {

}

void AnimationSprite::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    // which version of drawPixmap is up to you
    // void QPainter::drawPixmap(int x, int y, const QPixmap &pixmap, int sx, int sy, int sw, int sh)

    // painter -> drawPixmap(...)
}

QRectF AnimationSprite::boundingRect() const {

}


/**
 * @brief change the current animation,
 *        reset the elapsed time counter,
 *        update the current sub-rect to draw to match the first frame of the new animation
 *
 * @param animName
 */
void AnimationSprite::startAnim(const QString &animName) {

}

void AnimationSprite::timeUpdated(int msecs) {
    qDebug() << "animated\n";
}
