//
// Created by grusted on 12/11/24.
//

#ifndef MAP_H
#define MAP_H



namespace GeneticThings {

    class MapObject;

    class Map {
    private:
        int width, height;
        MapObject **map{};
    public:
        Map(int width, int height);
        bool isWall(int x, int y);
        bool isRobot(int x, int y);
        void printMap() const;
        ~Map();
    };
}



#endif //MAP_H
