#include "simulation.hpp"
#include "iostream"
#include <vector>

/**
 * Creates a new simulation object.
 *
 * @param signalizedIntersection Whether the intersection is signalized or not.
 */
Simulation::Simulation(bool signalizedIntersection) {
    std::srand(time(0));
    this->signalizedIntersection = signalizedIntersection;
    generateCrossroadBackgroud(&grid);
    finishedPedestrians = 0;
    finishedCars = 0;
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
    const int cycle_time = 250;
    second = second % cycle_time;

    const int CAR_GREEN_TIME = 120;
    const int CAR_HORIZONTAL_SEM_START = 0;
    const int CAR_VERTICAL_SEM_START = 130;
    const int PED_GREEN_TIME = 20;

    if (second == CAR_HORIZONTAL_SEM_START) {
        grid.car_semaphore_horizontal = grid.car_semaphore_horizontal.green();
        grid.pedestrian_semaphore_top = grid.pedestrian_semaphore_top.green();
        grid.pedestrian_semaphore_bottom = grid.pedestrian_semaphore_bottom.green();

    } else if (second == CAR_HORIZONTAL_SEM_START + PED_GREEN_TIME) {
        grid.pedestrian_semaphore_top = grid.pedestrian_semaphore_top.red();
        grid.pedestrian_semaphore_bottom = grid.pedestrian_semaphore_bottom.red();
        
    } else if (second == CAR_GREEN_TIME) {
        grid.car_semaphore_horizontal = grid.car_semaphore_horizontal.red();

    } else if (second == CAR_VERTICAL_SEM_START) {
        grid.car_semaphore_vertical = grid.car_semaphore_vertical.green();
        grid.pedestrian_semaphore_left = grid.pedestrian_semaphore_left.green();
        grid.pedestrian_semaphore_right = grid.pedestrian_semaphore_right.green();

    } else if (second == CAR_VERTICAL_SEM_START + PED_GREEN_TIME) {
        grid.pedestrian_semaphore_left = grid.pedestrian_semaphore_left.red();
        grid.pedestrian_semaphore_right = grid.pedestrian_semaphore_right.red();

    } else if (second == CAR_GREEN_TIME + CAR_VERTICAL_SEM_START - 10) {
        grid.car_semaphore_vertical = grid.car_semaphore_vertical.red();
    }
}

/**
 * Runs the simulation.
 */
void Simulation::Run() {
    int SECONDS = 250;

    std::vector<Movable> movableThings;
    for (int i = 0; i < SECONDS; i++) {
        makeStep(&movableThings);
        
        if (i % 16 == 0) {
            try {

                Movable tmp2(car, 110, 60, 55, 4, left, &grid);
                movableThings.push_back(tmp2);

            } catch (const std::exception &e) {
            }
        }
        if (i % 5 == 0) {
            try {
                //Movable tmp(person, 0, 0, 50, 50, right, &grid);
                //movableThings.push_back(tmp);
            } catch (const std::exception &e) {
            }
        }
        semaphoreRotation(i);

        generateImage(grid, DEFAULT_IMAGE_SIZE, "output/" + std::to_string(i) + ".bmp");
    }

    std::cout << "This many people have finished the journey in 250 seconds: ";
    std::cout << finishedCars;
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
