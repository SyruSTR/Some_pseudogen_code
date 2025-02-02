//
// Created by grusted on 12/11/24.
//

#ifndef MAPOBJECT_H
#define MAPOBJECT_H

#include "map.h"
#include "../SimulationController.h"

namespace GeneticThings {

    class Map;
    class Robot;

    class MapObject {
    protected:
        Map *map;
        SimulationController *sim;

        bool isInvincible;
        int hp;
        bool isAlive;
        ObjectType type;
    public:
        int x;
        int y;

        MapObject();
        MapObject(int x, int y, Map *map);

        bool IsAlive() const;
        ObjectType GetType() const;
        virtual void ExecuteAction() = 0;
        void GetDamage(int damage);
        void info();

        virtual ~MapObject();
    };
}


#endif //MAPOBJECT_H
