#include "grid.hpp"
#include "movable.hpp"
#include "image.hpp"

int main() {
    Grid grid(100);

    grid.createCar(10,10,left); // it crashes here

    generateImage(grid, 100, "output/output.bmp");
}
