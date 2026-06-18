#include <iostream>

#include "elevator.h"
#include "request.h"
#include "statistics.h"

Request call(int floor, Direction dir) {
    Request r;
    r.floor = floor;
    r.direction = dir;
    r.createdAt = std::chrono::steady_clock::now();
    return r;
}

int main() {
    std::cout << "=== Scenario 1: single elevator ===\n";

    Statistics stats;
    Elevator elevator(1, 1);
    elevator.addListener(&stats);
    stats.registerElevator(elevator.id());

    elevator.assign(call(5, Direction::Up));
    elevator.assign(call(2, Direction::Down));
    elevator.assign(call(9, Direction::Up));

    elevator.process();
    stats.onServed(elevator.id());

    std::cout << '\n' << stats.report();
    std::cout << "Final floor: " << elevator.currentFloor() << '\n';
    return 0;
}
