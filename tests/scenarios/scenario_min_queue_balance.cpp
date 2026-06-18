#include <iostream>
#include <memory>
#include <vector>

#include "dispatcher.h"
#include "elevator.h"
#include "request.h"
#include "statistics.h"
#include "strategy_factory.h"

Request call(int floor, Direction dir) {
    Request r;
    r.floor = floor;
    r.direction = dir;
    r.createdAt = std::chrono::steady_clock::now();
    return r;
}

int main() {
    std::cout << "=== Scenario 3: min-queue load balancing ===\n";

    Statistics stats;
    std::vector<std::unique_ptr<Elevator>> owned;
    std::vector<Elevator*> elevators;
    for (int i = 0; i < 2; ++i) {
        auto e = std::make_unique<Elevator>(i + 1, 1);
        e->addListener(&stats);
        stats.registerElevator(e->id());
        elevators.push_back(e.get());
        owned.push_back(std::move(e));
    }

    Dispatcher& dispatcher = Dispatcher::getInstance();
    dispatcher.setStrategy(StrategyFactory::create("min_queue"));
    dispatcher.registerElevators(elevators);

    for (int floor : {3, 7, 4, 9}) {
        dispatcher.submit(call(floor, Direction::Up));
    }
    dispatcher.dispatchAll();

    std::cout << "\nQueue sizes before processing:\n";
    for (auto* e : elevators) {
        std::cout << "  Elevator " << e->id() << ": " << e->queueSize()
                  << " target(s)\n";
    }

    for (auto* e : elevators) {
        e->process();
        stats.onServed(e->id());
    }

    std::cout << '\n' << stats.report();
    return 0;
}
