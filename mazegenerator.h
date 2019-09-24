#ifndef MAZEGENERATOR_H
#define MAZEGENERATOR_H

#include <QWidget>
#include <algorithm>    // std::shuffle
#include <array>        // std::array
#include <random>       // std::default_random_engine
#include <chrono>       // std::chrono::system_clock

#include <QDebug>
using namespace std;


class MazeGenerator
{
public:
    MazeGenerator(QList<QList<bool>> map);
    void carve_passages_from(int currX, int currY, QList<QList<bool>> &map);

private:
    std::array<int, 4> directions = {0, 1, 2, 3}; // North, South, East, West
    int nextX;
    int nextY;
    QList<int> dirX = {-2, 2, 0, 0};
    QList<int> dirY = {0, 0, 2, -2};
    QList<QList<bool>> visited;

    long long seed; // obtain a time-based seed
};

#endif


