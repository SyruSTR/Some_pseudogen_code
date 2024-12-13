//
// Created by grusted on 12/11/24.
//

#include "map.h"
#include "mapObject.h"

#include "map.h"

#include <cstdio>
#include <cstdlib>
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

    void Map::addRobot_at_random_place() {

        int new_x = rand() % (this->height-1) + 1;
        int new_y = rand() % (this->width-1) + 1;

        delete this->map[new_x][new_y];
        this-> map[new_x][new_y] = new Robot(new_x, new_y, this, 0);
    }


    void Map::printMap() const {
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                switch (map[i][j]->type) {
                    case EMPTY:
                        printf(" ");
                        break;
                    case WALL:
                        printf("#");
                        break;
                    case ROBOT:
                        printf("@");
                        break;
                    case FOOD:
                        printf("*");
                        break;
                    default:
                        printf(" ");
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

