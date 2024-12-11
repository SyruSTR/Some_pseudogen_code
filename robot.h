//
// Created by grusted on 12/11/24.
//

#ifndef ROBOT_H
#define ROBOT_H

#define GEN_LENGHT 8

class Robot {
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
    Robot(int id);

    void execute_action();

    ~Robot();
};

#endif //ROBOT_H
