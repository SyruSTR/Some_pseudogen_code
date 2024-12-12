//
// Created by grusted on 12/11/24.
//

#include "mapObject.h"
using namespace GeneticThings;

GeneticThings::MapObject::MapObject() {
    this->x = 0;
    this->y = 0;
    this->map = nullptr;
    this->type = EMPTY;
}

GeneticThings::MapObject::MapObject(int x, int y, Map *map, ObjectType type) : x(x), y(y), map(map), type(type){}

GeneticThings::MapObject::~MapObject(){}