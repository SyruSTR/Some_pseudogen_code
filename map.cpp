//
// Created by grusted on 12/11/24.
//

#include "map.h"
#include "mapObject.h"

#include "map.h"
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

        // Если нужно инициализировать объекты:
        // for (int i = 0; i < width; ++i) {
        //     for (int j = 0; j < height; ++j) {
        //         map[i][j] = GeneticThings::MapObject(i, j, this);
        //     }
        // }
    }

    Map::~Map() {
        for (int i = 0; i < width; ++i) {
            delete[] map[i];
        }
        delete[] map;
    }

}  // namespace GeneticThings

