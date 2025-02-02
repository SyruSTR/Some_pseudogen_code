#include "mapObject.h"
#include "map.h"


#ifndef WALL_H
#define WALL_H

namespace genetic_things {
    class Wall : public MapObject {
    public:
        Wall(int x, int y, Map *map);
        ~Wall() override;
        void executeAction() override;
    };
}

#endif //WALL_H
