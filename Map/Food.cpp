#include "Food.h"

using namespace genetic_things;

Food::Food(int x, int y, Map *map) : MapObject(x, y, map){
    this->_type = FOOD;
}
Food::~Food(){};

void Food::executeAction() {

}
