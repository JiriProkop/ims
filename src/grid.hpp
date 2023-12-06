#include <vector>

#ifndef GRID_HPP
#define GRID_HPP

class Point {
    private:
        bool empty;

        int bg_r;
        int bg_g;
        int bg_b;

        int r;
        int g;
        int b;

    public:
        Point(int bg_red, int bg_green, int bg_blue);
        bool isEmpty();
        // TODO get color
        void setColor(int red, int green, int blue);
        void clearPoint();
};


class Grid {
    private:
        std::vector<std::vector<Point>> grid;
    
    public:
        Grid(int size);
        Point getPoint(int x, int y);
        void setPoint(int x, int y, Point point);
};

#endif