#include "strategy_factory.h"

#include <stdexcept>

#include "min_queue_strategy.h"
#include "nearest_elevator_strategy.h"

namespace elevator_sim {

std::unique_ptr<IDispatchStrategy> StrategyFactory::create(
    const std::string& name) {
    if (name == "nearest") {
        return std::make_unique<NearestElevatorStrategy>();
    }
    if (name == "min_queue") {
        return std::make_unique<MinQueueStrategy>();
    }
    throw std::invalid_argument("Unknown dispatch strategy: " + name);
}

}  // namespace elevator_sim
