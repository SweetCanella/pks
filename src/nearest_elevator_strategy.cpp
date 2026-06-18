#include "nearest_elevator_strategy.h"

#include <cstdlib>
#include <limits>

#include "elevator.h"
#include "request.h"


Elevator* NearestElevatorStrategy::selectElevator(const Request& request, const std::vector<Elevator*>& elevators) {
    Elevator* best = nullptr;
    int bestDistance = std::numeric_limits<int>::max();
    for (Elevator* e : elevators) {
        if (e == nullptr) continue;
        int distance = std::abs(e->currentFloor() - request.floor);
        if (distance < bestDistance) {
            bestDistance = distance;
            best = e;
        }
    }
    return best;
}

