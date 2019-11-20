#ifndef GAMESCENE_H
#define GAMESCENE_H
#include <QGraphicsScene>
#include <QGraphicsProxyWidget>
#include <QMutableListIterator>
#include <QDebug>
#include <QApplication>
#include <QGraphicsView>
#include <QVector>
#include <QLabel>
#include "maze.h"
#include "mazegenerator.h"
#include "timerproxy.h"
#include "ghost.h"
#include "clyde.h"
#include "blinky.h"
#include "poocman.h"
#include "pacdot.h"
#include "commonInfo.h"
#include "button.h"
#include "gameoverscene.h"


class GameScene : public QGraphicsScene
{
    Q_OBJECT
public:
    GameScene(QGraphicsView *);
    void reset();
    QGraphicsView *view;
    QLabel *scoreLabel;
    QLabel *cntDownLabel;
    QLabel *livesLabel;

    Maze *mz;
    MazeGenerator *mGen;
    Poocman *pc;
    Clyde *c;
    Clyde *c2;
    QList<QList<bool>> map;
    QList<Pacdot *> *pacdots;
    QGraphicsProxyWidget *proxyItem;

    TimerProxy *tpro;

public slots:
    void updateLabel(QString);
    void switchScene();
};

#endif // GAMESCENE_H
