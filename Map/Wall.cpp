

#include "Wall.h"

using namespace genetic_things;

Wall::Wall(int x, int y, Map* map) : MapObject(x, y, map){
  this->_type = WALL;
  }

Wall::~Wall() = default;

void Wall::executeAction() {

}

