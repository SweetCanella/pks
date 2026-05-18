#pragma once

#include <vector>

namespace elevator_sim {

class Elevator;
struct Request;

struct IDispatchStrategy {
    virtual ~IDispatchStrategy() = default;

    virtual Elevator* selectElevator(
        const Request& request,
        const std::vector<Elevator*>& elevators) = 0;
};

}  // namespace elevator_sim
