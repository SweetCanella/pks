#include <iostream>

#include "simulation.h"

int main() {
    std::cout << "=== Scenario 4: full simulation run ===\n";

    SimulationConfig config;
    config.floors = 10;
    config.elevators = 3;
    config.strategy = "nearest";

    Simulation simulation(config);
    simulation.run();
    return 0;
}
