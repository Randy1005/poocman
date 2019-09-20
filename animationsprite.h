#ifndef ANIMATIONSPRITE_H
#define ANIMATIONSPRITE_H

#include <QGraphicsScene>
#include <QGraphicsObject>
#include <QPainter>
#include <QDebug>
#include "timerproxy.h"
#include <QCoreApplication>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QFile>
#include "commonInfo.h"


class AnimationSprite : public QGraphicsObject
{
    Q_OBJECT

public:
    AnimationSprite(TimerProxy *, QString, QGraphicsScene *);
    ~AnimationSprite();
    void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *);
    QRectF boundingRect() const = 0;
    void setSubRect(QRect);


    // animation methods
    void startAnim(const QString);

    // animation sprite image
    QPixmap *mSpriteImage;

    // character json description
    QJsonObject chrJsonObj;
    QJsonDocument chrJsonDoc;


    // sprite subrect / sprite origin
    QRect mSubRect;

    // current animation / frame / subrect json array
    QJsonObject mCurrAnim;
    QJsonArray animsArr;
    QJsonArray mSubRectArr;

    QString mAnimName;
    int mCurrFrame;

    QGraphicsScene *scene;



private slots:
    void timeUpdated(int);


};

#endif // ANIMATIONSPRITE_H
