//
// Created by grusted on 12/11/24.
//

#ifndef MAP_H
#define MAP_H



namespace GeneticThings {

    class MapObject;
    class Robot;

    class Map {
    private:
        int width, height;
        MapObject ***map{};
    public:
        Map(int width, int height);
        Robot* addRobot_at_random_place(int id);
        bool isWall(int x, int y);
        bool isRobot(int x, int y);
        void printMap() const;
        void swapObjects(int x1, int y1, int x2, int y2);
        ~Map();
    };
}



#endif //MAP_H
