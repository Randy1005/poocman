#include "mainwindow.h"
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


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QGraphicsScene *scene = new QGraphicsScene(nullptr);
    QGraphicsView *view = new QGraphicsView();


    // initialize map [could be done in a smarter/customized way]
    // create a 9 x 9 maze map  (try 15x15 next time)
    QList<QList<bool>> map {
        {false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false},
        {false, true, false, true, false, true, false, true, false, true, false, true, false, true, false, true, false, true, false},
        {false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false},
        {false, true, false, true, false, true, false, true, false, true, false, true, false, true, false, true, false, true, false},
        {false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false},
        {false, true, false, true, false, true, false, true, false, true, false, true, false, true, false, true, false, true, false},
        {false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false},
        {false, true, false, true, false, true, false, true, false, true, false, true, false, true, false, true, false, true, false},
        {false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false},
        {false, true, false, true, false, true, false, true, false, true, false, true, false, true, false, true, false, true, false},
        {false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false},
        {false, true, false, true, false, true, false, true, false, true, false, true, false, true, false, true, false, true, false},
        {false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false},
        {false, true, false, true, false, true, false, true, false, true, false, true, false, true, false, true, false, true, false},
        {false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false},
        {false, true, false, true, false, true, false, true, false, true, false, true, false, true, false, true, false, true, false},
        {false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false},
        {false, true, false, true, false, true, false, true, false, true, false, true, false, true, false, true, false, true, false},
        {false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false}
    };


    // new maze widget
    Maze *mz = new Maze();

    // new maze generator
    MazeGenerator *mGen = new MazeGenerator(map);

    // generate maze by backtracking
    mGen->carve_passages_from(1, 1, map);


    // setup map for maze
    mz->setVec(map);

    // create image pixmap of maze (for wall checking)
    mz->renderToPixmap();


    // test
    TimerProxy *tpro = new TimerProxy();
    Poocman *pc = new Poocman(tpro, ":/resource/poocman.json", scene, mz);
    Clyde *c = new Clyde(tpro, ":/resource/ghost.json", scene, mz);
    Blinky *b = new Blinky(tpro, ":/resource/ghost.json", scene, mz, pc);
    b->setSpeed(0.006);
    c->setSpeed(0.01);


    scene->setSceneRect(0, 0, mz->width(), mz->height());
    scene->addWidget(mz);
    scene->addItem(pc);
    scene->addItem(b);
    scene->addItem(c);

    // focusable poocman item
    pc->setFlag(QGraphicsItem::ItemIsFocusable);
    pc->setFocus();


    view->setScene(scene);
    view->setFocusPolicy(Qt::StrongFocus);
    view->show();


    return a.exec();
}
