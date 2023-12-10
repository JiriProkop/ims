#include "grid.hpp"
#include "movable.hpp"
#include "image.hpp"
#include "arguments.hpp"

#ifndef SIMULATION_HPP
#define SIMULATION_HPP

class Simulation {
    private:
        bool signalizedIntersection;
        Grid grid = Grid(DEFAULT_IMAGE_SIZE);
        Grid nextStepGrid = Grid(DEFAULT_IMAGE_SIZE);
        void semaphoreRotation(int second);
        int finishedCars;
        int finishedPedestrians;
        int simulationLength;
        int skacelovaGreenLength;
        int purkynovaGreenLength;

      public:
        Simulation(bool signalizedIntersection, int simulationLength, int skacelovaGreenLength, int purkynovaGreenLength);
        void makeStep(std::vector<Movable> *movableThings);
        void Run();
};

#endif
