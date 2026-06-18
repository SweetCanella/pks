#include "catch2/catch.hpp"
#include "simple_queue.h"

TEST_CASE("SimpleQueue stores and returns values", "[queue]") {
    SimpleQueue<int> queue;

    queue.push(10);
    auto value = queue.pop();

    REQUIRE(value.has_value());
    REQUIRE(*value == 10);
    REQUIRE(queue.empty());
}

TEST_CASE("SimpleQueue returns values in order", "[queue]") {
    SimpleQueue<int> queue;

    queue.push(1);
    queue.push(2);

    REQUIRE(*queue.pop() == 1);
    REQUIRE(*queue.pop() == 2);
}
