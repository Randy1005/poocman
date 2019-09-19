#include "animationsprite.h"

AnimationSprite::AnimationSprite(TimerProxy *tpro, QString name) : mSubRect(0, 0, 1, 1), mCurrAnim("idle"), mCurrFrame(0)
{
    // connect SIGNAL(TimerProxy::updateTime(int msecs)) to SLOT(timeUpdated(int))
    connect(tpro, SIGNAL(updateTime(int)), this, SLOT(timeUpdated(int)));

}

AnimationSprite::~AnimationSprite() {

}

void AnimationSprite::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    // whichever version of drawPixmap/drawImage is up to you
    // void QPainter::drawPixmap(QRectF, QPixmap)

}

QRectF AnimationSprite::boundingRect() const {
    return mSubRect;
}

void AnimationSprite::setSubRect(QRect newRect) {
    mSubRect = newRect;
}


/**
 * @brief change the current animation,
 *        reset the elapsed time counter,
 *        update the current sub-rect to draw to match the first frame of the new animation
 *
 * @param animName
 */
void AnimationSprite::startAnim(const QString animName) {
    mCurrAnim = animName;

}

void AnimationSprite::timeUpdated(int msecs) {
    prepareGeometryChange();
    update();
}
