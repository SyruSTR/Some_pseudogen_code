//
// Created by grusted on 12/11/24.
//

#include "map.h"
#include "mapObject.h"

#include "map.h"

#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_set>
#include <filesystem>

#include "robot.h"

namespace GeneticThings {

    Map::Map(int width, int height) {
        this->width = width;
        this->height = height;

        grid = new MapObject**[width];

        for (int x = 0; x < width; ++x) {
            grid[x] = new MapObject*[height];
        }

        //filling the map off EMPTY space
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                grid[x][y] = new MapObject(x, y, this);
            }
        }

        //add borders for map
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                if (y == 0 || y == height - 1 || x == 0 || x == width - 1) {
                    auto tmp = new MapObject(x, y, this, WALL);
                    std::swap(grid[x][y], tmp);
                    delete tmp;
                }
            }
        }
    }

    Map::Map(const std::string& fileName, const std::string& gensName) {

        std::ifstream mapFile(fileName);

        if (!mapFile.good())
            throw std::runtime_error("Map File does not exist");

        std::string tmpLine;
        std::vector<std::string> lines;

        while (getline(mapFile, tmpLine)) {
            lines.push_back(tmpLine);
        }
        mapFile.close();

        //check the line`s width, they should be equaled
        int width = lines[0].length();
        for (int i = 1; i < lines.size(); ++i) {
            if (lines[i].length() != width)
                throw std::invalid_argument("Wrong map size. Check the lines width");
        }

        this->width = width;
        this->height = lines.size();

        grid = new MapObject**[width];

        for (int x = 0; x < width; ++x) {
            grid[x] = new MapObject*[height];
        }

        //filling the map off EMPTY space
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                grid[x][y] = new MapObject(x, y, this);
            }
        }

        //open gens file
        std::ifstream gensFile(gensName);
        std::string tmpGensLine;
        int robot_id = 0;

        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                MapObject* tmp;
                ObjectType type;
                switch (lines[y][x]) {
                    case '#': {
                        type = WALL;
                        break;
                    }
                    case '@': {
                        if (!gensFile.good())
                            throw std::runtime_error("Gens File does not exist");
                        type = ROBOT;
                        if (getline(gensFile,tmpGensLine)) {
                            tmp = new Robot(x,y,this,robot_id,tmpGensLine);
                            std::swap(grid[x][y], tmp);
                            robots.push_back(dynamic_cast<Robot*>(grid[x][y]));
                            delete tmp;
                            robot_id++;
                        }
                        else {
                            throw std::length_error("Wrong count of gens, check the gens or map. Lines gens count is: " + robot_id);
                        }
                        continue;
                    }
                    case ' ': {
                        // EMPTY is already exist
                        continue;
                    }
                }
                tmp = new MapObject(x, y, this, type);
                std::swap(grid[x][y], tmp);
                delete tmp;
            }
        }

        gensFile.close();

    }


    std::vector<Robot *>* Map::getRobots() {
        return &robots;
    }



    void Map::addRobot_at_random_place(int id) {

        int index = this->height * this->width;
        do {
            int y = rand() % (this->height-1) + 1;
            int x = rand() % (this->width-1) + 1;

            if (grid[x][y]->type == WALL || grid[x][y]->type == ROBOT) {
                index--;
                continue;
            }

            delete this->grid[x][y];
            const auto robot = new Robot(x, y, this, id);
            this->grid[x][y] = robot;
            robots.push_back(robot);
            return;

        } while (index >= 0);
    }

    bool Map::isWall(int x, int y) {
        return grid[x][y]->type == WALL;
    }

    ObjectType Map::getObjectType(int x, int y) {
        return grid[x][y]->type;
    }

    void Map::swapObjects(int x1, int y1, int x2, int y2) {
        if (x1 < 0 || x1 >= width || y1 < 0 || y1 >= height ||
        x2 < 0 || x2 >= width || y2 < 0 || y2 >= height) {
            std::cerr << "Error: Swap coordinates out of bounds!" << std::endl;
            return;
        }

        MapObject* temp = grid[x1][y1];
        grid[x1][y1] = grid[x2][y2];
        grid[x1][y1]->x = x1;
        grid[x1][y1]->y = y1;

        grid[x2][y2] = temp;
        grid[x2][y2]->x = x2;
        grid[x2][y2]->y = y2;

    }

    MapObject* Map::get_object(int x, int y) {
        if (x < 0 || y < 0 || x >= height || y >= width ) return nullptr;

        return grid[x][y];

    }

    void Map::delete_object(int x, int y) {
        if (x < 0 || y < 0 || x >= height || y >= width) return;
        MapObject* empty_space = new MapObject(x, y, this);
        std::swap(grid[x][y], empty_space);
        delete empty_space;
    }


    void Map::printMap() const {
        for (int y = height-1; y >= 0; --y) {
            for (int x = 0; x < width; ++x) {
                //just for safe from SIGSEGV
                if (grid[x][y] != nullptr) {
                    switch (grid[x][y]->type) {
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

    Robot* Map::GetRobot(int x, int y) {
        MapObject* getted_object = get_object(x, y);

        if (auto robot = dynamic_cast<Robot*>(getted_object)) {
            return robot;
        }

        return nullptr;
    }

    Map::~Map() {
        for (int i = 0; i < width; ++i) {
            for (int j = 0; j < height; ++j) {
                delete grid[i][j];
            }
            delete[] grid[i];
        }
        delete[] grid;
    }

}  // namespace GeneticThings

