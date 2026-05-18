#pragma once

#include <chrono>

namespace elevator_sim {

struct Request;

struct IRequestCompletionListener {
    virtual ~IRequestCompletionListener() = default;

    virtual void onCompleted(const Request& request,
                             std::chrono::milliseconds waitTime) = 0;
};

}  // namespace elevator_sim
