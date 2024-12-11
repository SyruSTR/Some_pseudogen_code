#include "robot.h"
#include <iostream>

#define IF_INERVAL(value,a,b) if(value>=a && value<=b)

Robot::Robot(int id) {
    this->id = id;
    std::cout << "Robot " << id << " created" << std::endl;
    for (int i =0; i<GEN_LENGHT;i++) {
        gen[i] = i*2;
    }
}

Robot::~Robot() {
  std::cout << "Robot " << id << " destroyed" << std::endl;
}

void Robot::execute_action(){

    IF_INERVAL(gen[current_state],0,3){std::cout << "Move right" << std::endl;}
    IF_INERVAL(gen[current_state],4,7){std::cout << "Move left" << std::endl;}
    IF_INERVAL(gen[current_state],8,11){std::cout << "Move up" << std::endl;}
    IF_INERVAL(gen[current_state],12,15){std::cout << "Move down" << std::endl;}
    current_state = ++current_state % GEN_LENGHT;
  }