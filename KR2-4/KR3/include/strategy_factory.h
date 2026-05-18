#pragma once

#include <memory>
#include <string>

#include "i_dispatch_strategy.h"

namespace elevator_sim {

struct StrategyFactory {
    static std::unique_ptr<IDispatchStrategy> create(const std::string& name);
};

}  // namespace elevator_sim
