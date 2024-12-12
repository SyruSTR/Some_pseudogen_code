//
// Created by grusted on 12/11/24.
//

#include "map.h"
#include "mapObject.h"

#include "map.h"

#include <cstdio>
#include <unordered_set>

#include "mapObject.h"

namespace GeneticThings {

    Map::Map(int width, int height) {
        this->width = width;
        this->height = height;

        // Явное указание пространства имен
        map = new GeneticThings::MapObject*[width];

        // Выделение памяти для объектов в каждой строке
        for (int i = 0; i < width; ++i) {
            map[i] = new GeneticThings::MapObject[height];
        }


        for (int i = 0; i < width; ++i) {
            for (int j = 0; j < height; ++j) {
                map[i][j] = MapObject(i, j, this);
            }
        }

        //add walls for end of map
        for (int i = 0; i < width; ++i) {
            for (int j = 0; j < height; ++j) {
                if (i == 0 || i == width - 1 || j == 0 || j == height - 1) {
                    auto tmp = MapObject(i, j, this, WALL);
                    std::swap(map[i][j], tmp);
                }
            }
        }
    }

    void Map::printMap() const {
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                switch (map[j][i].type) {
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
        for (int i = 0; i < width; ++i) {
            delete[] map[i];
        }
        delete[] map;
    }

}  // namespace GeneticThings

