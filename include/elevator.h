#pragma once

#include <queue>
#include <vector>

#include "request.h"

struct IRequestCompletionListener;

class Elevator {
public:
    Elevator(int id, int startFloor = 1);

    int id() const { return id_; }
    int currentFloor() const { return currentFloor_; }
    int queueSize() const { return static_cast<int>(targets_.size()); }

    void addListener(IRequestCompletionListener* listener);

    void assign(const Request& request);

    void process();

private:
    int id_;
    int currentFloor_;
    std::queue<Request> targets_;
    std::vector<IRequestCompletionListener*> listeners_;
};
