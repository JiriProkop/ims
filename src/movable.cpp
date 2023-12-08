#include "movable.hpp"
#include "grid.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>

/**
 * Returns a random double between 0 and 1
 *
 * @return random double between 0 and 1
 */
double getRand() {
    std::srand(std::time(nullptr));
    return ((double)std::rand()) / RAND_MAX;
}

/**
 * Get pedestrian velocity in grid squares.
 *
 * @return velocity in grid squares.
 */
int getPederstrianVelocity() {
    double rand = getRand();
    if (rand <= 0.273 && rand >= 0) {
        return 2;
    } else if (rand <= 0.793 && rand > 0.273) {
        return 3;
    } else if (rand <= 0.93 && rand > 0.793) {
        return 4;
    } else if (rand <= 0.978 && rand > 0.93) {
        return 5;
    } else {
        return 6;
    }
}

/**
 * Get the direction where car is headed.
 *
 * @param orientation The orientation of the car.
 *
 * @return The end direction of the car.
 */
int getCarEndDirection(Orientation orientation) {
    double rand = getRand();
    if (rand >= 0 && rand < 0.5) {
        // go straight
        switch (orientation) {
            case Orientation::left: {
                return Orientation::right;
            }
            case Orientation::right: {
                return Orientation::left;
            }
            case Orientation::down: {
                return Orientation::up;
            }
            case Orientation::up: {
                return Orientation::down;
            }
        }
    } else if (rand >= 0.5 && rand <= 0.75) {
        // go right
        switch (orientation) {
            case Orientation::left: {
                return Orientation::down;
            }
            case Orientation::right: {
                return Orientation::up;
            }
            case Orientation::down: {
                return Orientation::right;
            }
            case Orientation::up: {
                return Orientation::left;
            }
        }
    } else {
        // go left
        switch (orientation) {
            case Orientation::left: {
                return Orientation::up;
            }
            case Orientation::right: {
                return Orientation::down;
            }
            case Orientation::down: {
                return Orientation::left;
            }
            case Orientation::up: {
                return Orientation::right;
            }
        }
    }
    return 0;
}

/**
 * Creates a movable object (e.g. a car)
 *
 * @param _kind The kind of movable object to create.
 * @param _start_x The X point to create the object on the grid.
 * @param _start_y The Y point to create the object on the grid.
 * @param _end_x The X point to end the object in.
 * @param _end_y The Y point to end the object in.
 * @param _orientation The orientation of the object.
 * @param grid The grid to create the object in.
 */
Movable::Movable(MovableThing _kind, int _start_x, int _start_y, int _end_x, int _end_y, Orientation _orientation, Grid *grid) {
    kind = _kind;
    x = _start_x;
    y = _start_y;
    end_x = _end_x;
    end_y = _end_y;
    orientation = _orientation;
    aggressivity = getRand();
    if (kind == person) {
        // TODO get person's end zone
        grid->createPerson(x, y);
        velocity = getPederstrianVelocity();
    } else if (kind == car) {
        car_end_direction = getCarEndDirection(orientation);
        grid->createCar(x, y, orientation);
        velocity = initial_car_velocity;
    }
}
/**
 * Checks if the way for the object is clear
 *
 * @param grid The grid.
 *
 * @return Returns a boolean (true if the way is clear).
 */
bool Movable::checkIfClearWay(Grid *grid) {
    // how far should we check the space
    int check_end_x = x;
    int check_end_y = y;

    int space = 1;
    if (kind == person) {
        space += SPACE_BETWEEN_PEOPLE;
    } else {
        space += SPACE_BETWEEN_CARS;
    }

    int add_x = 0;
    int add_y = 0;

    if (orientation == left) {
        check_end_x -= space;
        add_x = -1;
    } else if (orientation == right) {
        check_end_x += space;
        add_x = 1;
    } else if (orientation == up) {
        check_end_y += space;
        add_y = 1;
    } else if (orientation == down) {
        check_end_y -= space;
        add_y = -1;
    }

    for (int i = x + add_x; i != check_end_x; i += add_x) {
        if (!grid->getPoint(i, check_end_y).isEmpty()) {
            return false;
        }
    }

    for (int j = y + add_y; j != check_end_y; j += add_y) {
        if (!grid->getPoint(check_end_x, j).isEmpty()) {
            return false;
        }
    }

    // TODO only checks the left front point of the car, is it good enough?

    return true;
}

