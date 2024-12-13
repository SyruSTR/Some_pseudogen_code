
#include <iostream>
#include <signal.h>
#include <vector>

#include "map.h"
#include "robot.h"

int main(){
  GeneticThings::Map *map = new GeneticThings::Map(8,50);

  std::vector<GeneticThings::Robot*> robots;

  for (int i = 0; i < 1; i++) {
    auto test_robot = map->addRobot_at_random_place(i);
    if (!test_robot)
      break;
    robots.push_back(test_robot);

  }
  map->printMap();

  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < robots.size(); j++) {
      robots[j]->execute_action();
    }
    sleep(1);
    map->printMap();
  }



  delete map;
  return 0;
}
