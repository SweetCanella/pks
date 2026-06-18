#pragma once

#include "i_dispatch_strategy.h"

class MinQueueStrategy : public IDispatchStrategy {
public:
    Elevator* selectElevator(const Request& request, const std::vector<Elevator*>& elevators) override;
};
