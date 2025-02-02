//
// Created by grusted on 12/11/24.
//

#ifndef MAPOBJECT_H
#define MAPOBJECT_H

#include "map.h"
#include "../SimulationController.h"

namespace genetic_things {

    class Map;
    class Robot;

    class MapObject {
    protected:
        Map *_map;
        SimulationController *_sim;

        bool _isInvincible;
        int _hp;
        bool _isAlive;
        ObjectType _type;
    public:
        int x;
        int y;

        MapObject();
        MapObject(int x, int y, Map *map);

        bool isAlive() const;
        ObjectType getType() const;
        virtual void executeAction() = 0;
        void getDamage(int damage);
        void info();

        virtual ~MapObject();
    };
}


#endif //MAPOBJECT_H