/**
 * Checks if the object is in its finish
 *
 * @return Returns true, if the object is in its finish.
 */
bool Movable::checkIfFinished() {
    bool finished = false; // default value
    // TODO if person, check zones if in dest zone.
    if (x == end_x && y == end_y) {
        finished = true;
    }

    return finished;
}

/**
 * Checks if the way is clear (and not finished) and if so, move the object by one point.
 * 
 * @param grid The grid.
*/
void Movable::move(Grid *grid) {
    if (checkIfClearWay(grid) && !checkIfFinished()) {
        int new_x = x;
        int new_y = y;

        if (orientation == left) {
            new_x -= 1;
        } else if (orientation == right) {
            new_x += 1;
        } else if (orientation == up) {
            new_y += 1;
        } else if (orientation == down) {
            new_y -= 1;
        }

        if (kind == person) {
            grid->removePerson(x, y);
            grid->createPerson(new_x, new_y);
        } else if (kind == car) {
            grid->removeCar(x, y, orientation);
            grid->createCar(new_x, new_y, orientation);
        }

        x = new_x;
        y = new_y;
    }
}

/**
 * Removes the object from the grid.
 *
 * @param grid The grid.
 */
void Movable::removeMovable(Grid *grid) {
    if (kind == person) {
        grid->removePerson(x, y);
    } else if (kind == car) {
        grid->removeCar(x, y, orientation);
    }
}

/**
 * Slows down the car.
 */
void Movable::carSlowDown() {
    velocity -= car_speed_change;
    if (velocity < 0) {
        velocity = 0;
    }
}

/**
 * Speeds up the car.
 */
void Movable::carSpeedUp() { velocity += car_speed_change; }

/**
 * Stops the car.
 */
void Movable::carStop() { velocity = 0; }

/**
 * Checks if the car semaphore is green.
 *
 * @param grid The grid.
 * @return Returns true, if the car semaphore is green.
 */
bool Movable::isCarSemaphoreGreen(Grid *grid) {
    switch (orientation) {
        case Orientation::left:
        case Orientation::right:
            return grid->car_semaphore_horizontal == grid->car_semaphore_horizontal.green();
        case Orientation::up:
        case Orientation::down:
            return grid->car_semaphore_vertical == grid->car_semaphore_vertical.green();
    }
    return false; // to not get a warning
}

/**
 * Checks if the pedestrian semaphore is green.
 *
 * @param grid The grid.
 * @return Returns true, if the pedestrian semaphore is green.
 */
bool Movable::isPedestrianSemaphoreGreen(Grid *grid) {
    // TODO pozna se podle cilove sekce a orientace
    return false;
}

/**
 * Checks if the pedestrian is on a crosswalk.
 *
 * @param grid The grid.
 * @return Returns true, if the pedestrian is on a crosswalk.
 */
bool Movable::amIonCrosswalk(Grid *grid) {
    // TODO pozna se podle cilove sekce a orientace
    return false;
}

/**
 * Check all the rules with semaphores.
 *
 * @param grid The grid.
 * @return Returns true, if the object can go.
 */
bool Movable::canIGoWithSemaphores(Grid *grid) {
    // check all the rules :skull
    if (!checkIfClearWay(grid)) {
        return false;
    }
    if (kind == car && isCarSemaphoreGreen(grid)) {
        return true;
    } else if (kind == person && (isPedestrianSemaphoreGreen(grid) || amIonCrosswalk(grid))) {
        // kdyz chci jit nekam, kam chce uz also nekdo jit, random se vybere kdo pujde.
        return true;
    }
    return false;
}

/**
 * Check all the rules without semaphores.
 *
 * @param grid The grid.
 * @return Returns true, if the object can go.
 */
bool Movable::canIGoWithoutSemaphores(Grid *grid) {
    // TODO
    return true;
    // crossing for pedestrians or cars kdyz nejsou na hlavni:
    // l_veh - vzdalenost od auta od prechodu nebo od auta
    // v_veh - budouci nebo stavajici rychlost auta
    // l_ped - vzdalenost chodce od konce prechodu/pruhu
    // v_ped - ocekavan rychlost chodce/auta. Da se pouzit prumer.
    // t - podle akceptace chodce/auta, u chodce se muze urcit podle agresivity chodce
    // ROVNICE: l_veh/v_veh - l_ped/v_ped >= t
}
