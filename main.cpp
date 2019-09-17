#include "mainwindow.h"
#include <QDebug>
#include <QApplication>
#include "maze.h"
#include "mazegenerator.h"
#include "timerproxy.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // initialize map [could be done in a smarter way]
    QList<QList<bool>> map {
        {false, false, false, false, false, false, false, false, false, false, false},
        {false, true, false, true, false, true, false, true, false, true, false},
        {false, false, false, false, false, false, false, false, false, false, false},
        {false, true, false, true, false, true, false, true, false, true, false},
        {false, false, false, false, false, false, false, false, false, false, false},
        {false, true, false, true, false, true, false, true, false, true, false},
        {false, false, false, false, false, false, false, false, false, false, false},
        {false, true, false, true, false, true, false, true, false, true, false},
        {false, false, false, false, false, false, false, false, false, false, false},
        {false, true, false, true, false, true, false, true, false, true, false},
        {false, false, false, false, false, false, false, false, false, false, false},
    };


    // new maze widget
    Maze *mz = new Maze();

    // new maze generator
    MazeGenerator *mGen = new MazeGenerator(map);

    // generate maze by backtracking
    mGen -> carve_passages_from(1, 1, map);


    // setup map for maze widget
    mz -> setVec(map);

    // display maze
    mz -> show();

    // test
    TimerProxy *tm = new TimerProxy();


    return a.exec();
}
