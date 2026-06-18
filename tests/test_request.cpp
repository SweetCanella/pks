#include "catch2/catch.hpp"
#include "request.h"

TEST_CASE("Request stores floor and direction", "[request]") {
    Request request;
    request.floor = 5;
    request.direction = Direction::Down;

    REQUIRE(request.floor == 5);
    REQUIRE(request.direction == Direction::Down);
}

TEST_CASE("Request has default values", "[request]") {
    Request request;

    REQUIRE(request.floor == 0);
    REQUIRE(request.direction == Direction::Up);
}
