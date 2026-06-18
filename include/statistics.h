#pragma once

#include <chrono>
#include <map>
#include <string>
#include <vector>

#include "i_request_completion_listener.h"

class Statistics : public IRequestCompletionListener {
public:
    void registerElevator(int elevatorId);

    void onCompleted(const Request& request, std::chrono::milliseconds waitTime) override;

    void onServed(int elevatorId);

    std::string report() const;

private:
    std::vector<long long> waitTimesMs_;
    std::map<int, int> servedByElevator_;
};
