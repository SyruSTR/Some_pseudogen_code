#include "Empty.h"

using namespace genetic_things;

    Empty::Empty(int x, int y, Map *map) : MapObject(x, y, map){
        this->_type = EMPTY;
    }
    Empty::~Empty(){};

    void Empty::executeAction() {

    }



