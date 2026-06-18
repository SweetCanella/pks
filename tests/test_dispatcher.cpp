#include <vector>

#include "catch2/catch.hpp"
#include "dispatcher.h"
#include "elevator.h"
#include "strategy_factory.h"
#include "support.h"

TEST_CASE("Dispatcher returns the same instance", "[dispatcher]") {
    Dispatcher& first = Dispatcher::getInstance();
    Dispatcher& second = Dispatcher::getInstance();

    REQUIRE(&first == &second);
}

TEST_CASE("Dispatcher assigns request using selected strategy", "[dispatcher]") {
    Dispatcher& dispatcher = Dispatcher::getInstance();
    Elevator nearElevator(1, 2);
    Elevator farElevator(2, 10);

    dispatcher.setStrategy(StrategyFactory::create("nearest"));
    dispatcher.registerElevators({&nearElevator, &farElevator});
    dispatcher.submit(makeRequest(3));
    dispatcher.dispatchAll();

    REQUIRE(nearElevator.queueSize() == 1);
    REQUIRE(farElevator.queueSize() == 0);
}
