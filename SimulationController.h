//
// Created by grusted on 12/23/24.
//

#include <iostream>
#include <vector>
#include "mapObject.h"

#ifndef SIMULATIONCONTROLLER_H
#define SIMULATIONCONTROLLER_H


class SimulationController {
    private:
    GeneticThings::Map *map;
    std::vector<GeneticThings::Robot*> robots;

    public:
        SimulationController();
        ~SimulationController();
        void startSimulation();
        void deleteDeadRobots();
};



#endif //SIMULATIONCONTROLLER_H
