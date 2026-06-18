#pragma once

#include <vector>

class Elevator;
struct Request;

struct IDispatchStrategy {
    virtual ~IDispatchStrategy() = default;

    virtual Elevator* selectElevator(
        const Request& request,
        const std::vector<Elevator*>& elevators) = 0;
};
