
#include <iostream>
#include <signal.h>

#include "map.h"
#include "robot.h"

int main(){
  GeneticThings::Map *map = new GeneticThings::Map(8,50);

  auto test_robot = map->addRobot_at_random_place();
  map->printMap();

  for (int i = 0; i < 10; i++) {
    test_robot->execute_action();
    sleep(1);
    map->printMap();
  }



  delete map;
  return 0;
}
