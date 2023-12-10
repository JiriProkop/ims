#include "grid.hpp"
#include "movable.hpp"
#include "image.hpp"
#include "simulation.hpp"
#include "arguments.hpp"

int main(int argc, char **argv) {
    Arguments parsed(argc, argv);
    Simulation sim(true, parsed.simulationLength, parsed.skacelovaGreenLength, parsed.purkynovaGreenLength);
    sim.Run();

    return 0;
}

