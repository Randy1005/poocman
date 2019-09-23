#include "mainwindow.h"
#include <QDebug>
#include <QApplication>
#include <QGraphicsView>
#include "maze.h"
#include "mazegenerator.h"
#include "timerproxy.h"
#include "poocman.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QGraphicsScene *scene = new QGraphicsScene(nullptr);
    QGraphicsView *view = new QGraphicsView();



    // initialize map [could be done in a smarter/customized way]
    QList<QList<bool>> map {
        {false, false, false, false, false, false, false, false, false, false, false, false, false, false, false},
        {false, true, false, true, false, true, false, true, false, true, false, true, false, true, false},
        {false, false, false, false, false, false, false, false, false, false, false, false, false, false, false},
        {false, true, false, true, false, true, false, true, false, true, false, true, false, true, false},
        {false, false, false, false, false, false, false, false, false, false, false, false, false, false, false},
        {false, true, false, true, false, true, false, true, false, true, false, true, false, true, false},
        {false, false, false, false, false, false, false, false, false, false, false, false, false, false, false},
        {false, true, false, true, false, true, false, true, false, true, false, true, false, true, false},
        {false, false, false, false, false, false, false, false, false, false, false, false, false, false, false},
        {false, true, false, true, false, true, false, true, false, true, false, true, false, true, false},
        {false, false, false, false, false, false, false, false, false, false, false, false, false, false, false},
        {false, true, false, true, false, true, false, true, false, true, false, true, false, true, false},
        {false, false, false, false, false, false, false, false, false, false, false, false, false, false, false},
        {false, true, false, true, false, true, false, true, false, true, false, true, false, true, false},
        {false, false, false, false, false, false, false, false, false, false, false, false, false, false, false}
    };


    // new maze widget
    Maze *mz = new Maze();

    // new maze generator
    MazeGenerator *mGen = new MazeGenerator(map);

    // generate maze by backtracking
    mGen->carve_passages_from(1, 1, map);


    // setup map for maze
    mz->setVec(map);


    // test
    TimerProxy *tpro = new TimerProxy();
    Poocman *pc = new Poocman(tpro, ":/resource/poocman.json", scene, map);

    scene->setSceneRect(0, 0, mz->width(), mz->height());
    scene->addWidget(mz);
    scene->addItem(pc);

    // focusable item
    pc->setFlag(QGraphicsItem::ItemIsFocusable);
    pc->setFocus();

    view->setScene(scene);
    view->setFocusPolicy(Qt::StrongFocus);
    view->show();


    return a.exec();
}
