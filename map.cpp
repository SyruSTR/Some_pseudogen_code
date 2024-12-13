//
// Created by grusted on 12/11/24.
//

#include "map.h"
#include "mapObject.h"

#include "map.h"

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <unordered_set>

#include "robot.h"

namespace GeneticThings {

    Map::Map(int width, int height) {
        this->width = width;
        this->height = height;

        map = new MapObject**[height];

        for (int i = 0; i < height; ++i) {
            map[i] = new MapObject*[width];
        }

        //filling the map off EMPTY space
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                map[i][j] = new MapObject(i, j, this);
            }
        }

        //add borders for map
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                if (i == 0 || i == height - 1 || j == 0 || j == width - 1) {
                    auto tmp = new MapObject(i, j, this, WALL);
                    std::swap(map[i][j], tmp);
                    delete tmp;
                }
            }
        }
    }

    Robot* Map::addRobot_at_random_place() {

        int new_x = rand() % (this->height-1) + 1;
        int new_y = rand() % (this->width-1) + 1;

        delete this->map[new_x][new_y];
        const auto robot = new Robot(new_x, new_y, this, 0);
        this->map[new_x][new_y] = robot;
        return robot;
    }

    bool Map::isWall(int x, int y) {
        return map[x][y]->type == WALL;
    }

    void Map::swapObjects(int x1, int y1, int x2, int y2) {
        if (x1 < 0 || x1 >= height || y1 < 0 || y1 >= width ||
        x2 < 0 || x2 >= height || y2 < 0 || y2 >= width) {
            std::cerr << "Error: Swap coordinates out of bounds!" << std::endl;
            return;
        }

        MapObject* temp = map[x1][y1];
        map[x1][y1] = map[x2][y2];
        map[x1][y1]->x = x1;
        map[x1][y1]->y = y1;

        map[x2][y2] = temp;
        map[x2][y2]->x = x2;
        map[x2][y2]->y = y2;

    }



    void Map::printMap() const {
        for (int i = 0; i < width; ++i) {
            for (int j = 0; j < height; ++j) {
                switch (map[j][i]->type) {
                    case EMPTY:
                        printf("  ");
                        break;
                    case WALL:
                        printf("# ");
                        break;
                    case ROBOT:
                        printf("@ ");
                        break;
                    case FOOD:
                        printf("* ");
                        break;
                    default:
                        printf("^ ");
                }
            }
            printf("\n");
        }
    }

    Map::~Map() {
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                delete map[i][j];
            }
            delete[] map[i];
        }
        delete[] map;
    }

}  // namespace GeneticThings

