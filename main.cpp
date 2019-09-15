#include "mainwindow.h"
#include <QDebug>
#include <QInputDialog>
#include "maze.h"
#include "mazegenerator.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

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



    Maze *mz = new Maze();
    MazeGenerator *mGen = new MazeGenerator(map);
    mGen -> carve_passages_from(1, 1, map);


    mz -> setVec(map);
    mz -> show();


    return a.exec();
}
