//
// Created by grusted on 12/11/24.
//

#ifndef ROBOT_H
#define ROBOT_H

#include "mapObject.h"
#include "map.h"

#define GEN_LENGHT 8

namespace GeneticThings {
  class Robot : public MapObject {
  private:
    int id;

    //current pointer in
    int current_state = 0;
    //Gen commands for robot
    //1-4 move left
    //5-8 move right
    //9-12 move up
    //13-16 move down
    //other trash gen
    short int gen [GEN_LENGHT];
  public:
    Robot(int x, int y, Map *map, int id);

    void move(int x, int y);
    void execute_action();

    ~Robot();
  };
}

#endif //ROBOT_H
