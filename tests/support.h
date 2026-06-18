#pragma once

#include <chrono>

#include "i_request_completion_listener.h"
#include "request.h"

class RecordingListener : public IRequestCompletionListener {
public:
    void onCompleted(const Request& request, std::chrono::milliseconds waitTime) override {
        ++count_;
        lastFloor_ = request.floor;
        lastWait_ = waitTime;
    }

    int count() const { return count_; }
    int lastFloor() const { return lastFloor_; }
    std::chrono::milliseconds lastWait() const { return lastWait_; }

private:
    int count_ = 0;
    int lastFloor_ = -1;
    std::chrono::milliseconds lastWait_{0};
};

inline Request makeRequest(int floor, Direction dir = Direction::Up) {
    Request r;
    r.floor = floor;
    r.direction = dir;
    r.createdAt = std::chrono::steady_clock::now();
    return r;
}
