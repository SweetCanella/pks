#include <vector>

#include "catch2/catch.hpp"
#include "elevator.h"
#include "min_queue_strategy.h"
#include "support.h"

TEST_CASE("MinQueueStrategy chooses elevator with the smallest queue", "[minqueue]") {
    MinQueueStrategy strategy;
    Elevator busy(1, 1);
    Elevator free(2, 1);
    busy.assign(makeRequest(3));
    std::vector<Elevator*> elevators{&busy, &free};

    REQUIRE(strategy.selectElevator(makeRequest(5), elevators) == &free);
}

TEST_CASE("MinQueueStrategy returns null when there are no elevators", "[minqueue]") {
    MinQueueStrategy strategy;
    std::vector<Elevator*> elevators;

    REQUIRE(strategy.selectElevator(makeRequest(5), elevators) == nullptr);
}
