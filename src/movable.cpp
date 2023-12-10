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

bool isInPedZone1(int x, int y) {
    const int x_start = 30;
    const int x_end = 40;
    const int y_start = 82;
    const int y_end = 92;
    return x >= x_start && x <= x_end && y >= y_start && y <= y_end;
}

bool isInPedZone2(int x, int y) {
    const int x_start = 76;
    const int x_end = 86;
    const int y_start = 82;
    const int y_end = 92;
    return x >= x_start && x <= x_end && y >= y_start && y <= y_end;
}

bool isInPedZone3(int x, int y) {
    const int x_start = 30;
    const int x_end = 40;
    const int y_start = 32;
    const int y_end = 42;
    return x >= x_start && x <= x_end && y >= y_start && y <= y_end;
}

bool isInPedZone4(int x, int y) {
    const int x_start = 76;
    const int x_end = 86;
    const int y_start = 32;
    const int y_end = 42;
    return x >= x_start && x <= x_end && y >= y_start && y <= y_end;
}

std::function<bool(int, int)> Movable::getPedEndZone(int start_x, int start_y) {
    double rand = getRand();
    if (isInPedZone1(start_x, start_y)) {
        if (rand <= 0.5) {
            orientation = Orientation::right;
            pedEndzone = 2;
            return isInPedZone2;
        } else {
            orientation = Orientation::down;
            pedEndzone = 3;
            return isInPedZone3;
        }
    } else if (isInPedZone2(start_x, start_y)) {
        if (rand <= 0.5) {
            orientation = Orientation::left;
            pedEndzone = 1;
            return isInPedZone1;
        } else {
            orientation = Orientation::down;
            pedEndzone = 4;
            return isInPedZone4;
        }
    } else if (isInPedZone3(start_x, start_y)) {
        if (rand <= 0.5) {
            orientation = Orientation::right;
            pedEndzone = 4;
            return isInPedZone4;
        } else {
            orientation = Orientation::up;
            pedEndzone = 1;
            return isInPedZone1;
        }
    } else if (isInPedZone4(start_x, start_y)) {
        if (rand <= 0.5) {
            orientation = Orientation::left;
            pedEndzone = 3;
            return isInPedZone3;
        } else {
            orientation = Orientation::up;
            pedEndzone = 2;
            return isInPedZone2;
        }
    }
    return isInPedZone1; // to not get a warning
}

void Movable::getCoordinationsForPedestrian(Grid *grid) {
    int spawn_x_start;
    int spawn_y_start;
    double rand = getRand();
    if (rand >= 0 && rand < 0.2) {
        // top left spawn
        spawn_x_start = 30;
        spawn_y_start = 82;
    } else if (rand >= 0.2 && rand < 0.4) {
        // botom right spawn
        spawn_x_start = 76;
        spawn_y_start = 32;
    } else if (rand >= 0.4 && rand < 0.7) {
        // top right spawn
        spawn_x_start = 76;
        spawn_y_start = 82;
    } else {
        // bottom left spawn
        spawn_x_start = 30;
        spawn_y_start = 32;
    }

    int rand_x = getRand() * 10;
    int rand_y = getRand() * 10;
    while (!grid->getPoint(rand_x + spawn_x_start, rand_y + spawn_y_start).isEmpty()) {
        rand_x = getRand() * 10;
        rand_y = getRand() * 10;
    }
    x = rand_x + spawn_x_start;
    y = rand_y + spawn_y_start;
}

