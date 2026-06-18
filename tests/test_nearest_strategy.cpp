#include <vector>

#include "catch2/catch.hpp"
#include "elevator.h"
#include "nearest_elevator_strategy.h"
#include "support.h"

TEST_CASE("NearestElevatorStrategy chooses the closest elevator", "[nearest]") {
    NearestElevatorStrategy strategy;
    Elevator first(1, 1);
    Elevator second(2, 8);
    std::vector<Elevator*> elevators{&first, &second};

    REQUIRE(strategy.selectElevator(makeRequest(7), elevators) == &second);
}

TEST_CASE("NearestElevatorStrategy returns null when there are no elevators", "[nearest]") {
    NearestElevatorStrategy strategy;
    std::vector<Elevator*> elevators;

    REQUIRE(strategy.selectElevator(makeRequest(5), elevators) == nullptr);
}
