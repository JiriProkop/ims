#include "grid.hpp"
#include "movable.hpp"

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
Movable::Movable(MovableThing _kind, int _start_x, int _start_y, int _end_x, int _end_y, Orientation _orientation, Grid grid) {
    kind = _kind;
    x = _start_x;
    y = _start_y;
    end_x = _end_x;
    end_y = _end_y;
    orientation = _orientation;

    if (kind == person) {
        grid.createPerson(x, y);
    } else if (kind == car) {
        grid.createCar(x, y, orientation);
    }
}
/**
 * Checks if the way for the object is clear
 * 
 * @param grid The grid.
 * 
 * @return Returns a boolean (true if the way is clear).
*/
bool Movable::checkIfClearWay(Grid grid) {
    bool clear = false; // default value

    if (orientation == left) {
        clear = grid.getPoint(x - 1, y).isEmpty()
            && grid.getPoint(x - 1 - SPACE_BETWEEN_OBJECTS, y).isEmpty();
    } else if (orientation == right) {
        clear = grid.getPoint(x + 1, y).isEmpty()
            && grid.getPoint(x + 1 + SPACE_BETWEEN_OBJECTS, y).isEmpty();
    } else if (orientation == up) {
        clear = grid.getPoint(x, y + 1).isEmpty()
            && grid.getPoint(x, y + 1 + SPACE_BETWEEN_OBJECTS).isEmpty();
    } else if (orientation == down) {
        clear = grid.getPoint(x, y - 1).isEmpty()
            && grid.getPoint(x, y - 1 - SPACE_BETWEEN_OBJECTS).isEmpty();
    }
    // TODO only checks the left front point of the car, is it good enough?

    return clear;
}

/**
 * Checks if the object is in its finish
 * 
 * @return Returns true, if the object is in its finish.
*/
bool Movable::checkIfFinished() {
    bool finished = false; // default value

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
void Movable::move(Grid grid) {
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
            grid.removePerson(x, y);
            grid.createPerson(new_x, new_y);
        } else if (kind == car) {
            grid.removeCar(x, y, orientation);
            grid.createCar(new_x, new_y, orientation);
        }
    }
}