#include "catch2/catch.hpp"
#include "elevator.h"
#include "support.h"

TEST_CASE("Elevator stores id and start floor", "[elevator]") {
    Elevator elevator(2, 4);

    REQUIRE(elevator.id() == 2);
    REQUIRE(elevator.currentFloor() == 4);
    REQUIRE(elevator.queueSize() == 0);
}

TEST_CASE("Elevator processes assigned requests", "[elevator]") {
    Elevator elevator(1, 1);
    RecordingListener listener;
    elevator.addListener(&listener);

    elevator.assign(makeRequest(4));
    elevator.assign(makeRequest(6));
    elevator.process();

    REQUIRE(elevator.currentFloor() == 6);
    REQUIRE(elevator.queueSize() == 0);
    REQUIRE(listener.count() == 2);
}
