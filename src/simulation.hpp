#include "grid.hpp"

#ifndef SIMULATION_HPP
#define SIMULATION_HPP

class Simulation {
    private:
        const int grid_size = 100;
        bool signalizedIntersection;
        Grid grid = Grid(grid_size);
        Grid nextStepGrid = Grid(grid_size);
        void signalizedIntersectionRules();
        void unsignalizedIntersectionRules();

    public:
        Simulation(bool signalizedIntersection);
        void makeStep();

};

#endif
