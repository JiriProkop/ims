#include "grid.hpp"
#include "movable.hpp"
#include "image.hpp"

int main() {
    Grid grid(100);
    int SECONDS = 250;

    int finished = 0;
    std::vector<Movable> movableThings;
    for (int i = 0; i < SECONDS; i++) {
        if (i % 10 == 0) {
            Movable tmp(person, 40, 0, 40, 99, up, &grid);
            movableThings.push_back(tmp);
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

        generateImage(grid, 100, "output/" + std::to_string(i) + ".bmp");
    }

    std::cout << "This many people have finished the journey in 250 seconds: ";
    std::cout << finished;
    std::cout << "\n";
}
