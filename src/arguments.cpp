#include <iostream>
#include "arguments.hpp"

Arguments::Arguments(int argc, char** argv) {
    if (argc != 4) {
        printf("You must specify 3 arguments:\n");
        printf("  ./crossroad simulationLength skacelovaGreenLength purkynovaGreenLength\n");
        exit(1);
    }

    simulationLength = atoi(argv[1]);
    skacelovaGreenLength = atoi(argv[2]);
    purkynovaGreenLength = atoi(argv[3]);
}