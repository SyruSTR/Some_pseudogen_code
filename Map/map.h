//
// Created by grusted on 12/11/24.
//


/**
 * @file map.h
 *
 */
#ifndef MAP_H
#define MAP_H
#include <string>
#include <vector>


namespace genetic_things {

    enum ObjectType {
        EMPTY,
        WALL,
        ROBOT,
        FOOD
      };


    class MapObject;
    class Robot;
    class Wall;
    class Empty;

    /**
     * @class Map
     * @brief class represent grid of @see MapObject
     */
    class Map {
    private:

        std::vector<Robot*> _robots;
        /**
         * @bried height and wight of grid
         */
        int _width, _height;
        /**
         * @brief grid of objects represents like array[][]
         */
        MapObject ***_grid{};

        void initMap();
        void fillEmpty();
        void fillBorders();
    public:
        /**
         *
         * @param width of map
         * @param height of map
         *
         * @brief default Map constructor
         */
        Map(int width, int height);

        /**
         *
         * @param mapFile
         * @param gensFile
         *
         * @brief Map constructor, fill map from file
         */
        Map(const std::string& map_name,const std::string& gen_name);

        /**
         *
         * @param id for new robot
         * @return created ptr to created robot. If its NULL, grid dont have space for new robot.
         *
         */
        void addRobotAtRandomPlace(int id);

        std::vector<Robot*>* getRobots();

        /**
         *
         * @param x checking x coordinate
         * @param y checking y coordinate
         *
         * @brief Does grid have a wall at this position?
         */
        bool isWall(int x, int y);
        /**
         *
         * @param x checking x coordinate
         * @param y checking y coordinate
         * @return
         *
         * @brief Does grid have a robot at this position?
         */
        bool isRobot(int x, int y);

        /**
         * @brief print actual grid
         */
        void printMap() const;

        /**
         *
         * @param x1 x position of first object
         * @param y1 y position of first object
         * @param x2 x position of second object
         * @param y2 y position of second object
         *
         * @brief swap 2 @see MapObject (objects may be .....)
         */
        void swapObjects(int x1, int y1, int x2, int y2);
        MapObject* getObject(int x, int y);
        Robot* getRobot(int x, int y);
        void deleteObject(int x, int y);
        ObjectType getObjectType(int x, int y);
        ~Map();
    };
}



#endif //MAP_H
