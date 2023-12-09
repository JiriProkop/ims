#include "grid.hpp"
#include "movable.hpp"
#include "image.hpp"

#ifndef SIMULATION_HPP
#define SIMULATION_HPP

class Simulation {
    private:
        bool signalizedIntersection;
        Grid grid = Grid(DEFAULT_IMAGE_SIZE);
        Grid nextStepGrid = Grid(DEFAULT_IMAGE_SIZE);
        int finishedCars;
        int finishedPedestrians;

    public:
        Simulation(bool signalizedIntersection);
        void makeStep(std::vector<Movable> *movableThings);
        void Run();
};

#endif