void Movable::getCoordinationsForCar(Grid *grid) {
    const int possible_end_top_x = 64;
    const int possible_end_top_y = 110;
    const int possible_end_bottom_x = 52;
    const int possible_end_bottom_y = 10;
    const int possible_end_left_x = 10;
    const int possible_end_left_y = 66;
    const int possible_end_right_x = 110;
    const int possible_end_right_y = 54;

    double rand_spawn = getRand();
    double rand_end = getRand();
    if (rand_spawn >= 0 && rand_spawn < 0.2) {
        // top spawn
        x = 54;
        y = 110;
        orientation = Orientation::down;
        if(rand_end >= 0 && rand_end < 0.5) {
            end_x = possible_end_bottom_x;
            end_y = possible_end_bottom_y;
        } else if(rand_end >= 0.5 && rand_end < 0.75) {
            end_x = possible_end_right_x;
            end_y = possible_end_right_y;
        } else {
            end_x = possible_end_left_x;
            end_y = possible_end_left_y;
        }
    } else if (rand_spawn >= 0.2 && rand_spawn < 0.4) {
        // bottom spawn
        x = 66;
        y = 10;
        orientation = Orientation::up;
        if(rand_end >= 0 && rand_end < 0.5) {
            end_x = possible_end_top_x;
            end_y = possible_end_top_y;
        } else if(rand_end >= 0.5 && rand_end < 0.75) {
            end_x = possible_end_right_x;
            end_y = possible_end_right_y;
        } else {
            end_x = possible_end_left_x;
            end_y = possible_end_left_y;
        }
    } else if (rand_spawn >= 0.4 && rand_spawn < 0.7) {
        // left spawn
        x = 10;
        y = 54;
        orientation = Orientation::right;
        if(rand_end >= 0 && rand_end < 0.5) {
            end_x = possible_end_right_x;
            end_y = possible_end_right_y;
        } else if(rand_end >= 0.5 && rand_end < 0.75) {
            end_x = possible_end_bottom_x;
            end_y = possible_end_bottom_y;
        } else {
            end_x = possible_end_top_x;
            end_y = possible_end_top_y;
        }
    } else {
        // right spawn
        x = 110;
        y = 66;
        orientation = Orientation::left;
        if(rand_end >= 0 && rand_end < 0.5) {
            end_x = possible_end_left_x;
            end_y = possible_end_left_y;
        } else if(rand_end >= 0.5 && rand_end < 0.75) {
            end_x = possible_end_bottom_x;
            end_y = possible_end_bottom_y;
        } else {
            end_x = possible_end_top_x;
            end_y = possible_end_top_y;
        }
    }
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
    goingOut = false;
    aggressivity = getRand();
    if (kind == person) {
        getCoordinationsForPedestrian(grid);
        grid->createPerson(x, y);
        velocity = getPederstrianVelocity();
        isPedInEndZone = getPedEndZone(x, y);
    } else if (kind == car) {
        getCoordinationsForCar(grid);
        grid->createCar(x, y, orientation);
        velocity = initial_car_velocity;
    }
}

/**
 * Returns the type of the movable object.
 *
 */
MovableThing Movable::getKind() { return kind; }

/**
 * Returns the orientation of the object.
 *
 */
Orientation Movable::getOrientation() { return orientation; }

bool check_x_path(int x, int check_end_x, int check_end_y, int add_x, Grid *grid) {
    for (int i = x; i != check_end_x; i += add_x) {
        if (!grid->getPoint(i, check_end_y).isEmpty()) {
            return false;
        }
    }
    return true;
}

