//
// Created by grusted on 12/11/24.
//

#ifndef ROBOT_H
#define ROBOT_H

#include "mapObject.h"
#include "map.h"

#define GEN_LENGHT 64
#define MAX_GEN 64
#define START_HP 10
#define MAX_HP 99

#define ROBOT_JUMP 1
#define FOOD_JUMP 2
#define WALL_JUMP 3
#define EMPTY_JUMP 4

#define WALL_DAMAGE 5
#define FOOD_RESTORE_HP 5
#define ROBOT_DAMAGE 5


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
    int lookAt(int direction);
    void kick(int direction);

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
