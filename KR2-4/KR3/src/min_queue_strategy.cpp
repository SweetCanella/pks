#include "min_queue_strategy.h"

#include <limits>

#include "elevator.h"
#include "request.h"

namespace elevator_sim {

Elevator* MinQueueStrategy::selectElevator(
    const Request& /*request*/,
    const std::vector<Elevator*>& elevators) {
    Elevator* best = nullptr;
    int minQueue = std::numeric_limits<int>::max();
    for (Elevator* e : elevators) {
        if (e == nullptr) continue;
        if (e->queueSize() < minQueue) {
            minQueue = e->queueSize();
            best = e;
        }
    }
    return best;
}

}  // namespace elevator_sim
