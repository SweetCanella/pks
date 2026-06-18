#pragma once

#include <memory>
#include <string>
#include <vector>

#include "elevator.h"
#include "statistics.h"

struct SimulationConfig {
    int floors = 10;
    int elevators = 3;
    std::string strategy = "nearest";
};

class Simulation {
public:
    Simulation(SimulationConfig config);

    void run();

private:
    SimulationConfig config_;
    std::vector<std::unique_ptr<Elevator>> elevators_;
    Statistics stats_;
};
