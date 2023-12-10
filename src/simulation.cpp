#include "simulation.hpp"
#include "iostream"
#include "arguments.hpp"
#include <vector>

/**
 * Creates a new simulation object.
 *
 * @param signalizedIntersection Whether the intersection is signalized or not.
 */
Simulation::Simulation(bool signalizedIntersection, int _simulationLength, int _skacelovaGreenLength, int _purkynovaGreenLength) {
    std::srand(time(0));
    this->signalizedIntersection = signalizedIntersection;
    generateCrossroadBackgroud(&grid);
    finishedPedestrians = 0;
    finishedCars = 0;
    simulationLength = _simulationLength;
    skacelovaGreenLength = _skacelovaGreenLength;
    purkynovaGreenLength = _purkynovaGreenLength;
}

void Simulation::makeStep(std::vector<Movable> *movableThings) {
    for (size_t i = 0; i < movableThings->size(); i++) {
        if (movableThings->at(i).checkIfFinished()) {
            movableThings->at(i).removeMovable(&grid);

            if (movableThings->at(i).getKind() == person) {
                finishedPedestrians++;
            } else if (movableThings->at(i).getKind() == car) {
                finishedCars++;
            }

            movableThings->erase(movableThings->begin() + i);
        } else {
            bool output = movableThings->at(i).move(&grid, signalizedIntersection);

            if (output) {
            if (movableThings->at(i).getKind() == person) {
                finishedPedestrians++;
            } else if (movableThings->at(i).getKind() == car) {
                finishedCars++;
            }

            movableThings->erase(movableThings->begin() + i);
            }

        }
    }
}

void Simulation::semaphoreRotation(int second) {
    const int CAR_HORIZONTAL_SEM_START = 0;
    const int START_DIFF = 5;
    const int HORIZONTAL_GREEN_LENGTH = skacelovaGreenLength;
    const int VERTICAL_GREEN_LENGTH = purkynovaGreenLength;

    const int cycle_time = HORIZONTAL_GREEN_LENGTH + START_DIFF + VERTICAL_GREEN_LENGTH;
    second = second % cycle_time;

    if (second == CAR_HORIZONTAL_SEM_START) {
        grid.car_semaphore_horizontal = grid.car_semaphore_horizontal.green();
    
    } else if (second == CAR_HORIZONTAL_SEM_START + START_DIFF) {
        grid.pedestrian_semaphore_top = grid.pedestrian_semaphore_top.green();
        grid.pedestrian_semaphore_bottom = grid.pedestrian_semaphore_bottom.green();
    
    } else if (second == CAR_HORIZONTAL_SEM_START + HORIZONTAL_GREEN_LENGTH - START_DIFF) { 
        grid.pedestrian_semaphore_top = grid.pedestrian_semaphore_top.red();
        grid.pedestrian_semaphore_bottom = grid.pedestrian_semaphore_bottom.red();

    } else if (second == CAR_HORIZONTAL_SEM_START + HORIZONTAL_GREEN_LENGTH) {
        grid.car_semaphore_horizontal = grid.car_semaphore_horizontal.red();
        
    } else if (second == HORIZONTAL_GREEN_LENGTH + START_DIFF) {
        grid.car_semaphore_vertical = grid.car_semaphore_vertical.green();

    } else if (second == HORIZONTAL_GREEN_LENGTH + START_DIFF + START_DIFF) {
        grid.pedestrian_semaphore_left = grid.pedestrian_semaphore_left.green();
        grid.pedestrian_semaphore_right = grid.pedestrian_semaphore_right.green();

    } else if (second == HORIZONTAL_GREEN_LENGTH + START_DIFF + VERTICAL_GREEN_LENGTH - START_DIFF) {
        grid.pedestrian_semaphore_left = grid.pedestrian_semaphore_left.red();
        grid.pedestrian_semaphore_right = grid.pedestrian_semaphore_right.red();

    } else if (second == HORIZONTAL_GREEN_LENGTH + START_DIFF + VERTICAL_GREEN_LENGTH) {
        grid.car_semaphore_vertical = grid.car_semaphore_vertical.red();
    }
}

/**
 * Runs the simulation.
 */
void Simulation::Run() {
    int SECONDS = simulationLength;

    std::vector<Movable> movableThings;
    for (int i = 0; i < SECONDS; i++) {
        makeStep(&movableThings);
        
        if (i % 4 == 0) {
            try {

                Movable tmp2(car, &grid);
                movableThings.push_back(tmp2);

            } catch (const std::exception &e) {
            }
        }
        if (i % 2 == 0) {
            try {
                Movable tmp(person, &grid);
                movableThings.push_back(tmp);
            } catch (const std::exception &e) {
            }
        }
        semaphoreRotation(i);

        generateImage(grid, DEFAULT_IMAGE_SIZE, "output/" + std::to_string(i) + ".bmp");
    }

    std::cout << "cars finished: ";
    std::cout << finishedCars;
    std::cout << "\n";
    std::cout << "pedestrians finished: ";
    std::cout << finishedPedestrians;
    std::cout << "\n";
}