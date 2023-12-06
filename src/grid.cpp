#include <vector>
#include "grid.hpp"

Point::Point(int bg_red, int bg_green, int bg_blue) {
    bool empty = true;
        
    int bg_r = bg_red;
    int bg_g = bg_green;
    int bg_b = bg_red;

    int r = bg_red;
    int g = bg_green;
    int b = bg_blue;
}

bool Point::isEmpty() {
    return empty;
}

void Point::setColor(int red, int green, int blue) {
    r = red;
    g = green;
    b = blue;
    empty = false;
}

void Point::clearPoint() {
    r = bg_r;
    g = bg_g;
    b = bg_b;
    empty = true;
}

Grid::Grid(int size) {
    std::vector<Point> row(size, Point(0, 0, 0));
    grid = std::vector<std::vector<Point>>(size, row); 
}

Point Grid::getPoint(int x, int y) {
    // TODO check for bounds
    return grid[x][y];
}

void Grid::setPoint(int x, int y, Point point) {
    // TODO check for bounds
    grid[x][y] = point;
}