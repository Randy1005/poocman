#ifndef GAMESCENE_H
#define GAMESCENE_H
#include <QGraphicsScene>
#include <QDebug>
#include <QApplication>
#include <QGraphicsView>
#include <QVector>
#include "maze.h"
#include "mazegenerator.h"
#include "timerproxy.h"
#include "poocman.h"
#include "ghost.h"
#include "clyde.h"
#include "blinky.h"
#include "pacdot.h"
#include "commonInfo.h"

class GameScene : public  QGraphicsScene
{
public:
    GameScene();
};

#endif // GAMESCENE_H
