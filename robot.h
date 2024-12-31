//
// Created by grusted on 12/11/24.
//

#ifndef ROBOT_H
#define ROBOT_H

#include "mapObject.h"
#include "map.h"

#define GEN_LENGHT 8
#define MAX_GEN 64
#define START_HP 10
#define MAX_HP 99

namespace GeneticThings {
  class Robot : public MapObject {
  private:
    int id;

    //current pointer in
    int current_state = 0;
    //Gen commands for robot
    short int gen [GEN_LENGHT];

    int hp;
    bool isAlive;

    void die();
    void move(int direction);

    int robotXToVector(int direction);
    int robotYToVector(int direction);
  public:
    Robot(int x, int y, Map *map, int id);

    int get_id();
    bool is_alive();
    void execute_action();

    ~Robot();
  };
}

#endif //ROBOT_H
