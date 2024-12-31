#include "robot.h"
#include <iostream>

namespace GeneticThings {
#define IF_INERVAL(value,a,b) if(value>=a && value<=b)

    Robot::Robot(int x, int y, Map *map , int id):  MapObject(x,y, map, ROBOT) {
        this->id = id;
        std::cout << "Robot " << id << " created" << std::endl;
        for (int i =0; i<GEN_LENGHT;i++) {
            gen[i] = rand() % 1;
        }
        this->hp = START_HP;
        this->isAlive = true;
    }

    bool Robot::is_alive() {
        return isAlive;
    }

    Robot::~Robot() {
        std::cout << "Robot " << id << " destroyed" << std::endl;
    }

    int Robot::get_id() {
        return id;
    }


    void Robot::die() {
        isAlive = false;
    }


    void Robot::move(int direction) {

        int check_x = robotXToVector(direction);
        int check_y = robotYToVector(direction);

        switch (map->getObjectType(check_x,check_y)) {
            case WALL:
            case ROBOT:
                return;
            case FOOD:
                //todo eat
                break;
            default:
                break;
        }

        map->swapObjects(this->x,this->y,check_x,check_y);
    }

    int Robot::robotXToVector(int direction) {
        direction = direction % 4;
        if (direction == 0 || direction == 2) return this->x;
        if (direction == 1) return this->x + 1;
        if (direction == 3) return this->x - 1;
    }

    int Robot::robotYToVector(int direction) {
        direction = direction % 4;
        if (direction == 0) return this->y + 1;
        if (direction == 1 || direction == 3) return this->y;
        if (direction == 2) return this->y - 1;
    }



    void Robot::execute_action(){


        int actual_gen = gen[current_state];
        //0-3 move
        IF_INERVAL(actual_gen,0,3){move(actual_gen);}
        current_state = ++current_state % GEN_LENGHT;

        if (--hp <= 0) {
            die();
        }
    }
}
