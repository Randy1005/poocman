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


            // if cell is valid (between bounds and unvisited)
            if (nextY > 0 && nextY < (map.front().size()) &&
                nextX > 0 && nextX < (map[nextY].size()) &&
                visited[nextX][nextY] == false) {

                // wall between
                switch(direction) {
                    case 0:
                        map[currX-1][currY] = true;
                        break;
                    case 1:
                        map[currX+1][currY] = true;
                        break;
                    case 2:
                        map[currX][currY+1] = true;
                        break;
                    case 3:
                        map[currX][currY-1] = true;
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

