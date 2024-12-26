//
// Created by grusted on 12/11/24.
//


/**
 * @file map.h
 *
 */
#ifndef MAP_H
#define MAP_H



namespace GeneticThings {

    class MapObject;
    class Robot;

    /**
     * @class Map
     * @brief class represent grid of @see MapObject
     */
    class Map {
    private:
        /**
         * @bried height and wight of grid
         */
        int width, height;
        /**
         * @brief grid of objects represents like array[][]
         */
        MapObject ***grid{};
    public:
        /**
         *
         * @param width of map
         * @param height of map
         *
         * @brief Map constructor
         */
        Map(int width, int height);

        /**
         *
         * @param id for new robot
         * @return created ptr to created robot. If its NULL, grid dont have space for new robot.
         *
         */
        Robot* addRobot_at_random_place(int id);

        /**
         *
         * @param x checking x coordinate
         * @param y checking y coordinate
         * @return
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
        MapObject* get_object(int x, int y);
        void delete_object(int x, int y);
        ~Map();
    };
}



#endif //MAP_H
