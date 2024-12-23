//
// Created by grusted on 12/11/24.
//

#ifndef ROBOT_H
#define ROBOT_H

#include "mapObject.h"
#include "map.h"

#define GEN_LENGHT 8
#define MAX_GEN 64

namespace GeneticThings {
  class Robot : public MapObject {
  private:
    int id;

    //current pointer in
    int current_state = 0;
    //Gen commands for robot
    short int gen [GEN_LENGHT];
  public:
    Robot(int x, int y, Map *map, int id);

    void move(int x, int y);
    void execute_action();

    ~Robot();
  };
}

#endif //ROBOT_H
