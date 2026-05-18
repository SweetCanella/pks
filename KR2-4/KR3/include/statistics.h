#pragma once

#include <chrono>
#include <map>
#include <mutex>
#include <string>
#include <vector>

#include "i_request_completion_listener.h"

namespace elevator_sim {

class Statistics : public IRequestCompletionListener {
public:
    void registerElevator(int elevatorId);

    void onCompleted(const Request& request,
                     std::chrono::milliseconds waitTime) override;

    void onServed(int elevatorId);

    std::string report() const;

private:
    mutable std::mutex mtx_;
    std::vector<long long> waitTimesMs_;
    std::map<int, int> servedByElevator_;
};

}  // namespace elevator_sim
