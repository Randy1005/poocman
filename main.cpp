#include "mainwindow.h"
#include <QDebug>
#include <QApplication>
#include <QGraphicsView>
#include "timerproxy.h"
#include "commonInfo.h"
#include "gamescene.h"
#include "menuscene.h"
#include "gameoverscene.h"
#include "instrscene.h"
#include "button.h"

int Poocman::dotsEaten = 0;
int Poocman::lives = 2;
int TimerProxy::countdown = 200;
QGraphicsScene *Button::menu = nullptr;
QGraphicsScene *Button::game = nullptr;
QGraphicsScene *Button::gameover = nullptr;
QGraphicsScene *Button::instr = nullptr;



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QGraphicsView *view = new QGraphicsView();
    GameScene *game_scene = new GameScene(view);
    MenuScene *menu_scene = new MenuScene(view);
    InstrScene *instr_scene = new InstrScene(view);


    // initialize scene members
    Button::game = game_scene;
    Button::menu = menu_scene;
    Button::instr = instr_scene;


    // set scene to graphicsview
    view->setScene(menu_scene);
    view->show();



    return a.exec();
}
