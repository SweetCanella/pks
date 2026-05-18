#pragma once

#include "i_dispatch_strategy.h"

namespace elevator_sim {

class NearestElevatorStrategy : public IDispatchStrategy {
public:
    Elevator* selectElevator(
        const Request& request,
        const std::vector<Elevator*>& elevators) override;
};

}  // namespace elevator_sim
