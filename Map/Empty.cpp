#include "Empty.h"

using namespace GeneticThings;

    Empty::Empty(int x, int y, Map *map) : MapObject(x, y, map){
        this->type = EMPTY;
    }
    Empty::~Empty(){};

    void Empty::ExecuteAction() {

    }



