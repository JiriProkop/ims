#include "grid.hpp"

#ifndef MOVABLE_HPP
#define MOVABLE_HPP

#define SPACE_BETWEEN_PEOPLE 1 // the space to leave between people
#define SPACE_BETWEEN_CARS 2 // the space to leave between cars

enum MovableThing { person, car };

class Movable {
  private:
    MovableThing kind;
    int x;
    int y;
    int end_x;
    int end_y;
    Orientation orientation;
    bool finished;

  public:
    Movable(MovableThing _kind, int _start_x, int _start_y, int _end_x, int _end_y, Orientation _orientation, Grid *grid);
    bool checkIfClearWay(Grid *grid);
    bool checkIfFinished();
    void move(Grid *grid);
    void removeMovable(Grid *grid);
};

#endif