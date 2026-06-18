#include "simulation.h"

#include <iostream>

#include "dispatcher.h"
#include "request.h"
#include "strategy_factory.h"

Simulation::Simulation(SimulationConfig config) : config_(std::move(config)) {}

void Simulation::run() {
    std::cout << "[Simulation] Starting elevator simulator\n";
    std::cout << "[Simulation] Config: floors=" << config_.floors
              << ", elevators=" << config_.elevators
              << ", strategy=" << config_.strategy << '\n';

    elevators_.clear();
    std::vector<Elevator*> rawElevators;
    rawElevators.reserve(static_cast<size_t>(config_.elevators));
    for (int i = 1; i <= config_.elevators; ++i) {
        auto elevator = std::make_unique<Elevator>(i, 1);
        elevator->addListener(&stats_);
        stats_.registerElevator(i);
        rawElevators.push_back(elevator.get());
        elevators_.push_back(std::move(elevator));
    }

    Dispatcher& dispatcher = Dispatcher::getInstance();
    dispatcher.setStrategy(StrategyFactory::create(config_.strategy));
    dispatcher.registerElevators(rawElevators);

    const std::vector<Request> demoRequests = {
        {5, Direction::Up, std::chrono::steady_clock::now()},
        {3, Direction::Down, std::chrono::steady_clock::now()},
        {8, Direction::Up, std::chrono::steady_clock::now()},
        {2, Direction::Down, std::chrono::steady_clock::now()},
    };

    for (const auto& r : demoRequests) {
        dispatcher.submit(r);
    }

    dispatcher.dispatchAll();

    for (auto& e : elevators_) {
        e->process();
        stats_.onServed(e->id());
    }

    std::cout << '\n' << stats_.report();
    std::cout << "[Simulation] Completed successfully\n";
}
