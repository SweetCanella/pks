#pragma once

#include <chrono>

namespace elevator_sim {

enum class Direction {
    Up,
    Down,
};

struct Request {
    int floor = 0;
    Direction direction = Direction::Up;
    std::chrono::steady_clock::time_point createdAt =
        std::chrono::steady_clock::now();
};

}  // namespace elevator_sim
