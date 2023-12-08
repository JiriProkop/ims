#include "grid.hpp"
#include <iostream>
#include <stdexcept>
#include <vector>

Color::Color(int red, int green, int blue) {
    r = red;
    g = green;
    b = blue;
}

Point::Point(int bg_red, int bg_green, int bg_blue) {
    bool empty = true;

    bg_color = Color(bg_red, bg_green, bg_blue);
    color = Color(bg_red, bg_green, bg_blue);
}

bool Point::isEmpty() { return empty; }

void Point::setColor(Color col) {
    color = col;
    empty = false;
}

Color Point::getColor() { return color; }

void Point::clearPoint() {
    color = bg_color;
    empty = true;
}

Grid::Grid(int size) {
    gridSize = size;
    std::vector<Point> row(size, Point(255, 255, 255));
    grid = std::vector<std::vector<Point>>(size, row);
    // Initialize the vectors with some values
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            grid[i][j].clearPoint();
        }
    }


}

Point Grid::getPoint(int x, int y) {
    // TODO check for bounds
    return grid[y][x];
}

void Grid::setPoint(int x, int y, Point point) {
    // TODO check for bounds
    grid[y][x] = point;
}

/**
 * Creates a car on the grid
 *
 * @param x_left front most left point of the car
 * @param y_left front most left point of the car
 * @param orientation orientation of the car - points where the rest of the car is
 */
void Grid::createCar(int x_left, int y_left, Orientation orientation) {
    int add_x = 1;
    int add_y = 1;
    int end_x = x_left;
    int end_y = y_left;
    switch (orientation) {
        case Orientation::left: {
            end_x += car_len;
            end_y += car_wid;
            break;
        }
        case Orientation::right: {
            add_x = -1;
            add_y = -1;
            end_x -= car_len;
            end_y -= car_wid;
            break;
        }
        case Orientation::up: {
            add_y = -1;
            end_x += car_wid;
            end_y -= car_len;
            break;
        }
        case Orientation::down: {
            add_x = -1;
            end_x -= car_wid;
            end_y += car_len;
            break;
        }
    }

    // check if the car fits
    for (int i = y_left; i != end_y; i += add_y) {
        for (int j = x_left; j != end_x; j += add_x) {
            if (x_left < 0 || x_left >= gridSize || y_left < 0 || y_left >= gridSize) {
                throw std::invalid_argument("The car is being placed out of the grid bounds.");
                return;
            } else if (!grid[i][j].isEmpty()) {
                throw std::invalid_argument("The car does not fit - some 'needed' point is not empty.");
                return;
            }       
        }
    }

    // place the car
    for (int i = y_left; i != end_y; i += add_y) {
        for (int j = x_left; j != end_x; j += add_x) {
            grid[i][j].setColor(car_color);
        }
    }
}

/**
 * Removes a car from the grid
 *
 * @param x_left front most left point of the car
 * @param y_left front most left point of the car
 * @param orientation orientation of the car - points where the rest of the car is
 */
void Grid::removeCar(int x_left, int y_left, Orientation orientation) {
    int add_x = 1;
    int add_y = 1;
    int end_x = x_left;
    int end_y = y_left;
    switch (orientation) {
        case Orientation::left: {
            end_x += car_len;
            end_y += car_wid;
            break;
        }
        case Orientation::right: {
            add_x = -1;
            add_y = -1;
            end_x -= car_len;
            end_y -= car_wid;
            break;
        }
        case Orientation::up: {
            add_y = -1;
            end_x += car_wid;
            end_y -= car_len;
            break;
        }
        case Orientation::down: {
            add_x = -1;
            end_x -= car_wid;
            end_y += car_len;
            break;
        }
    }

    // check if there really is a car
    for (int i = y_left; i != end_y; i += add_y) {
        for (int j = x_left; j != end_x; j += add_x) {
            if (!isCar(j, i)) {
                throw std::invalid_argument("Found non car object where car should be.");
                return;
            }
        }
    }

    // place the car
    for (int i = y_left; i != end_y; i += add_y) {
        for (int j = x_left; j != end_x; j += add_x) {
            grid[i][j].clearPoint();
        }
    }
}

/**
 * Creates a person on the grid
 *
 * @param x x coordinate of the person
 * @param y y coordinate of the person
 */
void Grid::createPerson(int x, int y) {
    if (!(grid[y][x].isEmpty())) {
        throw std::invalid_argument("Place is already occupied.");
    }
    grid[y][x].setColor(person_color);
}

/**
 * Removes a person from the grid
 *
 * @param x x coordinate of the person
 * @param y y coordinate of the person
 */
void Grid::removePerson(int x, int y) {
    // check if it's really a person
    if (isPerson(x, y)) {
        grid[y][x].clearPoint();
    }else{
        throw std::invalid_argument("There is no person on this place.");
    }
}

/**
 * Checks if there is a person on the given coordinates
 *
 * @param x x coordinate of the car
 * @param y y coordinate of the car
 * @return true if there is a person, false otherwise
 */
bool Grid::isPerson(int x, int y) {
    Point point = getPoint(x, y);
    if (point.isEmpty()) {
        return false;
    } else if (point.getColor() == person_color) {
        return true;
    }
    return false;
}

/**
 * Checks if there is a car on the given coordinates
 *
 * @param x x coordinate of the car
 * @param y y coordinate of the car
 * @return true if there is a car, false otherwise
 */
bool Grid::isCar(int x, int y) {
    Point point = getPoint(x, y);
    if (point.isEmpty()) {
        return false;
    } else if (point.getColor() == car_color) {
        return true;
    }
    return false;
}
