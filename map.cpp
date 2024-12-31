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

        grid = new MapObject**[height];

        for (int i = 0; i < height; ++i) {
            grid[i] = new MapObject*[width];
        }

        //filling the map off EMPTY space
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                grid[i][j] = new MapObject(i, j, this);
            }
        }

        //add borders for map
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                if (i == 0 || i == height - 1 || j == 0 || j == width - 1) {
                    auto tmp = new MapObject(i, j, this, WALL);
                    std::swap(grid[i][j], tmp);
                    delete tmp;
                }
            }
        }
    }

    Robot* Map::addRobot_at_random_place(int id) {

        int index = this->height * this->width;
        do {
            int new_x = rand() % (this->height-1) + 1;
            int new_y = rand() % (this->width-1) + 1;

            if (grid[new_x][new_y]->type == WALL || grid[new_x][new_y]->type == ROBOT) {
                index--;
                continue;
            }

            delete this->grid[new_x][new_y];
            const auto robot = new Robot(new_x, new_y, this, id);
            this->grid[new_x][new_y] = robot;
            return robot;

        } while (index >= 0);


        return nullptr;
    }

    bool Map::isWall(int x, int y) {
        return grid[x][y]->type == WALL;
    }

    ObjectType Map::getObjectType(int x, int y) {
        return grid[x][y]->type;
    }

    void Map::swapObjects(int x1, int y1, int x2, int y2) {
        if (x1 < 0 || x1 >= height || y1 < 0 || y1 >= width ||
        x2 < 0 || x2 >= height || y2 < 0 || y2 >= width) {
            std::cerr << "Error: Swap coordinates out of bounds!" << std::endl;
            return;
        }

        MapObject* temp = grid[x1][y1];
        grid[x1][y1] = grid[x2][y2];
        grid[x1][y1]->x = x1;
        grid[x1][y1]->y = y1;

        grid[x2][y2] = temp;
        grid[x2][y2]->x = x2;
        grid[x2][y2]->y = y2;

    }

    MapObject* Map::get_object(int x, int y) {
        if (x < 0 || y < 0 || x >= height || y >= width ) return nullptr;

        return grid[x][y];

    }

    void Map::delete_object(int x, int y) {
        if (x < 0 || y < 0 || x >= height || y >= width) return;
        MapObject* empty_space = new MapObject(x, y, this);
        std::swap(grid[x][y], empty_space);
        delete empty_space;
    }


    void Map::printMap() const {
        for (int i = 0; i < width; ++i) {
            for (int j = 0; j < height; ++j) {
                //just for safe from SIGSEGV
                if (grid[j][i] != nullptr) {
                    switch (grid[j][i]->type) {
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
            }
            printf("\n");
        }
    }

    Map::~Map() {
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                delete grid[i][j];
            }
            delete[] grid[i];
        }
        delete[] grid;
    }

}  // namespace GeneticThings

