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
#include <math.h>
#include "maze.h"


typedef struct gridBound {
    double xMin, xMax, yMin, yMax;
} GridBound;

class AnimationSprite : public QGraphicsObject
{
    Q_OBJECT

public:
    AnimationSprite(TimerProxy *, QString, QGraphicsScene *, QList<QList<bool>>, Maze *);
    ~AnimationSprite();
    void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *);
    QRectF boundingRect() const = 0;
    void setSubRect(QRect);

    // convert from game view coordinate to grid(map) coordinate
    QPoint gridtogameCoord(QPoint);

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

    // game scene
    QGraphicsScene *scene;

    // map
    QList<QList<bool>> gameMap;

    // map units
    int offset;
    int cell_unit;

    // converted grid coordinates
    QVector<QVector<GridBound>> gameCoords;

    // maze widget
    Maze *mazeWidget;




private slots:
    void timeUpdated(int);

};

#endif // ANIMATIONSPRITE_H
