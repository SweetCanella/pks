#include <chrono>
#include <string>

#include "catch2/catch.hpp"
#include "statistics.h"
#include "support.h"

TEST_CASE("Statistics counts completed requests", "[stats]") {
    Statistics stats;

    stats.onCompleted(makeRequest(3), std::chrono::milliseconds(100));
    stats.onCompleted(makeRequest(5), std::chrono::milliseconds(200));

    std::string report = stats.report();
    REQUIRE(report.find("Total processed: 2") != std::string::npos);
    REQUIRE(report.find("Average wait: 150 ms") != std::string::npos);
}

TEST_CASE("Statistics counts served requests for elevator", "[stats]") {
    Statistics stats;

    stats.registerElevator(1);
    stats.onServed(1);

    std::string report = stats.report();
    REQUIRE(report.find("Elevator 1 served 1 request(s)") != std::string::npos);
}
