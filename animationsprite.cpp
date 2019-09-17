#include "animationsprite.h"

AnimationSprite::AnimationSprite()
{
    // read anim descriptions (JSON file or any other format)
    // initialize mSpriteImage
    // connect SIGNAL(TimerProxy::updateTime(int msecs)) to SLOT(timeUpdated(int))
}

void AnimationSprite::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    // which version of drawPixmap is up to you
    // void QPainter::drawPixmap(int x, int y, const QPixmap &pixmap, int sx, int sy, int sw, int sh)

    // painter -> drawPixmap(...)
}


/**
 * @brief which will change the current animation,
 *        reset the elapsed time counter,
 *        and update the current sub-rect to draw to match the first frame of the new animation
 *
 * @param animName
 */
void AnimationSprite::startAnim(const QString &animName) {

}
