#include <exception>
#include <iostream>
#include <string>

#include "simulation.h"

int main(int argc, char** argv) {
    SimulationConfig config;
    if (argc >= 2) config.floors = std::stoi(argv[1]);
    if (argc >= 3) config.elevators = std::stoi(argv[2]);
    if (argc >= 4) config.strategy = argv[3];

    try {
        Simulation simulation(config);
        simulation.run();
    } catch (const std::exception& ex) {
        std::cerr << "[Fatal] " << ex.what() << '\n';
        return 1;
    }
    return 0;
}
