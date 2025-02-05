
#ifndef FOOD_H
#define FOOD_H

#include "mapObject.h"
#include "map.h"

namespace genetic_things {
    class Food : public MapObject {
    public:
        Food(int x, int y, Map *map);
        ~Food() override;
        void executeAction() override;
    };
}





#endif //FOOD_H