bool check_y_path(int y, int check_end_x, int check_end_y, int add_y, Grid *grid) {
    for (int j = y; j != check_end_y; j += add_y) {
        if (!grid->getPoint(check_end_x, j).isEmpty()) {
            return false;
        }
    }
    return true;
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
            if (kind == person && grid->getPoint(i, check_end_y).getColor() != grid->car_color) {
                if (check_x_path(x, check_end_x, check_end_y + 1, add_x, grid)) {
                    std::cout << "check_x_path" << std::endl;
                    grid->removePerson(x, y);
                    y += 1;
                    grid->createPerson(x, y);
                    std::cout << "after check_x_path" << std::endl;
                    return true;
                } else if (check_x_path(x, check_end_x, check_end_y - 1, add_x, grid)) {
                    std::cout << "check_x_path" << std::endl;
                    grid->removePerson(x, y);
                    y -= 1;
                    grid->createPerson(x, y);
                    std::cout << "after check_x_path" << std::endl;
                    return true;
                }
                return false;
            } else {
                return false;
            }
        }
    }

    for (int j = y + add_y; j != check_end_y; j += add_y) {
        if (!grid->getPoint(check_end_x, j).isEmpty()) {
            if (kind == person && grid->getPoint(check_end_x, j).getColor() != grid->car_color) {
                // check if we can go around the obstacle
                if (check_y_path(y, check_end_x + 1, check_end_y, add_y, grid)) {
                    std::cout << "check_y_path" << std::endl;
                    grid->removePerson(x, y);
                    x += 1;
                    grid->createPerson(x, y);
                    std::cout << "after check_y_path" << std::endl;
                    return true;
                } else if (check_y_path(y, check_end_x - 1, check_end_y - 1, add_y, grid)) {
                    std::cout << "check_y_path" << std::endl;
                    grid->removePerson(x, y);
                    x -= 1;
                    grid->createPerson(x, y);
                    std::cout << "after check_y_path" << std::endl;
                    return true;
                }
                return false;
            } else {
                return false;
            }
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
    if (kind == person) {
        finished = isPedInEndZone(x, y);
    } else {
        if (x == end_x && y == end_y) {
            finished = true;
        }
    }

    return finished;
}

/**
 * Checks if the way is clear (and not finished) and if so, move the object by one point.
 *
 * @param grid The grid.
 */
bool Movable::move(Grid *grid, bool signalized) {
    for (int i = 0; i < velocity; i++) {

    const int PURKYNOVA_START = 48;
    const int PURKYNOVA_WIDTH = 24;
    const int SKACELOVA_START = 46;
    const int SKACELOVA_WIDTH = 28;

    // stop if obejct if it cannot move
    bool canIGo = false;
    if (signalized) {
        canIGo = canIGoWithSemaphores(grid);
    } else {
        canIGo = canIGoWithoutSemaphores(grid);
    }


    if (kind == car) {

        switch (orientation) {
            case left:
                if (x == PURKYNOVA_START + PURKYNOVA_WIDTH + 14) {
                    if (!canIGo) {
                        carStop();
                    } else {
                        goingOut = true;
                    }
                }
                break;

            case right:
                if (x == PURKYNOVA_START - 14) {
                    if (!canIGo) {
                        carStop();
                    } else {
                        goingOut = true;
                    }
                }
                break;

            case up:
                if (y == SKACELOVA_START - 14) {
                    if (!canIGo) {
                        carStop();
                    } else {
                        goingOut = true;
                    }
                }
                break;

            case down:
                if (y == SKACELOVA_START + SKACELOVA_WIDTH + 14) {
                    if (!canIGo) {
                        carStop();
                    } else {
                        goingOut = true;
                    }
                }
                break;

        }
    } else if (kind == person) {
        if (!canIGo) {
            return false;
        }
    }



        if (checkIfFinished()) {

            if (kind == person) {
                grid->removePerson(x, y);
            } else if (kind == car) {
                grid->removeCar(x, y, orientation);
            }
            
            return true;
        }
        
        if (canIGo) {
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

            // make a turn
            Orientation newOrientation = orientation;
            switch (orientation) {
                case Orientation::left:
                case Orientation::right:
                    if (new_x == end_x && new_y != end_y) {
                        if (new_y < end_y) {
                            newOrientation = up;
                        } else {
                            newOrientation = down;
                        }
                    }
                    break;
                case Orientation::up:
                case Orientation::down:
                    if (new_y == end_y && new_x != end_x) {
                        if (new_x < end_x) {
                            newOrientation = right;
                        } else {
                            newOrientation = left;
                        }
                    }
                    break;
            }
            // menim mu y ale nepremystuju ho
            if (kind == person) {
                grid->removePerson(x, y);
                grid->createPerson(new_x, new_y);
            } else if (kind == car) {
                grid->removeCar(x, y, orientation);
                orientation = newOrientation;
                // if the car cant continue, stay and wait for the way to free
                try {
                    grid->createCar(new_x, new_y, orientation);
                } catch(const std::invalid_argument& e) {
                    grid->createCar(x, y, orientation);
                    new_x = x;
                    new_y = y;
                }
                
            }

            x = new_x;
            y = new_y;
        }
    }

    // adjust car speed
    if (kind == car) {
        if (velocity == 0 && isCarSemaphoreGreen(grid)) {
            carSpeedUp();
        }

        if (velocity < initial_car_velocity) {
            carSpeedUp();
        }

    }

    return false;
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
    switch (orientation) {
        case Orientation::left:
        case Orientation::right:
            if (pedEndzone == 1 || pedEndzone == 2) {
                return grid->pedestrian_semaphore_top == grid->pedestrian_semaphore_top.green();
            } else if (pedEndzone == 3 || pedEndzone == 4) {
                return grid->pedestrian_semaphore_bottom == grid->pedestrian_semaphore_bottom.green();
            }
        case Orientation::up:
        case Orientation::down:
            if (pedEndzone == 1 || pedEndzone == 3) {
                return grid->pedestrian_semaphore_left == grid->pedestrian_semaphore_left.green();
            } else if (pedEndzone == 2 || pedEndzone == 4) {
                return grid->pedestrian_semaphore_right == grid->pedestrian_semaphore_right.green();
            }
    }
    return false;
}

/**
 * Checks if the pedestrian is on a crosswalk.
 *
 * @param grid The grid.
 * @return Returns true, if the pedestrian is on a crosswalk.
 */
bool Movable::amIonCrosswalk(Grid *grid) {
    if (y >= 46 && y <= 74) {
        if (x >= 30 && x <= 40) {
            // left crosswalk
            return true;
        } else if (x >= 76 && x <= 86) {
            // right crosswalk
            return true;
        }
    } else if (x >= 48 && x <= 72) {
        if (y >= 32 && y <= 42) {
            // bottom crosswalk
            return true;
        } else if (y >= 82 && y <= 92) {
            // top crosswalk
            return true;
        }
    }
    return false;
}

bool Movable::amIinsideIntersection(Grid *grid) {
    if (x >= 48 && x <= 72 && y >= 46 && y <= 74) {
        return true;
    }
    return false;
}

bool Movable::amIRightBeforeCrosswalk(Grid *grid) {
    int d = 0;

    if (kind == car) {
        if (x < 30) {
            d = 30 - x;
        } else if (x > 86) {
            d = x - 86;
        } else if (y < 32) {
            d = 32 - y;
        } else if (y > 92) {
            d = y - 92;
        }
        return d <= SPACE_BETWEEN_CARS;
    } else if (kind == person) {
        if (x < 48) {
            d = 48 - x;
        } else if (x > 72) {
            d = x - 72;
        }
        return d <= SPACE_BETWEEN_PEOPLE;
    }
    return false;
}

/**
 * Check all the rules with semaphores.
 *
 * @param grid The grid.
 * @return Returns true, if the object can go.
 */
bool Movable::canIGoWithSemaphores(Grid *grid) {
    if (!checkIfClearWay(grid)) {
        return false;
    }
    if (kind == car) {
        // the car is going out of the intersection
        if (goingOut) {
            return true;
        }

        if (isCarSemaphoreGreen(grid) || amIinsideIntersection(grid)) {
            return true;
        }
        // i can go to the crosswalk, even if it's red
        if (!amIRightBeforeCrosswalk(grid)) {
            return true;
        }
    } else if (kind == person) {
        if (isPedestrianSemaphoreGreen(grid) || amIonCrosswalk(grid)) {
            return true;
        }
        if (!amIRightBeforeCrosswalk(grid)) {
            return true;
        }
        // kdyz chci jit nekam, kam chce uz also nekdo jit, random se vybere kdo pujde.
    }
    return false;
}

bool Movable::amIOnPriorityRoad(Grid *grid) {
    if (y >= 46 && y <= 74 && ((x >= 0 && x <= 42) || (x >= 72 && x <= 120))) {
        return true;
    }
    return false;
}

bool Movable::ownDesicion(Grid *grid) {
    // TODO
    if (kind == person) {
        // kdyz obe auta stoji, jdi.
        // jinak rozhodnuti podle vzorce
    }
    return false;
}

bool Movable::letPedestriansGo(Grid *grid) {
    // checkni jestli tam nekdo ceka a random se rozhodni, jestli ho pustis nebo ne
    // pokud je pustil nekdo z druheho smeru, mas znacne vetsi sanci je taky pustit
    // TODO
    return false;
}

/**
 * Check all the rules without semaphores.
 *
 * @param grid The grid.
 * @return Returns true, if the object can go.
 */
bool Movable::canIGoWithoutSemaphores(Grid *grid) {
    if (!checkIfClearWay(grid)) {
        return false;
    }
    if (kind == car) {
        // kdyz jsem na hlavni, muzu jet basicly vzdycky, else se musim rozhodnout
        if (amIOnPriorityRoad(grid)) {
            return true;
        } else if (amIinsideIntersection(grid)) {
            return true;
        } else if (ownDesicion(grid)) { // z hlediska aut, nebere lidi v potaz
            return true;
        }

        // tady to chce jinou funkci - random se rozhodne, jestli je pustim nebo ne - musi tam , ale nekdo cekat.
        if (amIRightBeforeCrosswalk(grid) && letPedestriansGo(grid)) { // + && i wan
            return true;
        }
    } else if (kind == person) {
        if (amIonCrosswalk(grid)) {
            return true;
        } else if (amIRightBeforeCrosswalk(grid) && ownDesicion(grid)) {
            return true;
        }
    }
    return false;
    // crossing for pedestrians or cars kdyz nejsou na hlavni:
    // l_veh - vzdalenost od auta od prechodu nebo od auta
    // v_veh - budouci nebo stavajici rychlost auta
    // l_ped - vzdalenost chodce od konce prechodu/pruhu
    // v_ped - ocekavan rychlost chodce/auta. Da se pouzit prumer.
    // t - podle akceptace chodce/auta, u chodce se muze urcit podle agresivity chodce
    // ROVNICE: l_veh/v_veh - l_ped/v_ped >= t
}
