#pragma once

#include <memory>
#include <vector>

#include "i_dispatch_strategy.h"
#include "request.h"
#include "simple_queue.h"

class Elevator;

class Dispatcher {
public:
    static Dispatcher& getInstance();

    Dispatcher(const Dispatcher&) = delete;
    Dispatcher& operator=(const Dispatcher&) = delete;

    void setStrategy(std::unique_ptr<IDispatchStrategy> strategy);
    void registerElevators(std::vector<Elevator*> elevators);

    void submit(Request request);
    void dispatchAll();

private:
    Dispatcher() = default;

    SimpleQueue<Request> queue_;
    std::unique_ptr<IDispatchStrategy> strategy_;
    std::vector<Elevator*> elevators_;
};
