#include "mazegenerator.h"

MazeGenerator::MazeGenerator(QList<QList<bool>> map)
{
    // initialize visited table
    visited = map;
    for (int y = 0; y < map.front().size(); y++) {
        for (int x = 0; x < map[y].size(); x++) {
            visited[y][x] = false;
        }
    }

    // obtain a time-based seed
    seed = std::chrono::system_clock::now().time_since_epoch().count();
}

void MazeGenerator::carve_passages_from(int currX, int currY, QList<QList<bool>> &map) {

    if (visited[currX][currY] == true)
        return;
    else {

        // scramble the 4 directions
        shuffle(directions.begin(), directions.end(), std::default_random_engine(seed));

        // traverse the direction list and carve a passage
        for (int& direction: directions) {
            nextX = currX + dirX[direction];
            nextY = currY + dirY[direction];

//            qDebug() << nextX << " " << nextY << "\n";

            // if cell is valid (between bounds and unvisited)
            if (nextY > 0 && nextY < (map.front().size() - 1) &&
                nextX > 0 && nextX < (map[nextY].size() - 1) &&
                visited[nextX][nextY] == false) {

//                qDebug() << "cell valid" << "\n";
                // wall between
                switch(direction) {
                    case 0:
                        map[currX-1][currY] = true;
//                        qDebug() << "north wall" << "\n";
                        break;
                    case 1:
                        map[currX+1][currY] = true;
//                        qDebug() << "south wall" << "\n";
                        break;
                    case 2:
                        map[currX][currY+1] = true;
//                        qDebug() << "east wall" << "\n";
                        break;
                    case 3:
                        map[currX][currY-1] = true;
//                        qDebug() << "west wall" << "\n";
                        break;
                    default:
                        break;
                }

                // set visited to true
                visited[currX][currY] = true;

                // recursive call
                carve_passages_from(nextX, nextY, map);
            }
        }

    }
}

