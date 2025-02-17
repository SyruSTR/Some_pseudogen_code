//
// Created by grusted on 12/23/24.
//

#include "SimulationController.h"

#include <algorithm>
#include <fstream>
#include <unistd.h>

#include "Map/robot.h"

SimulationController::SimulationController(){
  std::cout << "Simulation controller created" << std::endl;

  //_map = new genetic_things::Map(50,10);
  _map = new genetic_things::Map("../TestMap.txt", "../TestGens.txt");
  _robots = _map->getRobots();

  for (int i = 0; i < 10; i++) {
    _map->addRobotAtRandomPlace(i);
  }

  for (int i = 0; i < 10; i++) {
    _map->addFoodAtRandomPlace();
  }
}

void SimulationController::deleteDeadRobots(){
  if (_map) {
    //delete robot from system
    _robots->erase(std::remove_if(_robots->begin(),_robots->end(),
      [this](genetic_things::Robot* search_robot){
        if (!search_robot->isAlive()) {
          //delete robot from grid
          _map->deleteObject(search_robot->x,search_robot->y);
          return true;
        }
        return false;
      }),
      _robots->end());

    //todo Maybe replace to the food
  }
}


void SimulationController::startSimulation(){

  _map->printMap();

  for (int i = 0; i < 10; i++) {
    for (auto & robot : *_robots) {
      robot->executeAction();
    }
    deleteDeadRobots();
    usleep(100);
    _map->printMap();
  }


}

SimulationController::~SimulationController() {
  delete _map;
}
