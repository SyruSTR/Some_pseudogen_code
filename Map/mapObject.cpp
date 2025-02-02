//
// Created by grusted on 12/11/24.
//

#include "mapObject.h"

#include <iostream>
using namespace genetic_things;

MapObject::MapObject() {
    this->x = 0;
    this->y = 0;
    this->_map = nullptr;
    this->_type = EMPTY;
}

MapObject::MapObject(int x, int y, Map *map) : _map(map), x(x), y(y){}


bool MapObject::isAlive() const {
    return _isAlive;
}

void MapObject::info() {
    std::cout << "x -> " << x << std::endl;
    std::cout << "y -> " << y << std::endl;
}

ObjectType MapObject::getType() const {
    return _type;
}

void MapObject::getDamage(const int damage) {
    if (!_isInvincible) {
        if (damage > this->_hp)
            this->_hp = 0;
        else {
            this->_hp -= damage;
        }
    }
}

MapObject::~MapObject(){}