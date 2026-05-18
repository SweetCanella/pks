#include "dispatcher.h"

#include <iostream>
#include <utility>

#include "elevator.h"

namespace elevator_sim {

Dispatcher& Dispatcher::getInstance() {
    static Dispatcher instance;
    return instance;
}

void Dispatcher::setStrategy(std::unique_ptr<IDispatchStrategy> strategy) {
    std::lock_guard<std::mutex> lock(mtx_);
    strategy_ = std::move(strategy);
}

void Dispatcher::registerElevators(std::vector<Elevator*> elevators) {
    std::lock_guard<std::mutex> lock(mtx_);
    elevators_ = std::move(elevators);
    std::cout << "[Dispatcher] Registered " << elevators_.size()
              << " elevator(s)\n";
}

void Dispatcher::submit(Request request) {
    std::cout << "[Dispatcher] Submitted request: floor=" << request.floor
              << " direction="
              << (request.direction == Direction::Up ? "up" : "down")
              << '\n';
    queue_.push(std::move(request));
}

void Dispatcher::dispatchAll() {
    queue_.shutdown();

    while (true) {
        auto opt = queue_.waitAndPop();
        if (!opt.has_value()) {
            break;
        }
        Request r = *opt;

        std::unique_lock<std::mutex> lock(mtx_);
        if (strategy_ == nullptr || elevators_.empty()) {
            std::cout << "[Dispatcher] No strategy or elevators configured, "
                         "dropping request\n";
            continue;
        }
        Elevator* chosen = strategy_->selectElevator(r, elevators_);
        lock.unlock();

        if (chosen != nullptr) {
            chosen->assign(r);
        }
    }
}

}  // namespace elevator_sim
