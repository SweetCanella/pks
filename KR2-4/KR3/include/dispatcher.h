#pragma once

#include <memory>
#include <mutex>
#include <vector>

#include "i_dispatch_strategy.h"
#include "request.h"
#include "thread_safe_queue.h"

namespace elevator_sim {

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

    mutable std::mutex mtx_;
    ThreadSafeQueue<Request> queue_;
    std::unique_ptr<IDispatchStrategy> strategy_;
    std::vector<Elevator*> elevators_;
};

}  // namespace elevator_sim
