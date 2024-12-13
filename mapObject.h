//
// Created by grusted on 12/11/24.
//

#ifndef MAPOBJECT_H
#define MAPOBJECT_H

#include "map.h"

namespace GeneticThings {
    enum ObjectType {
        EMPTY,
        WALL,
        ROBOT,
        FOOD
      };

    class Map;
    class Robot;

    class MapObject {
    protected:
        Map *map;
    public:
        int x;
        int y;

        ObjectType type;
        MapObject();
        MapObject(int x, int y, Map* map, ObjectType type = EMPTY);

        void info();
        ~MapObject();

        MapObject &operator=(Robot * robot);
    };
}


#endif //MAPOBJECT_H
