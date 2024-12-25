//
// Created by grusted on 12/23/24.
//

#include <stdio.h>
#include <iostream>

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
};



#endif //SIMULATIONCONTROLLER_H
