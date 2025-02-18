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


namespace genetic_things {
  class Robot : public MapObject {
  private:

    enum X_VECTOR {
      _4X,
      _8X
    };

    int _id;

    //current pointer in
    int _current_state = 0;
    //Gen commands for robot
    short int _gens [GEN_LENGHT];

    void die();
    void move(int direction);
    int lookAt(int direction);
    void kick(int direction);

    int robotXToVector(int direction, X_VECTOR x_vector  );
    int robotYToVector(int direction, X_VECTOR x_vector  );
    int addHp(int hp_count);

    void validateAndParseGen(std::string &raw_line);
  public:
    Robot(int x, int y, Map *map, int id);
    Robot(int x, int y, Map *map, int id, std::string &gens_from_file);

    void executeAction() override;

    int getId() const;

    ~Robot() override;
  };
}

#endif //ROBOT_H
