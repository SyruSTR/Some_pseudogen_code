#include "robot.h"
#include <iostream>
#include <regex>

namespace genetic_things {
#define IF_INERVAL(value,a,b) if(value>=a && value<=b)

    Robot::Robot(int x, int y, Map *map , int id):  MapObject(x,y, map) {
        this->_id = id;
        this->_type = ROBOT;
        this->_hp = START_HP;
        this->_isAlive = true;
        for (int i =0; i<GEN_LENGHT;i++) {
            _gens[i] = rand() % GEN_LENGHT;
        }
        std::cout << "Robot " << id << " created" << std::endl;
    }

    Robot::Robot(int x, int y, Map *map, int id, std::string &gens_from_file): MapObject(x,y, map) {
        this->_type = ROBOT;
        this->_id = id;
        this->_hp = START_HP;
        this->_isAlive = true;
        validateAndParseGen(gens_from_file);

        std::cout << "Robot " << id << " created" << std::endl;
    }

    void Robot::validateAndParseGen( std::string &raw_line) {
        // Regex to match the format: [ num1, num2, ..., numN ]
        const std::regex pattern(R"(\[\s*(\d{1,2}(,\s*\d{1,2})*)\s*\])");
        std::smatch match;

        if (!std::regex_match(raw_line, match, pattern)) {
            throw std::invalid_argument("Invalid gen. Expected format: [ num1, num2, ..., numN ]");
        }

        //stream of numbers
        std::istringstream iss(match[1].str());
        std::string tmp_number;
        int i = 0;

        while (std::getline(iss, tmp_number, ',')) {
            int value = std::stoi(tmp_number);
            if (value < 0 || value >= GEN_LENGHT) {
                throw std::out_of_range("Number out of range [0,63]:" + std::to_string(value));
            }
            this->_gens[i] = static_cast<short int>(value);
            i++;
        }

        if (i != GEN_LENGHT) {
            throw std::length_error("Line doesnt contain 64 numbers, it contains: " + std::to_string(i));
        }
    }

    Robot::~Robot() {
        std::cout << "Robot " << _id << " destroyed" << std::endl;
    }

    int Robot::getId() const {
        return _id;
    }


    void Robot::die() {
        _isAlive = false;
    }


    void Robot::move(int direction) {

        int check_x = robotXToVector(direction,_4X);
        int check_y = robotYToVector(direction,_4X);

        switch (_map->getObjectType(check_x,check_y)) {
            case WALL:
            case ROBOT:
                return;
            case FOOD:
                _map->deleteObject(check_x,check_y);
                this->addHp(FOOD_RESTORE_HP);
                break;
            default:
                break;
        }

        _map->swapObjects(this->x,this->y,check_x,check_y);
    }


    int Robot::robotXToVector(int direction, X_VECTOR x_vector  ) {
        if (x_vector == _4X) {
            direction = direction % 4;
            if (direction == 0 || direction == 2) return this->x;
            if (direction == 1) return this->x + 1;
            if (direction == 3) return this->x - 1;
        }
        else if (x_vector == _8X) {
            direction = (direction - 4) % 8;
            switch (direction) {
                case 7:
                case 6:
                case 5:
                    return this->x - 1;
                case 0:
                case 4:
                    return this->x;
                case 1:
                case 2:
                case 3:
                    return this->x+1;
            }
        }
        return -1;
    }

    int Robot::robotYToVector(int direction, X_VECTOR x_vector) {
        if (x_vector == _4X) {
            direction = direction % 4;
            if (direction == 0) return this->y + 1;
            if (direction == 1 || direction == 3) return this->y;
            if (direction == 2) return this->y - 1;
        }
        else if (x_vector == _8X) {
            direction = (direction - 4) % 8;
            switch (direction) {
                case 0:
                case 1:
                case 7:
                    return this->y +1;
                case 2:
                case 6:
                    return this->y;
                case 3:
                case 4:
                case 5:
                    return this->y-1;
            }
        }
        return -1;
    }

    int Robot::lookAt(const int direction) {
        int const check_x = robotXToVector(direction,_8X);
        int const check_y = robotYToVector(direction,_8X);

        switch (_map->getObjectType(check_x,check_y)) {
            case WALL:
                return WALL_JUMP;
            case FOOD:
                return FOOD_JUMP;
            case ROBOT:
                return ROBOT_JUMP;
            case EMPTY:
                return EMPTY_JUMP;
            default:
                return 0;
        }
    }

    void Robot::kick(int direction) {
        int const check_x = robotXToVector(direction,_8X);
        int const check_y = robotYToVector(direction,_8X);

        switch (_map->getObjectType(check_x,check_y)) {
            case WALL: {
                std::cout << "The robot: " << this->_id << " is kicking the WALL" << std::endl;
                this->_hp -= WALL_DAMAGE;
                break;
            }
            case FOOD: {
                //todo destroy food
                std::cout << "The robot: " << this->_id << " is kicking the FOOD" << std::endl;
                this->_hp += FOOD_RESTORE_HP;
                break;
            }
            case ROBOT: {

                Robot* kicked_robot = this->_map->getRobot(check_x,check_y);
                if (kicked_robot != NULL) {
                    std::cout << "The robot: " << _id << " is kicking the robot: " << kicked_robot->_id << std::endl;
                    kicked_robot->_hp -= ROBOT_DAMAGE;
                }
                // kicked_robot.hp -= kicked_robot.hp;
                break;
            }
            default:
                break;
        }
    }

    void Robot::executeAction(){
        int actual_gen = _gens[_current_state];
        //0-3 move
        IF_INERVAL(actual_gen,0,3) {
            move(actual_gen);
            _current_state = ++_current_state % GEN_LENGHT;
        }
        else IF_INERVAL(actual_gen,4,11) {
            const int jump = lookAt(actual_gen);
            _current_state = (_current_state + jump) % GEN_LENGHT;
        }
        else IF_INERVAL(actual_gen,12,19) {
            kick(actual_gen);
        }
        else _current_state = ++_current_state % GEN_LENGHT;


        if (--_hp <= 0) {
            die();
        }
    }
}
