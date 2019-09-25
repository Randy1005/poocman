#include "animationsprite.h"

AnimationSprite::AnimationSprite(TimerProxy *tpro, QString name, QGraphicsScene *parent, Maze *mzWidget) :
    mSubRect(0, 0, 1, 1), mCurrFrame(0), scene(parent), mazeWidget(mzWidget)
{
    // convert JSON file to object
    QFile jsonfile;
    jsonfile.setFileName(name);
    jsonfile.open(QIODevice::ReadOnly | QIODevice::Text);

    QJsonParseError jsonError;
    QString val = jsonfile.readAll();
    chrJsonDoc = QJsonDocument::fromJson(val.toUtf8(), &jsonError);
    if (jsonError.error) {
        qWarning() << jsonError.errorString();
        return;
    }
    jsonfile.close();

    chrJsonObj = chrJsonDoc.object();

    // parse animation descriptions
    QJsonArray chrJsonArr = chrJsonObj["behaviors"].toArray();
    foreach (const QJsonValue &val, chrJsonArr) {
        QJsonObject obj = val.toObject();
        if (obj["name"].toString() == "SpriteAnimationBehavior") {
            animsArr = obj["params"].toObject()["anims"].toArray();
        }
    }


    // connect SIGNAL(TimerProxy::updateTime(int msecs)) to SLOT(timeUpdated(int))
    connect(tpro, SIGNAL(updateTime(int)), this, SLOT(timeUpdated(int)));

    // assign margin offset / cell unit size
    offset = (GAME_WIDTH-GAME_HEIGHT)/2;
    cell_unit = MAZE_SIZE/(2*MAZE_PASSAGE_SIZE+1);
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
    mCurrFrame = 0;
    mAnimName = animName;

    // parse current animation object, assign to mCurrentAnimation
    foreach(const QJsonValue &val, animsArr) {
        QJsonObject obj = val.toObject();
        if (obj["animName"].toString() == animName) {
            mCurrAnim = obj["animFrames"].toArray().at(mCurrFrame).toObject();
        }
    }

    // assign to mSubRect
    mSubRectArr = mCurrAnim["rect"].toArray();
    mSubRect = QRect(mSubRectArr.at(0).toInt(),
                     mSubRectArr.at(1).toInt(),
                     mSubRectArr.at(2).toInt(),
                     mSubRectArr.at(3).toInt());

    // reset timer
    // ...
}

void AnimationSprite::timeUpdated(int msecs) {

    prepareGeometryChange();

    // parse current animation object, assign to mCurrentAnimation
    // and increment frame
    foreach(const QJsonValue &val, animsArr) {
        QJsonObject obj = val.toObject();
        if (obj["animName"].toString() == mAnimName) {
            if (mCurrFrame < obj["animFrames"].toArray().size() - 1) {
                ++mCurrFrame;
            } else {
                mCurrFrame = 0;
            }

            mCurrAnim = obj["animFrames"].toArray().at(mCurrFrame).toObject();

            // update mSubRect
            mSubRectArr = mCurrAnim["rect"].toArray();
            setSubRect(QRect(mSubRectArr.at(0).toInt(),
                             mSubRectArr.at(1).toInt(),
                             mSubRectArr.at(2).toInt(),
                             mSubRectArr.at(3).toInt()));
        }
    }

    scene -> update();

}
