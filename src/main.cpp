#include "grid.hpp"
#include "movable.hpp"
#include "image.hpp"

int main() {
    Grid grid(DEFAULT_IMAGE_SIZE);

    generateCrossroadBackgroud(&grid);

    int SECONDS = 250;

    int finished = 0;
    std::vector<Movable> movableThings;
    for (int i = 0; i < SECONDS; i++) {
        if (i % 16 == 0) {
            try {
                Movable tmp(car, 10, 54, 118, 54, right, &grid);
                movableThings.push_back(tmp);
            } catch (const std::exception& e) { }
        }


        for (size_t j = 0; j < movableThings.size(); j++) {
            if (movableThings[j].checkIfFinished()) {
                finished++;
                movableThings[j].removeMovable(&grid);

                movableThings.erase(movableThings.begin() + j);
            } else {
                movableThings[j].move(&grid);
            }
        }

        generateImage(grid, DEFAULT_IMAGE_SIZE, "output/" + std::to_string(i) + ".bmp");
    }


    std::cout << "This many people have finished the journey in 250 seconds: ";
    std::cout << finished;
    std::cout << "\n";
}

