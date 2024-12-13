#include "robot.h"
#include <iostream>

namespace GeneticThings {
#define IF_INERVAL(value,a,b) if(value>=a && value<=b)

    Robot::Robot(int x, int y, Map *map , int id):  MapObject(x,y, map, ROBOT) {
        this->id = id;
        std::cout << "Robot " << id << " created" << std::endl;
        for (int i =0; i<GEN_LENGHT;i++) {
            gen[i] = i*2;
        }
    }

    Robot::~Robot() {
        std::cout << "Robot " << id << " destroyed" << std::endl;
    }

    void Robot::move(int x, int y) {
        if (map->isWall(x,y))
            return;
        //todo if isRobot

        map->swapObjects(this->x,this->y,x,y);
    }


    void Robot::execute_action(){

        //0-3 move left
        IF_INERVAL(gen[current_state],0,3){move(x+1,y);}
        //4-7 move right
        IF_INERVAL(gen[current_state],4,7){move(x-1,y);}
        //8-11 move up
        IF_INERVAL(gen[current_state],8,11){move(x,y+1);}
        //12-15 move down
        IF_INERVAL(gen[current_state],12,15){move(x,y-1);}
        current_state = ++current_state % GEN_LENGHT;
    }
}
