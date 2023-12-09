#include "grid.hpp"
#include <functional>

#ifndef MOVABLE_HPP
#define MOVABLE_HPP

#define SPACE_BETWEEN_PEOPLE 1 // the space to leave between people
#define SPACE_BETWEEN_CARS 2   // the space to leave between cars

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
    int aggressivity;
    int velocity;
    static const int initial_car_velocity = 14; // 25 km/h ~= 7 m/s
    static const int car_speed_change = 4;      // 2 m/s^2
    std::function<bool(int, int)> getPedEndZone(int start_x, int start_y);
    std::function<bool(int, int)> isPedInEndZone;
    bool isCarSemaphoreGreen(Grid *grid);
    bool isPedestrianSemaphoreGreen(Grid *grid);
    bool amIonCrosswalk(Grid *grid);

  public:
    Movable(MovableThing _kind, int _start_x, int _start_y, int _end_x, int _end_y, Orientation _orientation, Grid *grid);
    bool checkIfClearWay(Grid *grid);
    bool checkIfFinished();
    void carSlowDown();
    void carSpeedUp();
    void carStop();
    void move(Grid *grid);
    void removeMovable(Grid *grid);
    bool canIGoWithSemaphores(Grid *grid);
    bool canIGoWithoutSemaphores(Grid *grid);
};

#endif
