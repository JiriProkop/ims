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

                Movable tmp2(car, 110, 60, 55, 4, left, &grid);
                movableThings.push_back(tmp2);

            } catch (const std::exception &e) {
            }
        }
        if (i % 2 == 0) {
            try {
                Movable tmp(person, 0, 0, 50, 50, right, &grid);
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

// RULES:
// with lights
// auta: kdyz je cervena nebo jsou na chodniku jeste lidi, stuj.
//       jinak jed
// lidi: kdyz je zelena a nebo cervena, ale jsi jeste na chodniku, jdi
//       jinak stuj

// also, pokud chci projit nekudy, kde je auto, cekam
//       stejne u auta

// kdyz chci jit nekam, kam chce uz also nekdo jit, random se vybere kdo pujde.

// one sim round is 1 second

// without lights
// crossing for pedestrians or cars kdyz nejsou na hlavni:
// l_veh - vzdalenost od auta od prechodu nebo od auta
// v_veh - budouci nebo stavajici rychlost auta
// l_ped - vzdalenost chodce od konce prechodu/pruhu
// v_ped - ocekavan rychlost chodce/auta. Da se pouzit prumer.
// t - podle akceptace chodce/auta, u chodce se muze urcit podle agresivity chodce
// ROVNICE: l_veh/v_veh - l_ped/v_ped >= t

// rychlost aut
// prumer 25 km/h ~= 7 m/s coz by bylo 14 policek :aware:
// proto bude potreba vzit v potaz i zrychleni a zpomaleni
// zrychleni i zpomalnei - 2 m/s^2
//      special case: possible kolize - zastaveni skoro hned
