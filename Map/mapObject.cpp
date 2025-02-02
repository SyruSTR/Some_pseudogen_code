//
// Created by grusted on 12/11/24.
//

#include "mapObject.h"

#include <iostream>
using namespace GeneticThings;

MapObject::MapObject() {
    this->x = 0;
    this->y = 0;
    this->map = nullptr;
    this->type = EMPTY;
}

MapObject::MapObject(int x, int y, Map *map) : x(x), y(y), map(map){}


bool MapObject::IsAlive() const {
    return isAlive;
}

void MapObject::info() {
    std::cout << "x -> " << x << std::endl;
    std::cout << "y -> " << y << std::endl;
}

ObjectType MapObject::GetType() const {
    return type;
}

void MapObject::GetDamage(const int damage) {
    if (!isInvincible) {
        if (damage > this->hp)
            this->hp = 0;
        else {
            this->hp -= damage;
        }
    }
}

MapObject::~MapObject(){}