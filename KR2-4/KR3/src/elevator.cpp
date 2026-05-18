#include "elevator.h"

#include <chrono>
#include <cstdlib>
#include <iostream>

#include "i_request_completion_listener.h"

namespace elevator_sim {

Elevator::Elevator(int id, int startFloor)
    : id_(id), currentFloor_(startFloor) {}

void Elevator::addListener(IRequestCompletionListener* listener) {
    if (listener != nullptr) {
        listeners_.push_back(listener);
    }
}

void Elevator::assign(const Request& request) {
    targets_.push(request);
    std::cout << "[Elevator " << id_ << "] Assigned target floor "
              << request.floor << '\n';
}

void Elevator::process() {
    while (!targets_.empty()) {
        Request r = targets_.front();
        targets_.pop();

        int travel = std::abs(r.floor - currentFloor_);
        currentFloor_ = r.floor;

        std::cout << "[Elevator " << id_ << "] Arrived at floor "
                  << currentFloor_ << " (travelled " << travel
                  << " floor(s))\n";

        auto wait = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::steady_clock::now() - r.createdAt);

        for (auto* listener : listeners_) {
            listener->onCompleted(r, wait);
        }
    }
}

}  // namespace elevator_sim
