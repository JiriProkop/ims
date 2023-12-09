#include <vector>

#ifndef GRID_HPP
#define GRID_HPP

enum Orientation { left, right, up, down };

class Color {
  public:
    int r;
    int g;
    int b;
    Color(int red, int green, int blue);
    Color red();
    Color green();

    bool operator==(const Color &c) {
        if (r == c.r && g == c.g && b == c.b)
            return true;
        return false;
    }
};

class Point {
  private:
    bool empty;

    Color bg_color = Color(255, 255, 255);
    Color color = Color(255, 255, 255);

  public:
    Point(int bg_red, int bg_green, int bg_blue);
    bool isEmpty();
    Color getColor();
    void setColor(Color color);
    void clearPoint();
};

class Grid {
  private:
    std::vector<std::vector<Point>> grid;
    int gridSize;
    const int car_len = 8;
    const int car_wid = 4;
    const Color car_color = Color(255, 0, 0);
    const Color person_color = Color(0, 255, 0);

  public:
    Grid(int size);
    Point getPoint(int x, int y);
    void setPoint(int x, int y, Point point);
    void createCar(int x_left, int y_left, Orientation orientation);
    void createPerson(int x, int y);
    bool isCar(int x, int y);
    bool isPerson(int x, int y);
    void removeCar(int x_left, int y_left, Orientation orientation);
    void removePerson(int x, int y);
    // FIXME semafory jsou rizene v simulaci
    Color car_semaphore_horizontal = Color(255, 0, 0);
    Color car_semaphore_vertical = Color(255, 0, 0);
    
    Color pedestrian_semaphore_top = Color(255, 0, 0);
    Color pedestrian_semaphore_bottom = Color(255, 0, 0);
    Color pedestrian_semaphore_left = Color(255, 0, 0);
    Color pedestrian_semaphore_right = Color(255, 0, 0);
};

#endif
