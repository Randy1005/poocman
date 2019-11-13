#include "mainwindow.h"
#include <QDebug>
#include <QApplication>
#include <QGraphicsView>
#include "timerproxy.h"
#include "poocman.h"
#include "commonInfo.h"
#include "gamescene.h"
#include "menuscene.h"

int Poocman::dotsEaten = 0;
int Poocman::lives = 3;
int TimerProxy::countdown = 60;


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GameScene *game_scene = new GameScene();
    MenuScene *menu_scene = new MenuScene();

    QGraphicsView *view = new QGraphicsView();  



    // set scene to graphicsview
    view->setScene(menu_scene);
    view->show();



    return a.exec();
}
