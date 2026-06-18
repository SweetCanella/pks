#include <stdexcept>

#include "catch2/catch.hpp"
#include "strategy_factory.h"

TEST_CASE("StrategyFactory creates known strategies", "[factory]") {
    auto nearest = StrategyFactory::create("nearest");
    auto minQueue = StrategyFactory::create("min_queue");

    REQUIRE(nearest != nullptr);
    REQUIRE(minQueue != nullptr);
}

TEST_CASE("StrategyFactory rejects unknown strategy name", "[factory]") {
    REQUIRE_THROWS_AS(StrategyFactory::create("unknown"), std::invalid_argument);
}
