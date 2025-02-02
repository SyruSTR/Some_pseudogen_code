#include "robot.h"
#include <iostream>
#include <regex>

namespace GeneticThings {
#define IF_INERVAL(value,a,b) if(value>=a && value<=b)

    Robot::Robot(int x, int y, Map *map , int id):  MapObject(x,y, map) {
        this->id = id;
        this->type = ROBOT;
        this->hp = START_HP;
        this->isAlive = true;
        for (int i =0; i<GEN_LENGHT;i++) {
            gen[i] = rand() % GEN_LENGHT;
        }
        std::cout << "Robot " << id << " created" << std::endl;
    }

    Robot::Robot(int x, int y, Map *map, int id, std::string &gens_from_file): MapObject(x,y, map) {
        this->type = ROBOT;
        this->id = id;
        this->hp = START_HP;
        this->isAlive = true;
        ValidateAndParseGen(gens_from_file);

        std::cout << "Robot " << id << " created" << std::endl;
    }

    void Robot::ValidateAndParseGen( std::string &raw_line) {
        // Regex to match the format: [ num1, num2, ..., numN ]
        std::regex pattern(R"(\[\s*(\d{1,2}(,\s*\d{1,2})*)\s*\])");
        std::smatch match;

        if (!std::regex_match(raw_line, match, pattern)) {
            throw std::invalid_argument("Invalid gen. Expected format: [ num1, num2, ..., numN ]");
        }

        //stream of numbers
        std::istringstream iss(match[1].str());
        std::string tmpNumber;
        int i = 0;

        while (std::getline(iss, tmpNumber, ',')) {
            int value = std::stoi(tmpNumber);
            if (value < 0 || value >= GEN_LENGHT) {
                throw std::out_of_range("Number out of range [0,63]:" + std::to_string(value));
            }
            this->gen[i] = static_cast<short int>(value);
            i++;
        }

        if (i != GEN_LENGHT) {
            throw std::length_error("Line doesnt contain 64 numbers, it contains: " + std::to_string(i));
        }
    }

    Robot::~Robot() {
        std::cout << "Robot " << id << " destroyed" << std::endl;
    }

    int Robot::get_id() const {
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
        return -1;
    }

    int Robot::robotYToVector(int direction) {
        direction = direction % 4;
        if (direction == 0) return this->y + 1;
        if (direction == 1 || direction == 3) return this->y;
        if (direction == 2) return this->y - 1;
        return -1;
    }

    int Robot::lookAt(const int direction) {
        int const check_x = robotXToVector(direction);
        int const check_y = robotYToVector(direction);

        switch (map->getObjectType(check_x,check_y)) {
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
        int const check_x = robotXToVector(direction);
        int const check_y = robotYToVector(direction);

        switch (map->getObjectType(check_x,check_y)) {
            case WALL: {
                std::cout << "The robot: " << this->id << " is kicking the WALL" << std::endl;
                this->hp -= WALL_DAMAGE;
                break;
            }
            case FOOD: {
                //todo destroy food
                std::cout << "The robot: " << this->id << " is kicking the FOOD" << std::endl;
                this->hp += FOOD_RESTORE_HP;
                break;
            }
            case ROBOT: {

                Robot* kicked_robot = this->map->GetRobot(check_x,check_y);
                if (kicked_robot != NULL) {
                    std::cout << "The robot: " << this->id << " is kicking the robot: " << kicked_robot->id << std::endl;
                    kicked_robot->hp -= ROBOT_DAMAGE;
                }
                // kicked_robot.hp -= kicked_robot.hp;
                break;
            }
            default:
                break;
        }
    }

    void Robot::ExecuteAction(){
        int actual_gen = gen[current_state];
        //0-3 move
        IF_INERVAL(actual_gen,0,3) {
            move(actual_gen);
            current_state = ++current_state % GEN_LENGHT;
        }
        else IF_INERVAL(actual_gen,4,11) {
            const int jump = lookAt(actual_gen);
            current_state = (current_state + jump) % GEN_LENGHT;
        }
        else IF_INERVAL(actual_gen,12,23) {
            kick(actual_gen);
        }
        else current_state = ++current_state % GEN_LENGHT;


        if (--hp <= 0) {
            die();
        }
    }
}
