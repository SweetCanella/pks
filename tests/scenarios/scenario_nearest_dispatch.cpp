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
    std::cout << "=== Scenario 2: nearest-elevator dispatch ===\n";

    Statistics stats;
    std::vector<std::unique_ptr<Elevator>> owned;
    std::vector<Elevator*> elevators;
    const int startFloors[] = {1, 5, 10};
    for (int i = 0; i < 3; ++i) {
        auto e = std::make_unique<Elevator>(i + 1, startFloors[i]);
        e->addListener(&stats);
        stats.registerElevator(e->id());
        elevators.push_back(e.get());
        owned.push_back(std::move(e));
    }

    Dispatcher& dispatcher = Dispatcher::getInstance();
    dispatcher.setStrategy(StrategyFactory::create("nearest"));
    dispatcher.registerElevators(elevators);

    dispatcher.submit(call(2, Direction::Up));
    dispatcher.submit(call(6, Direction::Down));
    dispatcher.submit(call(9, Direction::Up));
    dispatcher.dispatchAll();

    for (auto* e : elevators) {
        e->process();
        stats.onServed(e->id());
    }

    std::cout << '\n' << stats.report();
    return 0;
}
