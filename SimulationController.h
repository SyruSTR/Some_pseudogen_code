//
// Created by grusted on 12/23/24.
//

#include <iostream>
#include <vector>
#include "Map/mapObject.h"

#ifndef SIMULATIONCONTROLLER_H
#define SIMULATIONCONTROLLER_H


class SimulationController {
    private:
    genetic_things::Map *_map;
    std::vector<genetic_things::Robot*> * _robots;

    public:
        SimulationController();
        ~SimulationController();
        void startSimulation();
        void deleteDeadRobots();
};



#endif //SIMULATIONCONTROLLER_H
