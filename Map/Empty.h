#ifndef EMPTY_H
#define EMPTY_H

#include "mapObject.h"
#include "map.h"

namespace GeneticThings {
    class Empty : public MapObject {
    public:
        Empty(int x, int y, Map *map);
        ~Empty() override;
        void ExecuteAction() override;
    };
}

#endif //EMPTY_H
