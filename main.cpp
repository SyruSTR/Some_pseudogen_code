
#include <iostream>
#include "map.h"

int main(){
  GeneticThings::Map *map = new GeneticThings::Map(50,8);

  map->printMap();

  delete map;
  return 0;
}
