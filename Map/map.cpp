//
// Created by grusted on 12/11/24.
//

#include "map.h"
#include "Empty.h"
#include "Wall.h"
#include "robot.h"

#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_set>


namespace genetic_things {

    Map::Map(int width, int height) {
        this->_width = width;
        this->_height = height;

        _grid = new MapObject**[width];

        for (int x = 0; x < width; ++x) {
            _grid[x] = new MapObject*[height];
        }

        //filling the map off EMPTY space
        for (int y = 0; y < _height; ++y) {
            for (int x = 0; x < _width; ++x) {
                _grid[x][y] = new Empty(x, y, this);
            }
        }

        //add borders for map
        for (int y = 0; y < _height; ++y) {
            for (int x = 0; x < _width; ++x) {
                if (y == 0 || y == _height - 1 || x == 0 || x == _width - 1) {
                    MapObject* tmp = new Wall(x, y, this);
                    std::swap(_grid[x][y], tmp);
                    delete tmp;
                }
            }
        }
    }

    Map::Map(const std::string& file_name, const std::string& gens_name) {

        std::ifstream map_file(file_name);

        if (!map_file.good())
            throw std::runtime_error("Map File does not exist");

        std::string tmp_line;
        std::vector<std::string> lines;

        while (getline(map_file, tmp_line)) {
            lines.push_back(tmp_line);
        }
        map_file.close();

        //check the line`s width, they should be equaled
        int width = lines[0].length();
        for (int i = 1; i < lines.size(); ++i) {
            if (lines[i].length() != width)
                throw std::invalid_argument("Wrong map size. Check the lines width");
        }

        this->_width = width;
        this->_height = lines.size();

        _grid = new MapObject**[_width];

        for (int x = 0; x < _width; ++x) {
            _grid[x] = new MapObject*[_height];
        }

        //filling the map off EMPTY space
        for (int y = 0; y < _height; ++y) {
            for (int x = 0; x < _width; ++x) {
                _grid[x][y] = new Empty(x, y, this);
            }
        }

        //open gens file
        std::ifstream gens_file(gens_name);
        std::string tmp_gens_line;
        int robot_id = 0;

        for (int y = 0; y < _height; ++y) {
            for (int x = 0; x < _width; ++x) {
                MapObject* tmp;
                bool found = false;
                switch (lines[y][x]) {
                    case '#': {
                        found = true;
                        tmp = new Wall(x, y, this);
                        break;
                    }
                    case '@': {
                        if (!gens_file.good())
                            throw std::runtime_error("Gens File does not exist");
                        if (getline(gens_file,tmp_gens_line)) {
                            found = true;
                            tmp = new Robot(x,y,this,robot_id,tmp_gens_line);
                            _robots.push_back(dynamic_cast<Robot*>(tmp));
                            robot_id++;
                        }
                        else {
                            throw std::length_error("Wrong count of gens, check the gens or map. Lines gens count is: " + std::to_string(robot_id));
                        }
                        break;
                    }
                    case ' ': {
                        // EMPTY is already exist
                        break;
                    }
                }
                // tmp = new MapObject(x, y, this, type);
                if (found) {
                    std::swap(_grid[x][y], tmp);
                    delete tmp;
                }
            }
        }
        gens_file.close();
    }


    std::vector<Robot *>* Map::getRobots() {
        return &_robots;
    }



    void Map::addRobotAtRandomPlace(int id) {

        int index = this->_height * this->_width;
        do {
            int y = rand() % (this->_height-1) + 1;
            int x = rand() % (this->_width-1) + 1;

            if (_grid[x][y]->getType() == WALL || _grid[x][y]->getType() == ROBOT) {
                index--;
                continue;
            }

            delete this->_grid[x][y];
            const auto robot = new Robot(x, y, this, id);
            this->_grid[x][y] = robot;
            _robots.push_back(robot);
            return;

        } while (index >= 0);
    }

    bool Map::isWall(int x, int y) {
        return _grid[x][y]->getType() == WALL;
    }

    ObjectType Map::getObjectType(int x, int y) {
        return _grid[x][y]->getType();
    }

    void Map::swapObjects(int x1, int y1, int x2, int y2) {
        if (x1 < 0 || x1 >= _width || y1 < 0 || y1 >= _height ||
        x2 < 0 || x2 >= _width || y2 < 0 || y2 >= _height) {
            std::cerr << "Error: Swap coordinates out of bounds!" << std::endl;
            return;
        }

        MapObject* temp = _grid[x1][y1];
        _grid[x1][y1] = _grid[x2][y2];
        _grid[x1][y1]->x = x1;
        _grid[x1][y1]->y = y1;

        _grid[x2][y2] = temp;
        _grid[x2][y2]->x = x2;
        _grid[x2][y2]->y = y2;

    }

    MapObject* Map::getObject(int x, int y) {
        if (x < 0 || y < 0 || x >= _height || y >= _width ) return nullptr;

        return _grid[x][y];

    }

    void Map::deleteObject(int x, int y) {
        if (x < 0 || y < 0 || x >= _height || y >= _width) return;
        MapObject* empty_space = new Empty(x, y, this);
        std::swap(_grid[x][y], empty_space);
        delete empty_space;
    }


    void Map::printMap() const {
        for (int y = _height-1; y >= 0; --y) {
            for (int x = 0; x < _width; ++x) {
                //just for safe from SIGSEGV
                if (_grid[x][y] != nullptr) {
                    switch (_grid[x][y]->getType()) {
                        case EMPTY:
                            printf("  ");
                        break;
                        case WALL:
                            printf("# ");
                        break;
                        case ROBOT:
                            printf("@ ");
                        break;
                        case FOOD:
                            printf("* ");
                        break;
                        default:
                            printf("^ ");
                    }
                }
            }
            printf("\n");
        }
    }

    Robot* Map::getRobot(int x, int y) {
        MapObject* getted_object = getObject(x, y);

        if (auto robot = dynamic_cast<Robot*>(getted_object)) {
            return robot;
        }

        return nullptr;
    }

    Map::~Map() {
        for (int i = 0; i < _width; ++i) {
            for (int j = 0; j < _height; ++j) {
                delete _grid[i][j];
            }
            delete[] _grid[i];
        }
        delete[] _grid;
    }

}  // namespace genetic_things

