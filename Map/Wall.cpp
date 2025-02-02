

#include "Wall.h"

using namespace GeneticThings;

Wall::Wall(int x, int y, Map* map) : MapObject(x, y, map){
  this->type = WALL;
  }

Wall::~Wall() = default;

void Wall::ExecuteAction() {

}

