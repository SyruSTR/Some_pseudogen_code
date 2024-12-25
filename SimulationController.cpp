//
// Created by grusted on 12/23/24.
//

#include "SimulationController.h"

SimulationController::SimulationController(){
  std::cout << "Simulation controller created" << std::endl;

  map = new GeneticThings::Map(8,50);

  for (int i = 0; i < 10; i++) {
    auto test_robot = map->addRobot_at_random_place(i);
    if (!test_robot)
      break;
    robots.push_back(test_robot);

  }
}
void SimulationController::startSimulation(){

  map->printMap();

  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < robots.size(); j++) {
      robots[j]->execute_action();
    }
    sleep(1);
    map->printMap();
  }


}

SimulationController::~SimulationController() {
  delete map;
}
